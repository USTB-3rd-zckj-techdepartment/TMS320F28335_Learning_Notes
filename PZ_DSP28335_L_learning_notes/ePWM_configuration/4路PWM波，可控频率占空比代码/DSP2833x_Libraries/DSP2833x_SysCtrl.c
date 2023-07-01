
//###########################################################################
//
// FILE:   DSP2833x_SysCtrl.c
//
// TITLE:  DSP2833x ��ϵͳ����ģ����г�ʼ����
//
// ����:
//         
//�ͷ����ڣ�
//###########################################################################
// DSP2833x  ͷ�ļ�
//###########################################################################


#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

//��InitFlash����ӳ�䵽CMD�ļ��е�ramfuncs�Σ���CMD�ļ���ramfuncs�α����䵽RAM����

#pragma CODE_SECTION(InitFlash, "ramfuncs");

//---------------------------------------------------------------------------
// InitSysCtrl:
//---------------------------------------------------------------------------
// ��κ����Ĺ��ܾ��ǽ�ϵͳ���ƼĴ�����ʼ������Ҫ��״̬��
//���岽����Էֳ��Ĳ��֣�
// - ��ֹ���Ź���·
// - ��PLLCR�Ĵ�����ֵ�Ի����Ҫ��ϵͳʱ��Ƶ��
// - ���ߡ���������ʱ��Ԥ����Ĵ�����ֵ�Ի����Ҫ�ĸߡ���������ʱ��Ƶ��
// - ����Ҫʹ�õ�����ʱ�ӽ���ʹ��

void InitSysCtrl(void)
{

   // Disable the watchdog
   DisableDog();

   // Initialize the PLL control: PLLCR and DIVSEL
   // DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2833x_Examples.h
   InitPll(DSP28_PLLCR,DSP28_DIVSEL);

   // Initialize the peripheral clocks
   InitPeripheralClocks();
}


//---------------------------------------------------------------------------
// ��ʼ��FLASH����
//---------------------------------------------------------------------------
// �˺�����ʼ��FLASH���ƼĴ���

//                   ע��
// �˺���������RAM�����У������OTP/FLASH�����еĻ�����������Ԥ�ϵĺ��


void InitFlash(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1;

   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI.
   //Refer to the datasheet for the latest information.
#if CPU_FRQ_150MHZ
   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;

   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 8;
#endif

#if CPU_FRQ_100MHZ
   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 3;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 3;

   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 5;
#endif
   //                CAUTION
   //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;

   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.

   asm(" RPT #7 || NOP");
}


//---------------------------------------------------------------------------
//ι������
//---------------------------------------------------------------------------
// ���������λ���Ź���ʱ��

void ServiceDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}

//---------------------------------------------------------------------------
// ��ֹ���Ź�����
//---------------------------------------------------------------------------
// �˺����������ǽ�ֹ���Ź���ʱ��

void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}

//---------------------------------------------------------------------------
// PLL��ؼĴ�����ʼ������
//---------------------------------------------------------------------------
// �˺�����ʼ��PLLSTS[CLKINDIV]��PLLCR���ƼĴ���

void InitPll(Uint16 val, Uint16 divsel)
{

   // Make sure the PLL is not running in limp mode
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
   {
      // Missing external clock has been detected
      // Replace this line with a call to an appropriate
      // SystemShutdown(); function.
      asm("        ESTOP0");
   }

   // DIVSEL MUST be 0 before PLLCR can be changed from
   // 0x0000. It is set to 0 by an external reset XRSn
   // This puts us in 1/4
   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
       EDIS;
   }

   // Change the PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {

      EALLOW;
      // Before setting PLLCR turn off missing clock detect logic
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;

      // Optional: Wait for PLL to lock.
      // During this time the CPU will switch to OSCCLK/2 until
      // the PLL is stable.  Once the PLL is stable the CPU will
      // switch to the new PLL value.
      //
      // This time-to-lock is monitored by a PLL lock counter.
      //
      // Code is not required to sit and wait for the PLL to lock.
      // However, if the code does anything that is timing critical,
      // and requires the correct clock be locked, then it is best to
      // wait until this switching has completed.

      // Wait for the PLL lock bit to be set.

      // The watchdog should be disabled before this loop, or fed within
      // the loop via ServiceDog().

	  // Uncomment to disable the watchdog
      DisableDog();

      while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
      {
	      // Uncomment to service the watchdog
          // ServiceDog();
      }

      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
      EDIS;
    }

    // If switching to 1/2
	if((divsel == 1)||(divsel == 2))
	{
		EALLOW;
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;
	    EDIS;
	}

	// If switching to 1/1
	// * First go to 1/2 and let the power settle
	//   The time required will depend on the system, this is only an example
	// * Then switch to 1/1
	if(divsel == 3)
	{
		EALLOW;
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = 2;
	    DELAY_US(50L);
	    SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;
	    EDIS;
    }
}

