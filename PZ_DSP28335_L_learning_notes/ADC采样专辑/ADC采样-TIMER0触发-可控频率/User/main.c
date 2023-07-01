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
#include "smg.h"
#include "adc.h"

float adc_voll;
float adc_vlos[200];

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void main()
{

	int index=0;



	InitSysCtrl();

	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	LED_Init();
	//TIM0_Init(150,200000);//200ms(150MHzΪʱ��SYSCLKOUT Ҳ����150MHz������Ҫ�ģ����� �Ĳ���Y Ϊ��ʱ�����ڣ���λus 2000000us=200ms ����TI�ٷ������趨��)
	TIM0_Init(150,1000);//����1KHz�Ĳ���Ƶ��
	SMG_Init();
	ADC_Init();

	while(1)
	{
/*	    while (AdcRegs.ADCST.bit.INT_SEQ1 == 0){}

	    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	    { */
            adc_voll=(float)Read_ADCValue()*3.0/4096;
            SMG_DisplayFloat(adc_voll,2);
            adc_vlos[index++]=adc_voll;//�洢���Թ��۲�
            if(index>=200)
                {
                    index=0;
                }
/*	    }


	}*/
	}
}

