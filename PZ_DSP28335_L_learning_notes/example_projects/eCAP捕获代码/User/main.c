/*
 * main.c
 *
 *  Created on: 2018-3-21
 *      Author: Administrator
 */

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "leds.h"
#include "time.h"
#include "uart.h"
#include "stdio.h"
#include "ecap.h"
#include "epwm.h"
long cap1reg[50];
long cap2reg[50];
long cap3reg[50];
long cap4reg[50];
int  index_1=0;
int  min=0;
long temp;
long mincap1;
int min_in1000=0;
int min_in500=0;
int min_in100=0;
int min_in30=0;
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main()
{



	InitSysCtrl();
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	LED_Init();
	TIM0_Init(150,200000);//200ms
	UARTa_Init(4800);

	//EPWM5_Init(PWM5_TIMER_MIN);  //ePWM在约9375Hz与7500000Hz之间变化
	EPWM1_Init(9999);
	eCAP1_Init();
/*	EPwm5A_SetCompare(2500);*/
	while(1)
	{
	    EPwm1A_SetCompare(3000);

	}
}

