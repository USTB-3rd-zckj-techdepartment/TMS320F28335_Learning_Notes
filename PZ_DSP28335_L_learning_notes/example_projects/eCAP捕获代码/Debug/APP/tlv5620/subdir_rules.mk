################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
APP/tlv5620/tlv5620.obj: ../APP/tlv5620/tlv5620.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.2.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example20_DSP2833x_ADC_seqmode/APP/adc" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example35_DSP2833x_ADC-DMA/APP/dma" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example33_DSP2833x_DAC/APP/tlv5620" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example32_DSP2833x_LCD12864/APP/lcd12864" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example31_DSP2833x_LCD1602/APP/lcd1602" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example30_DSP2833x_IIC_eeprom/APP/iic" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example30_DSP2833x_IIC_eeprom/APP/24cxx" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example29_DSP2833x_SPI_secwatch/APP/secwatch" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example26_DSP2833x_SPI_loopback/APP/spi" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example23_DSP2833x_SCI_loopback/APP/uart" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example10_DSP2833x_Time0/APP/time" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example14_DSP2833x_Epwm_Time_Interrupt/APP/epwm" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example13_DSP2833x_8Seg/APP/smg" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example05_DSP2833x_Relay/APP/relay" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example09_DSP2833x_External_Interruption/APP/exti" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example08_DSP2833x_Step_Motor/APP/step_motor" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example07_DSP2833x_DC_Motor/APP/dc_motor" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example06_DSP2833x_Key/APP/key" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_common/include" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example04_DSP2833x_BEEP/APP/beep" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example02_DSP2833x_LED/APP/leds" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.2.0/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="APP/tlv5620/tlv5620.pp" --obj_directory="APP/tlv5620" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


