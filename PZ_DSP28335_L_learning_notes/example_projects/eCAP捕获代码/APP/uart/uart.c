/*
 * uart.c
 *
 *  Created on: 2018-1-31
 *      Author: Administrator
 */

#include "uart.h"


void UARTa_Init(Uint32 baud)
{
	unsigned char scihbaud=0;
	unsigned char scilbaud=0;
	Uint16 scibaud=0;

	scibaud=37500000/(8*baud)-1;
	scihbaud=scibaud>>8;
	scilbaud=scibaud&0xff;


	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
	EDIS;

	InitSciaGpio();

	//Initalize the SCI FIFO
	SciaRegs.SCIFFTX.all=0xE040;
	SciaRegs.SCIFFRX.all=0x204f;
	SciaRegs.SCIFFCT.all=0x0;

	// Note: Clocks were turned on to the SCIA peripheral
	// in the InitSysCtrl() function
	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
								   // No parity,8 char bits,
								   // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
								   // Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA =1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	SciaRegs.SCIHBAUD    =scihbaud;  // 9600 baud @LSPCLK = 37.5MHz.
	SciaRegs.SCILBAUD    =scilbaud;
//	SciaRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset

}


// Transmit a character from the SCI'
void UARTa_SendByte(int a)
{
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0);
	SciaRegs.SCITXBUF=a;
}

void UARTa_SendString(char * msg)
{
	int i=0;

	while(msg[i] != '\0')
	{
		UARTa_SendByte(msg[i]);
		i++;
	}
}



//用于波特率自动识别测试
#ifdef UART_AUTOBAUN_TEST

#define BAUDSTEP 100            // Amount BRR will be incremented between each
                                // autobaud lock

Uint16 ReceivedCount;
Uint16 ErrorCount;
Uint16 SendChar;
Uint16 ReceivedAChar;   // scia received character
Uint16 ReceivedBChar;   // scib received character
Uint16 BRRVal;
Uint16 Buff[10] = {0x55, 0xAA, 0xF0, 0x0F, 0x00, 0xFF, 0xF5, 0x5F, 0xA5, 0x5A};


void error(char n)
{
	ErrorCount++;
	asm("     ESTOP0");  	       // Uncomment to stop the test here
	for (;;);

}

// SCIA  8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scia_init()
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

    // Reset FIFO's
    SciaRegs.SCIFFTX.all=0x8000;

    SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;
    SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset


}

// SCIB  8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity

void scib_init()
{
    // Reset FIFO's
    ScibRegs.SCIFFTX.all=0x8000;

    // 1 stop bit, No parity, 8-bit character
    // No loopback
    ScibRegs.SCICCR.all = 0x0007;

    // Enable TX, RX, Use internal SCICLK
    ScibRegs.SCICTL1.all = 0x0003;

    // Disable RxErr, Sleep, TX Wake,
    // Diable Rx Interrupt, Tx Interrupt
    ScibRegs.SCICTL2.all = 0x0000;

    // Relinquish SCI-A from reset
    ScibRegs.SCICTL1.all = 0x0023;

}

// Transmit a character from the SCI-A'
void scia_xmit(int a)
{
    SciaRegs.SCITXBUF=a;
}

// Transmit a character from the SCI-B'
void scib_xmit(int a)
{
    ScibRegs.SCITXBUF=a;
}

//------------------------------------------------
// Perform autobaud lock with the host.
// Note that if autobaud never occurs
// the program will hang in this routine as there
// is no timeout mechanism included.
//------------------------------------------------

void scia_AutobaudLock()
{

    SciaRegs.SCICTL1.bit.SWRESET = 0;
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    // Must prime baud register with >= 1
    SciaRegs.SCIHBAUD = 0;
    SciaRegs.SCILBAUD = 1;

    // Prepare for autobaud detection
    // Make sure the ABD bit is clear by writing a 1 to ABDCLR
    // Set the CDC bit to enable autobaud detection
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;
    SciaRegs.SCIFFCT.bit.CDC = 1;

    // Wait until we correctly read an
    // 'A' or 'a' and lock
	//
	// As long as Autobaud calibration is enabled (CDC = 1),
	// SCI-B (host) will continue transmitting 'A'. This will
	// continue until interrupted by the SCI-A RX ISR, where
	// SCI-A RXBUF receives 'A', autobaud-locks (ABDCLR=1
	// CDC=0),and returns an 'A' back to the host. Then control
	// is returned to this loop and the loop is exited.
	//
	// NOTE: ABD will become set sometime between
	//       scib_xmit and the DELAY_US loop, and
	//       the SCI-A RX ISR will be triggered.
    //       Upon returning and reaching the if-statement,
	//       ABD will have been cleared again by the ISR.

    while(SciaRegs.SCIFFCT.bit.CDC== 1)
    {
       // Note the lower the baud rate the longer
       // this delay has to be to allow the other end
       // to echo back a character (about 4 characters long)
       // Make this really long since we are going through all
       // the baud rates.
    	DELAY_US(280000L);



    	if(SciaRegs.SCIFFCT.bit.CDC == 1)
    		scib_xmit('A');  // host transmits 'A'

    }

    return;
}

