/*
 * epwm.c
 *
 *  Created on: 2018-1-26
 *      Author: Administrator
 */


#include "epwm.h"
#include "leds.h"

interrupt void epwm1_isr(void);
void EPWM1_Init(Uint16 tbprd)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Disable TBCLK within the ePWM
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
	EDIS;

	InitEPwm1Gpio();

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.EPWM1_INT = &epwm1_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	EDIS;

	// Setup Sync
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;  // Pass through
	// Allow each timer to be sync'ed
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	EPwm1Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm1Regs.TBPRD = tbprd;
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=0x4;
	EPwm1Regs.TBCTL.bit.CLKDIV=TB_DIV4;

	// Setup shadow register load on ZERO
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm1Regs.CMPA.half.CMPA = 0;    // Set compare A value
	EPwm1Regs.CMPB = 0;              // Set Compare B value

	// Set actions
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;            // Set PWM1B on Zero
	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;          // Clear PWM1B on event B, up count

	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm1Regs.ETSEL.bit.INTEN = 1;  // Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	EDIS;

	// Enable CPU INT3 which is connected to EPWM1-3 INT:
	IER |= M_INT3;

	// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

interrupt void epwm1_isr(void)
{
	static Uint16 cnt=0;

	cnt++;
	if(cnt==5000)
	{
		cnt=0;
		LED3_TOGGLE;
	}

	// Clear INT flag for this timer
	EPwm1Regs.ETCLR.bit.INT = 1;
	// Acknowledge this interrupt to receive more interrupts from group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
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

void EPWM2_Init(Uint16 tbprd)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Disable TBCLK within the ePWM
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
    EDIS;

    InitEPwm2Gpio();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    // Setup Sync
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;  // Pass through
    // Allow each timer to be sync'ed
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm2Regs.TBPHS.half.TBPHS = 0;
    EPwm2Regs.TBCTR = 0x0000;                  // Clear counter
    EPwm2Regs.TBPRD = tbprd;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV=TB_DIV1;

    // Setup shadow register load on ZERO
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set Compare values
    EPwm2Regs.CMPA.half.CMPA = 0;    // Set compare A value
    EPwm2Regs.CMPB = 0;              // Set Compare B value

    // Set actions
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_CLEAR;            // Set PWM1A on Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;          // Clear PWM1A on event A, up count
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // Set PWM1B on Zero
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;          // Clear PWM1B on event B, up count

    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm2Regs.ETSEL.bit.INTEN = 1;  // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
    EDIS;
}

void EPwm2A_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPA.half.CMPA = val;  //设置占空比
}
void EPwm2B_SetCompare(Uint16 val)
{
    EPwm2Regs.CMPB = val;  //设置占空比
}
