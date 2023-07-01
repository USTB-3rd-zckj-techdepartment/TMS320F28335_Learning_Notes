/*
 * adc.c
 *
 *  Created on: 2018-1-29
 *      Author: Administrator
 */

#include "adc.h"




void ADC_Init(void)
{
	// Specific clock setting for this example:
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
	EDIS;
	AdcRegs.ADCREFSEL.bit.REF_SEL = 0;//�����ڲ��ο���ѹ һ��Ĭ�����
	// Specific clock setting for this example:
	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/(2*ADC_MODCLK) =25Mhz//Ĭ�����ò����޸� ADCʱ��Ƶ�ʲ�Ӱ�����Ƶ��
	EDIS;
    /*
     * �������ADCTRL3����
     * ��Ҫ����//��ADC����ʱ������ ����ģʽ����
     */
	//AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits/˳�����  //�˺�����InitAdc()����
	InitAdc();  // For this example, init the ADC //ADCTRL3�ĳ�ʼ��
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  ////Ĭ�����ò����޸� ADCʱ��Ƶ�ʲ�Ӱ�����Ƶ��
    /*  AdcRegs.ADCTRL3.all
     *  bit 15-8    0 ;����
     *  bit 7-6    11 ;ADCBGRFDN,reference power ,00=off 11=on
     *  bit  5      1 ;ADCPWDN��main ADC power��0=off��1=on
     *  bit 4-1   0001;ADCCLKPS��clock prescaler��FCLK=HSPCLK/(2*ADCCLKPS)
     *  bit  0      0 ;SMODE_SEL��0=sequential sampling�����в�������1=simultaneous sampling(��������)
     */
	/*
	 * �������ADCTRL1����
	 * ��Ҫ����//��λ���ܣ��趨��������
	 */
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;  //ADC_SHCLK=0xf //Ĭ�����ò����޸� ADCʱ��Ƶ�ʲ�Ӱ�����Ƶ��
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode����ģʽ
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       // Setup continuous run
	/*  AdcRegs.ADCTRL1.all
	 *  bit 15      0 ;����
	 *  bit 14      0 ;RESEY ��λ 0 =�޶�����1=��λADC
	 *  bit 13-12  00 ;SUSMOD,00=ignore emulation suspend ����Ĭ�ϼ���
	 *  bit 11-8 1111 ;ACQ_PS (Acquisition)��1111=16XADCCLK  //ADCģ�������е�S/H���
	 *  bit  7      0 ;CPS(Core clock)��0: ADCCLKFCLK/1��1: ADCCLKFCLK/2 (�����һ������Ƶ)
	 *  bit  6      0 ;CONT_RUN��0=start/stop mode��1=continuous run  //0����ͣ����ģʽ��1����������ģʽ��������һ�λ᲻ͣ������
	 *  bit  5      0 ;SEQ_OVRD��0=disabled��1=enabled
	 *  bit  4      1 ;SEQ_CASC��0=dual sequencer��˫���У���1=cascaded sequencer��������
	 *  bit 3-0     0 ;����
	 */
    /*
     * �������ADCTRL2����
     * ��Ҫ����//������� ���з����� �ж�ʹ�ܵȵ�
     */
    // Start SEQ1
    AdcRegs.ADCTRL2.all = 0x0900;
    /*  AdcRegs.ADCTRL2.all
     *  bit 15      0 ;ePWM_SOCB_SEQ��0=no action
     *  bit 14      0 ;RST_SEQ1��0=no action
     *  bit 13      0 ;SOC_SEQ1��0=clear any pending SOCs 1= Start SEQ1
     *  bit 12      0 ;����
     *  bit 11      1 ;INT_ENA_SEQ1��1=enable interrupt ʹ��SEQ1�ж�
     *  bit 10      0 ;INT_MOD_SEQ1��0=interrupt on every SEQ1 conversion
     *  bit  9      0 ;����
     *  bit  8      1 ;ePWM_SOCA_SEQ1��1=SEQ1 start from ePWM SOCA trigger
     *  bit  7      0 ;EXT_SOC_SEQ1��1=SEQ1 start from ADCSOC pin
     *  bit  6      0 ;RST_SEQ2��0=no action
     *  bit  5      0 ;SOC_SEQ2��0=clear any pending SOCs
     *  bit  4      0 ;����
     *  bit  3      0 ;INT_ENA_SEQ2��1=enable interrupt ʹ��SEQ2�ж� 0= interrupt disabled
     *  bit  2      0 ;INT_MOD_SEQ2��0=interrupt on every SEQ2 conversion
     *  bit  1      0 ;����
     *  bit  0      0 ;ePWM_SOCB_SEQ2��0=no action
     */
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; //����ADCIN0ͨ����ADC�����з��������ã�
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;  //ֻ��1��ͨ������ֵΪ1����ͨ����-1��Ĭ�ϣ�=0
}

Uint16 Read_ADCValue(void)
{
	while (AdcRegs.ADCST.bit.INT_SEQ1== 0);
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	return AdcRegs.ADCRESULT0>>4;
}

