################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
APP/exti/exti.obj: ../APP/exti/exti.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example10_DSP2833x_Time0/APP/time" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example14_DSP2833x_Epwm_Time_Interrupt/APP/epwm" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example13_DSP2833x_8Seg/APP/smg" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example05_DSP2833x_Relay/APP/relay" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example09_DSP2833x_External_Interruption/APP/exti" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example08_DSP2833x_Step_Motor/APP/step_motor" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example07_DSP2833x_DC_Motor/APP/dc_motor" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example06_DSP2833x_Key/APP/key" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_common/include" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example04_DSP2833x_BEEP/APP/beep" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Example/Example02_DSP2833x_LED/APP/leds" --include_path="E:/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="APP/exti/exti.d" --obj_directory="APP/exti" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