/* --------------------------------------------------- */
/* ISR for PIE INT9.1                                  */
/* Connected to RXAINT  SCI-A                          */
/* ----------------------------------------------------*/

interrupt void rxaint_isr(void)     // SCI-A
{
	// Insert ISR Code here

	PieCtrlRegs.PIEACK.bit.ACK9 = 1;

	// If autobaud detected, we must clear CDC
	if(SciaRegs.SCIFFCT.bit.ABD == 1)
	{
		SciaRegs.SCIFFCT.bit.ABDCLR = 1;
		SciaRegs.SCIFFCT.bit.CDC = 0;
		// Check received character - should be 'A'
		ReceivedAChar = 0;
		ReceivedAChar = SciaRegs.SCIRXBUF.all;
		if(ReceivedAChar != 'A')
		{
			error(2);
		}
      else scia_xmit(ReceivedAChar);
	}

   // This was not autobaud detect
   else
   {
      // Check received character against sendchar
      ReceivedAChar = 0;
      ReceivedAChar = SciaRegs.SCIRXBUF.all;
      if(ReceivedAChar != SendChar)
      {
         error(3);
      }
      else scia_xmit(ReceivedAChar);
   }

   SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;	// clear Receive interrupt flag
   ReceivedCount++;
}

void UART_AutoBaud_Test(void)
{
	Uint16 i=0;

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
	SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;   // SCI-B
	EDIS;

	InitSciaGpio();
	InitScibGpio();

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;	    // This is needed to write to EALLOW protected registers
	PieVectTable.SCIRXINTA = &rxaint_isr;
	EDIS;       // This is needed to disable write to EALLOW protected register

	scia_init();       // Initalize SCIA
	scib_init();       // Initalize SCIB

	// Enable interrupts
	PieCtrlRegs.PIEIER9.all = 0x0001; // Enable all SCIA RXINT interrupt
	IER |= M_INT9;			         // enable PIEIER9, and INT9
	EINT;

	// Start with BRR = 1, work through each baud rate setting
	// incrementing BRR by BAUDSTEP
	for (BRRVal = 0x0000; BRRVal < (Uint32)0xFFFF; BRRVal+=BAUDSTEP)
	{

		// SCIB has a known baud rate.  SCIA will autobaud to match
		ScibRegs.SCIHBAUD = (BRRVal >> 8);
		ScibRegs.SCILBAUD = (BRRVal);

		// Initiate an autobaud lock with scia.  Check
		// returned character against baud lock character 'A'
		scia_AutobaudLock();
		while(ScibRegs.SCIRXST.bit.RXRDY != 1) { }
		ReceivedBChar = 0;
		ReceivedBChar =  ScibRegs.SCIRXBUF.bit.RXDT;
		if(ReceivedBChar != 'A')
		{
			error(0);
		}

		// Send/echoback characters
		// 55 AA F0 0F 00 FF F5 5F A5 5A
		for(i= 0; i<=9; i++)
		{
		  SendChar = Buff[i];
		  scib_xmit(SendChar);			    // Initiate interrupts and xmit data in isr
		  // Wait to get the character back and check
		  // against the sent character.
		  while(ScibRegs.SCIRXST.bit.RXRDY != 1)
		  {
			  asm("   NOP");
		  }
		  ReceivedBChar = 0;
		  ReceivedBChar =  ScibRegs.SCIRXBUF.bit.RXDT;
		  if(ReceivedBChar != SendChar) error(1);
		}

	} // Repeat for next BRR setting

	// Stop here, no more
	while(1)
	{
		asm("    NOP");
	}

}


#endif

