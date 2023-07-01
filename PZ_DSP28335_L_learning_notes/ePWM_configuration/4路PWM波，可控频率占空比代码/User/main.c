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
#include "epwm.h"


/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void main()
{
	int i=0;


	InitSysCtrl();

	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	LED_Init();
//	TIM0_Init(1500,200000);//200ms
	EPWM1_Init(46874);
	EPWM2_Init(15000);
//	EPWM3_Init(15000);
//	EPWM4_Init(15000);
//	EPWM5_Init(15000);
	while(1)
	{

		EPwm1A_SetCompare(2344);
		EPwm1B_SetCompare(2344);
		EPwm2A_SetCompare(7500);
		EPwm2B_SetCompare(7500);
	//	EPwm3A_SetCompare(7500);
	//	EPwm3B_SetCompare(7500);
	//	EPwm4A_SetCompare(7500);
	//	EPwm4B_SetCompare(7500);
	}
}