//--------------------------------------------------------------------------
// ����������ʼ������ʱ��
//---------------------------------------------------------------------------
//�����������ʼ������ģ���ʱ�ӣ������2�����裺
//�������øߡ���������Ԥ����Ĵ�����
//�ڶ��ǶԸ�������ʱ�ӽ�����ѡ���ʹ�ܣ�
//Ϊ�˽��͹��ģ�������ʹ�ܲ��õ�����ģ��ʱ�ӣ�
//
//ע�����ĳһ����ʱ��ûʹ�ܣ����ܶ�����صļĴ������ж�д��

void InitPeripheralClocks(void)
{
   EALLOW;

// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
   SysCtrlRegs.HISPCP.all = 0x0001;
   SysCtrlRegs.LOSPCP.all = 0x0002;//Lowspeedclock=SYSCLKOUT/4=150/4=37.5MHZ;

// XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
   // XTIMCLK = SYSCLKOUT/2
   XintfRegs.XINTCNF2.bit.XTIMCLK = 1;
   // XCLKOUT = XTIMCLK/2
   XintfRegs.XINTCNF2.bit.CLKMODE = 1;
   // Enable XCLKOUT
   XintfRegs.XINTCNF2.bit.CLKOFF = 0;

// Peripheral clock enables set for the selected peripherals.
// If you are not using a peripheral leave the clock off
// to save on power.
//
// Note: not all peripherals are available on all 2833x derivates.
// Refer to the datasheet for your particular device.
//
// This function is not written to be an example of efficient code.

   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0;    // ADC

   // *IMPORTANT*
   // The ADC_cal function, which  copies the ADC calibration values from TI reserved
   // OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
   // Boot ROM. If the boot ROM code is bypassed during the debug process, the
   // following function MUST be called for the ADC to function according
   // to specification. The clocks to the ADC MUST be enabled before calling this
   // function.
   // See the device data manual and/or the ADC Reference
   // Manual for more information.

   ADC_cal();


   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 0;   // SCI-A
   SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 0;   // SCI-B
   SysCtrlRegs.PCLKCR0.bit.SCICENCLK = 0;   // SCI-C
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;   // SPI-A
   SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = 0; // McBSP-A
   SysCtrlRegs.PCLKCR0.bit.MCBSPBENCLK = 0; // McBSP-B
   SysCtrlRegs.PCLKCR0.bit.ECANAENCLK=0;    // eCAN-A
   SysCtrlRegs.PCLKCR0.bit.ECANBENCLK=0;    // eCAN-B

   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Disable TBCLK within the ePWM
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 0;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 0;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 0;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
   SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 0;  // ePWM5
   SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 0;  // ePWM6
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Enable TBCLK within the ePWM

   SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 0;  // eCAP3
   SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 0;  // eCAP4
   SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 0;  // eCAP5
   SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 0;  // eCAP6
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  // eCAP1
   SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 0;  // eCAP2
   SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 0;  // eQEP1
   SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 0;  // eQEP2

   SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 0; // CPU Timer 0
   SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 0; // CPU Timer 1
   SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 0; // CPU Timer 2

   SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 0;       // DMA Clock
   SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 0;     // XTIMCLK
   SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;    // GPIO input clock

   EDIS;
}

//---------------------------------------------------------------------------
// Example: CsmUnlock:
//---------------------------------------------------------------------------
// This function unlocks the CSM. User must replace 0xFFFF's with current
// password for the DSP. Returns 1 if unlock is successful.

#define STATUS_FAIL          0
#define STATUS_SUCCESS       1

Uint16 CsmUnlock()
{
    volatile Uint16 temp;

    // Load the key registers with the current password. The 0xFFFF's are dummy
	// passwords.  User should replace them with the correct password for the DSP.

    EALLOW;
    CsmRegs.KEY0 = 0xFFFF;
    CsmRegs.KEY1 = 0xFFFF;
    CsmRegs.KEY2 = 0xFFFF;
    CsmRegs.KEY3 = 0xFFFF;
    CsmRegs.KEY4 = 0xFFFF;
    CsmRegs.KEY5 = 0xFFFF;
    CsmRegs.KEY6 = 0xFFFF;
    CsmRegs.KEY7 = 0xFFFF;
    EDIS;

    // Perform a dummy read of the password locations
    // if they match the key values, the CSM will unlock

    temp = CsmPwl.PSWD0;
    temp = CsmPwl.PSWD1;
    temp = CsmPwl.PSWD2;
    temp = CsmPwl.PSWD3;
    temp = CsmPwl.PSWD4;
    temp = CsmPwl.PSWD5;
    temp = CsmPwl.PSWD6;
    temp = CsmPwl.PSWD7;

    // If the CSM unlocked, return succes, otherwise return
    // failure.
    if (CsmRegs.CSMSCR.bit.SECURE == 0) return STATUS_SUCCESS;
    else return STATUS_FAIL;

}


//===========================================================================
// End of file.
//===========================================================================
