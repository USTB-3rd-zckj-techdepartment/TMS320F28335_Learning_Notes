################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
APP/leds/%.obj: ../APP/leds/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example16_DSP2833x_Epwm_updown_AQ/Example16_DSP2833x_Epwm_updown_AQ/APP/time" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example16_DSP2833x_Epwm_updown_AQ/Example16_DSP2833x_Epwm_updown_AQ/APP/epwm" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_common/include" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Example/Example16_DSP2833x_Epwm_updown_AQ/Example16_DSP2833x_Epwm_updown_AQ/APP/leds" --include_path="E:/TMS320F28335/DSP8233x_ProjectExample/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="APP/leds/$(basename $(<F)).d_raw" --obj_directory="APP/leds" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


