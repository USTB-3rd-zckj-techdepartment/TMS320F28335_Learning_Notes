################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2833x_Libraries/%.obj: ../DSP2833x_Libraries/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/ecap" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/epwm" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/uart" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/time" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_common/include" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/leds" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_Libraries/$(basename $(<F)).d_raw" --obj_directory="DSP2833x_Libraries" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DSP2833x_Libraries/%.obj: ../DSP2833x_Libraries/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/ecap" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/epwm" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/uart" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/time" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_common/include" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example39_DSP2833x_eCAP_Capture_pwm/Example39_DSP2833x_eCAP_Capture_pwm/APP/leds" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="DSP2833x_Libraries/$(basename $(<F)).d_raw" --obj_directory="DSP2833x_Libraries" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


