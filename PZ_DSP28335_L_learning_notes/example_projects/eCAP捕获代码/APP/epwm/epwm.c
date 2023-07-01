/*
 * epwm.c
 *
 *  Created on: 2018-1-26
 *      Author: Administrator
 */


#include "epwm.h"
#include "leds.h"

interrupt void epwm1_tzint_isr(void);
void EPWM1_Init(Uint16 tbprd)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Disable TBCLK within the ePWM
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
	EDIS;

	InitEPwm1Gpio();
	InitTzGpio();

	//////////////////////////////以下3个IO口设置为输出，作为列扫描////////////////////////////
	EALLOW;
	//初始化行1的GPIO48
	GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;   									// Enable pullup on GPIO48
	GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1;   									// Load output latch
	GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;  									// GPIO48 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;   									// GPIO48 = output

	//初始化行2的GPIO49
	GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;   									// Enable pullup on GPIO49
	GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;   									// Load output latch
	GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;  									// GPIO49 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;   									// GPIO49 = output

	//初始化行3的GPIO50
	GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;   									// Enable pullup on GPIO50
	GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1;   									// Load output latch
	GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;  									// GPIO50 = GPIO
	GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;   									// GPIO50 = output
	EDIS;

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.EPWM1_TZINT = &epwm1_tzint_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	EDIS;

	// Enable TZ1 and TZ2 as one shot trip sources
	EALLOW;
	EPwm1Regs.TZSEL.bit.OSHT1 = 1;
	EPwm1Regs.TZSEL.bit.OSHT2 = 1;

	// What do we want the TZ1 and TZ2 to do?
	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI;
	EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

	// Enable TZ interrupt
	EPwm1Regs.TZEINT.bit.OST = 1;
	EDIS;

	// Setup Sync
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;  // Pass through
	// Allow each timer to be sync'ed
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	EPwm1Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm1Regs.TBPRD = tbprd;
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=1;
	EPwm1Regs.TBCTL.bit.CLKDIV=0;

	// Setup shadow register load on ZERO
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm1Regs.CMPA.half.CMPA = 0;    // Set compare A value
	EPwm1Regs.CMPB = 0;              // Set Compare B value

	// Set actions
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // Set PWM1B on Zero
	EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;          // Clear PWM1B on event B, up count


	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	EDIS;

	// Enable CPU INT3 which is connected to EPWM1-3 INT:
	IER |= M_INT2;

	// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
	PieCtrlRegs.PIEIER2.bit.INTx1 = 1;

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

interrupt void epwm1_tzint_isr(void)
{
	 EALLOW;
	 EPwm1Regs.TZCLR.bit.OST = 1;
	 EPwm1Regs.TZCLR.bit.INT = 1;
	 EDIS;
	// Acknowledge this interrupt to receive more interrupts from group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}


void EPwm1A_SetCompare(Uint16 val)
{
	EPwm1Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm1B_SetCompare(Uint16 val)
{
	EPwm1Regs.CMPB = val;  //设置占空比
}


void EPWM6_Init(Uint16 tbprd)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Disable TBCLK within the ePWM
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;  // ePWM6
	EDIS;

	InitEPwm6Gpio();

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	EDIS;

	// Setup Sync
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;  // Pass through
	// Allow each timer to be sync'ed
	EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm6Regs.TBPHS.half.TBPHS = 0;
	EPwm6Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm6Regs.TBPRD = tbprd;
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
	EPwm6Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
	EPwm6Regs.TBCTL.bit.CLKDIV=TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm6Regs.CMPA.half.CMPA = 0;    // Set compare A value
	EPwm6Regs.CMPB = 0;              // Set Compare B value

	// Set actions
	EPwm6Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
	EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count
	EPwm6Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // Set PWM1B on Zero
	EPwm6Regs.AQCTLB.bit.CBU = AQ_SET;          // Clear PWM1B on event B, up count

	EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm6Regs.ETSEL.bit.INTEN = 1;  // Enable INT
	EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	EDIS;
}

void EPwm6A_SetCompare(Uint16 val)
{
	EPwm6Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm6B_SetCompare(Uint16 val)
{
	EPwm6Regs.CMPB = val;  //设置占空比
}




void EPWM3_Init(Uint16 tbprd)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
	EDIS;

	InitEPwm3Gpio();

	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm3Regs.TBPRD = tbprd;
	EPwm3Regs.TBPHS.all = 0x00000000;
	EPwm3Regs.AQCTLA.bit.PRD = AQ_TOGGLE;      // Toggle on PRD

	// TBCLK = SYSCLKOUT
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;
	EPwm3Regs.TBCTL.bit.CLKDIV = 0;

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
}


void EPWM5_Init(Uint16 tbprd)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;  // ePWM5
	EDIS;

	InitEPwm5Gpio();

	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
	EPwm5Regs.TBPRD = tbprd;
	EPwm5Regs.TBPHS.all = 0x00000000;
	EPwm5Regs.AQCTLA.bit.PRD = AQ_TOGGLE;      // Toggle on PRD

	// TBCLK = SYSCLKOUT
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = 1;
	EPwm5Regs.TBCTL.bit.CLKDIV = 0;

    // Setup shadow register load on ZERO
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values

    EPwm5Regs.CMPB = 0;              // Set Compare B value

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm5Regs.CMPA.half.CMPA = EPwm5Regs.TBPRD*0.3;    // Set compare A value
	EDIS;

}
void EPwm5A_SetCompare(Uint16 val)
{
    EPwm5Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm5B_SetCompare(Uint16 val)
{
    EPwm5Regs.CMPB = val;  //设置占空比
}
