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
	AdcRegs.ADCREFSEL.bit.REF_SEL = 0;//采用内部参考电压 一般默认如此
	// Specific clock setting for this example:
	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/(2*ADC_MODCLK) =25Mhz//默认配置不用修改 ADC时钟频率不影响采样频率
	EDIS;
    /*
     * 下面进行ADCTRL3配置
     * 主要功能//对ADC采样时钟配置 采样模式配置
     */
	//AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits/顺序采样  //此函数在InitAdc()里面
	InitAdc();  // For this example, init the ADC //ADCTRL3的初始化
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  ////默认配置不用修改 ADC时钟频率不影响采样频率
    /*  AdcRegs.ADCTRL3.all
     *  bit 15-8    0 ;保留
     *  bit 7-6    11 ;ADCBGRFDN,reference power ,00=off 11=on
     *  bit  5      1 ;ADCPWDN，main ADC power，0=off，1=on
     *  bit 4-1   0001;ADCCLKPS，clock prescaler，FCLK=HSPCLK/(2*ADCCLKPS)
     *  bit  0      0 ;SMODE_SEL，0=sequential sampling（序列采样），1=simultaneous sampling(并发采样)
     */
	/*
	 * 下面进行ADCTRL1配置
	 * 主要功能//复位功能，设定采样窗口
	 */
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;  //ADC_SHCLK=0xf //默认配置不用修改 ADC时钟频率不影响采样频率
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode级联模式
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       // Setup continuous run
	/*  AdcRegs.ADCTRL1.all
	 *  bit 15      0 ;保留
	 *  bit 14      0 ;RESEY 复位 0 =无动作；1=复位ADC
	 *  bit 13-12  00 ;SUSMOD,00=ignore emulation suspend 保持默认即可
	 *  bit 11-8 1111 ;ACQ_PS (Acquisition)，1111=16XADCCLK  //ADC模块周期中的S/H宽度
	 *  bit  7      0 ;CPS(Core clock)，0: ADCCLKFCLK/1，1: ADCCLKFCLK/2 (额外的一个二分频)
	 *  bit  6      0 ;CONT_RUN，0=start/stop mode，1=continuous run  //0，启停工作模式，1，连续工作模式。（启动一次会不停采样）
	 *  bit  5      0 ;SEQ_OVRD，0=disabled，1=enabled
	 *  bit  4      1 ;SEQ_CASC，0=dual sequencer（双序列），1=cascaded sequencer（级联）
	 *  bit 3-0     0 ;保留
	 */
    /*
     * 下面进行ADCTRL2配置
     * 主要功能//软件启动 序列发生器 中断使能等等
     */
    // Start SEQ1
    AdcRegs.ADCTRL2.all = 0x0900;
    /*  AdcRegs.ADCTRL2.all
     *  bit 15      0 ;ePWM_SOCB_SEQ，0=no action
     *  bit 14      0 ;RST_SEQ1，0=no action
     *  bit 13      0 ;SOC_SEQ1，0=clear any pending SOCs 1= Start SEQ1
     *  bit 12      0 ;保留
     *  bit 11      1 ;INT_ENA_SEQ1，1=enable interrupt 使能SEQ1中断
     *  bit 10      0 ;INT_MOD_SEQ1，0=interrupt on every SEQ1 conversion
     *  bit  9      0 ;保留
     *  bit  8      1 ;ePWM_SOCA_SEQ1，1=SEQ1 start from ePWM SOCA trigger
     *  bit  7      0 ;EXT_SOC_SEQ1，1=SEQ1 start from ADCSOC pin
     *  bit  6      0 ;RST_SEQ2，0=no action
     *  bit  5      0 ;SOC_SEQ2，0=clear any pending SOCs
     *  bit  4      0 ;保留
     *  bit  3      0 ;INT_ENA_SEQ2，1=enable interrupt 使能SEQ2中断 0= interrupt disabled
     *  bit  2      0 ;INT_MOD_SEQ2，0=interrupt on every SEQ2 conversion
     *  bit  1      0 ;保留
     *  bit  0      0 ;ePWM_SOCB_SEQ2，0=no action
     */
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; //采用ADCIN0通道（ADC的序列发生器配置）
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;  //只用1个通道，故值为1（个通道）-1（默认）=0
}

Uint16 Read_ADCValue(void)
{
	while (AdcRegs.ADCST.bit.INT_SEQ1== 0);
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	return AdcRegs.ADCRESULT0>>4;
}

