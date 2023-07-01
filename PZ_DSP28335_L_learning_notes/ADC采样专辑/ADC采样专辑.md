- ## 连续采样模式
  
  这部分采样效果看似不错，但实际上可控性差，比如不知道采样频率，更别提修改了。
  
  ### 首先看主函数
  
  ```C
  #include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
  #include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
  
  #include "leds.h"
  #include "time.h"
  #include "smg.h"
  #include "adc.h"
  
  
  
  
  /*******************************************************************************
  * 函 数 名         : main
  * 函数功能                   : 主函数
  * 输    入         : 无
  * 输    出         : 无
  *******************************************************************************/
  void main()
  {
          int i=0;
          float adc_vol;
  
          InitSysCtrl();
  
          InitPieCtrl();
          IER = 0x0000;
          IFR = 0x0000;
          InitPieVectTable();
  
          LED_Init();
          TIM0_Init(150,200000);//200ms
          SMG_Init();
          ADC_Init();
  
          while(1)
          {
                  adc_vol=(float)Read_ADCValue()*3.0/4096;
                  SMG_DisplayFloat(adc_vol,2);
  //                SMG_DisplayInt(Read_ADCValue());
  
          }
  }
  ```
  
  可以看出，主要分为ADC初始化，以及采样显示两个环节
  
  ### ADC初始化
  
  ```C
  void ADC_Init(void)
  {
          // Specific clock setting for this example:
          EALLOW;
          SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
          EDIS;
  
          // Specific clock setting for this example:
          EALLOW;
          SysCtrlRegs.HISPCP.all = ADC_MODCLK;        // HSPCLK = SYSCLKOUT/(2*ADC_MODCLK)
          EDIS;
  
          InitAdc();  // For this example, init the ADC
  
          // Specific ADC setup for this example:
          AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
          AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
          AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
          AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
          AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // 注意，就是这句话实现了连续采样
          AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;
  
          // Start SEQ1
          AdcRegs.ADCTRL2.all = 0x2000;
  
  }
  ```
  
  这里我没做进一步修改和阐述，给大家一个直观的感受，更细致的学习见下一章节即可
  
  ### 采样函数
  
  ```C
  Uint16 Read_ADCValue(void)
  {
          while (AdcRegs.ADCST.bit.INT_SEQ1== 0);
          AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
          return AdcRegs.ADCRESULT0>>4;
  }
  ```
  
  ## TIMER0触发ADC采样模式
  
  精华来了
  
  这一章讲述的是以可控频率触发ADC采样
  
  最终实现效果 采用1KHz的采样频率
  
  采集输入频率为1001Hz的正弦波，效果还不错，当然有进一步的优化空间，不过出新手村绝对是没问题的
  
  ![img](https://lsw8dv5h36.feishu.cn/space/api/box/stream/download/asynccode/?code=NWJjZWU4NDhlZTA4Y2Q0Y2FmZmY3YjY1NTg4YjQ5MDZfdmw2ZWZKWU15T2N0OENqMm1NV1RkcFk0MEh4c2Zuc2pfVG9rZW46Rk4xTWJOQ3VBb2hYT1p4bDJpTmN5ck9vbjNkXzE2ODgyMDQ2MDU6MTY4ODIwODIwNV9WNA)
  
  ### 首先看看ADC初始化的完全体吧
  
  首先采用内部参考电压（一般不需要更改）
  
  其次是ADC的时钟频率配置，我们这里配置的是150MHz/6/2=12.5MHz（总之这不重要！！！！）
  
  #### ADC的时钟频率、转换时间和采样频率
  
  ADC的时钟频率，转换时间和采样频率是三个比较容易混淆的概念。ADC的时钟频率就是每秒有多少个时钟脉冲的意思，它是ADC工作的基础，正如上面所介绍的，它是由系统时钟经过很多环节分频后得到的，它取决于外部的时钟输入和各个环节的倍频或者分频的系数。而转换时间是指ADC模块完成一个通道或者一个序列的转换所需要的时间，很显然，转换时间是由ADC的时钟频率来决定的。采样频率是指ADC模块每秒能够完成多少次的采样，采样频率取决于启动ADC的频率。启动ADC的方式有很多，比如利用软件直接启动，利用PWM的某些事件，或者是利用外部引脚来启动。启动ADC的频率才是ADC的采样频率，例如如果每隔1ms启动一次ADC，那么ADC的采样频率就为1KHz。ADC的采样频率和ADC时钟或者ADC转换时间都没有什么关系，采样频率应该根据采样定理和工程的实际需要来确定。在F28335中，ADC的采样频率最高为12.5MSPS。
  
  #### 采样窗口配置与时钟配置实例
  
  采样窗口越大越好（采样窗口必须保证采样电容能有足够的时间来使得其电压等于外部输入的模拟电压，否则采样就会不正确），但也不宜过大，或许8宽度足矣。
  
  过大的采样窗口会影响采样时间
  
  ![img](https://lsw8dv5h36.feishu.cn/space/api/box/stream/download/asynccode/?code=N2VmOTc0YmVjYWNiMDM4MmQxMGUyMmRkM2RjZGY3Yzdfa2RDMGx2REpaUkFKbnUyOGppUWFzTTVSVVdTS3BuOHNfVG9rZW46UTdGM2J1OXZ1b0x5Z0Z4MmtrVWMydGNQblRjXzE2ODgyMDQ2MDU6MTY4ODIwODIwNV9WNA)
  
  下图为我们完整的配置 
  
  ![img](https://lsw8dv5h36.feishu.cn/space/api/box/stream/download/asynccode/?code=NWZiNGVmNzhjY2IxMjIyYjZhZTE5NzU5Yjk1NmExOTVfb1BBRXVXSWpFSXJFclVzVkFTVU5yUzZ5amI2RWtVTlpfVG9rZW46QWZrSWJ2ODE3bzFaYWF4VmVtUWNubE5SbmlnXzE2ODgyMDQ2MDU6MTY4ODIwODIwNV9WNA)
  
  #### ADC工作方式
  
  这一部分涉及的概念较多，建议自行阅读。
  
  本实验采用SEQ1,2级联模式cascade mode
  
  顺序(sequential)采样（因为只有一个输入引脚ADCINA0）
  
  #### ADC主要配置寄存器
  
  下面三小节具体到位讲述了ADCTRL配置
  
  ##### ADCTRL3
  
  主要功能：对ADC采样时钟配置 采样模式配置
  
  ```C
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
  ```
  
  ##### ADCTRL2
  
  主要功能：软件启动 序列发生器 中断使能等等
  
  ```C
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
  ```
  
  ##### ADCTRL1
  
  主要功能：复位功能，设定采样窗口
  
  ```C
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
  ```
  
  #### 通道转换器配置
  
  ```C
     AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; //采用ADCIN0通道（ADC的序列发生器配置）
     AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;  //只用1个通道，故值为1（个通道）-1（默认）=0
  ```
  
  #### 完整配置代码
  
  ```C
  void ADC_Init(void)
  {
          // Specific clock setting for this example:
          EALLOW;
          SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
          EDIS;
          AdcRegs.ADCREFSEL.bit.REF_SEL = 0;//采用内部参考电压 一般默认如此
          // Specific clock setting for this example:
          EALLOW;
          SysCtrlRegs.HISPCP.all = ADC_MODCLK;        // HSPCLK = SYSCLKOUT/(2*ADC_MODCLK) =25Mhz//默认配置不用修改 ADC时钟频率不影响采样频率
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
  ```
  
  ### 其次看看触发作用的TIMER0，以配置ADC采样频率
  
  第一个参数是系统主频150MHz，不用改变
  
  第二个参数决定了TIM0触发频率，即1KHz
  
  ```C
  TIM0_Init(150,1000);//采用1KHz的采样频率
  ```
  
  TIM0内部如下（在学习笔记中讲述过）
  
  ```C
  void TIM0_Init(float Freq, float Period)
  {
          EALLOW;
          SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
          EDIS;
  
          EALLOW;
          PieVectTable.TINT0 = &TIM0_IRQn;
          EDIS;
  
  
          // CPU Timer 0
          // Initialize address pointers to respective timer registers:
          CpuTimer0.RegsAddr = &CpuTimer0Regs;
          // Initialize timer period to maximum:
          CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
          // Initialize pre-scale counter to divide by 1 (SYSCLKOUT):
          CpuTimer0Regs.TPR.all  = 0;
          CpuTimer0Regs.TPRH.all = 0;
          // Make sure timer is stopped:
          CpuTimer0Regs.TCR.bit.TSS = 1;
          // Reload all counter register with period value:
          CpuTimer0Regs.TCR.bit.TRB = 1;
          // Reset interrupt counters:
          CpuTimer0.InterruptCount = 0;
  
          ConfigCpuTimer(&CpuTimer0, Freq, Period);
  
          CpuTimer0Regs.TCR.bit.TSS=0;
  
          IER |= M_INT1;
  
          PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
  
          EINT;
          ERTM;
  
  }
  ```
  
  最重要的还是中断配置，软件启动ADC
  
  SOC应该是start of conversion
  
  ```C
  interrupt void TIM0_IRQn(void)
  {
          EALLOW;
          LED1_TOGGLE;
          PieCtrlRegs.PIEACK.bit.ACK1=1;
          EDIS;
          AdcRegs.ADCTRL2.bit.SOC_SEQ1=1; // 软件置位启动ADC
  /*
          PieCtrlRegs.PIEACK.all =  PIEACK_GROUP1;
          CpuTimer0Regs.TCR.bit.TIF=1;
          CpuTimer0Regs.TCR.bit.TRB=1;
  */
  
  }
  ```
  
  在主函数的读取中，也要及时清除中断标志
  
  ```C
  Uint16 Read_ADCValue(void)
  {
          while (AdcRegs.ADCST.bit.INT_SEQ1== 0); 
          AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1; //清楚中断
          return AdcRegs.ADCRESULT0>>4;
  }
  ```
  
  最后我们看看主函数
  
  float adc_voll; float adc_vlos[200];
  
  这两个用来观测
  
  ```C
  #include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
  #include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
  
  #include "leds.h"
  #include "time.h"
  #include "smg.h"
  #include "adc.h"
  
  float adc_voll;
  float adc_vlos[200];
  
  /*******************************************************************************
  * 函 数 名         : main
  * 函数功能                   : 主函数
  * 输    入         : 无
  * 输    出         : 无
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
          //TIM0_Init(150,200000);//200ms(150MHz为时钟SYSCLKOUT 也就是150MHz，不需要改，后面 的参数Y 为定时器周期，单位us 2000000us=200ms 这是TI官方函数设定的)
          TIM0_Init(150,1000);//采用1KHz的采样频率
          SMG_Init();
          ADC_Init();
  
          while(1)
          {
  /*            while (AdcRegs.ADCST.bit.INT_SEQ1 == 0){}
  
              AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
              { */
              adc_voll=(float)Read_ADCValue()*3.0/4096;
              SMG_DisplayFloat(adc_voll,2);
              adc_vlos[index++]=adc_voll;//存储，以供观测
              if(index>=200)
                  {
                      index=0;
                  }
  /*            }
  
  
          }*/
          }
  }
  ```
  
  [参考视频](https://www.bilibili.com/video/BV18h411B7Fz/?p=20&spm_id_from=333.1296.top_right_bar_window_history.content.click&vd_source=f55e9b0a7c1da847b04085ba57aed552)（顾老师的最后一讲）
  