################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./APP/epwm/epwm.obj" \
"./APP/leds/leds.obj" \
"./APP/time/time.obj" \
"./DSP2833x_Libraries/DSP2833x_ADC_cal.obj" \
"./DSP2833x_Libraries/DSP2833x_CodeStartBranch.obj" \
"./DSP2833x_Libraries/DSP2833x_CpuTimers.obj" \
"./DSP2833x_Libraries/DSP2833x_DefaultIsr.obj" \
"./DSP2833x_Libraries/DSP2833x_EPwm.obj" \
"./DSP2833x_Libraries/DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_Libraries/DSP2833x_Gpio.obj" \
"./DSP2833x_Libraries/DSP2833x_PieCtrl.obj" \
"./DSP2833x_Libraries/DSP2833x_PieVect.obj" \
"./DSP2833x_Libraries/DSP2833x_SysCtrl.obj" \
"./DSP2833x_Libraries/DSP2833x_usDelay.obj" \
"./User/main.obj" \
"../DSP2833x_Libraries/28335_RAM_lnk.cmd" \
"../DSP2833x_Libraries/DSP2833x_Headers_nonBIOS.cmd" \
"../DSP2833x_Libraries/IQmath.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include APP/epwm/subdir_vars.mk
-include APP/leds/subdir_vars.mk
-include APP/time/subdir_vars.mk
-include DSP2833x_Libraries/subdir_vars.mk
-include User/subdir_vars.mk
-include APP/epwm/subdir_rules.mk
-include APP/leds/subdir_rules.mk
-include APP/time/subdir_rules.mk
-include DSP2833x_Libraries/subdir_rules.mk
-include User/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example16_DSP2833x_Epwm_updown_AQ.out \

EXE_OUTPUTS__QUOTED += \
"Example16_DSP2833x_Epwm_updown_AQ.out" \


# All Target
all: Example16_DSP2833x_Epwm_updown_AQ.out

# Tool invocations
Example16_DSP2833x_Epwm_updown_AQ.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"Example16_DSP2833x_Epwm_updown_AQ.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="Example16_DSP2833x_Epwm_updown_AQ_linkInfo.xml" --rom_model -o "Example16_DSP2833x_Epwm_updown_AQ.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "APP\epwm\epwm.obj" "APP\leds\leds.obj" "APP\time\time.obj" "DSP2833x_Libraries\DSP2833x_ADC_cal.obj" "DSP2833x_Libraries\DSP2833x_CodeStartBranch.obj" "DSP2833x_Libraries\DSP2833x_CpuTimers.obj" "DSP2833x_Libraries\DSP2833x_DefaultIsr.obj" "DSP2833x_Libraries\DSP2833x_EPwm.obj" "DSP2833x_Libraries\DSP2833x_GlobalVariableDefs.obj" "DSP2833x_Libraries\DSP2833x_Gpio.obj" "DSP2833x_Libraries\DSP2833x_PieCtrl.obj" "DSP2833x_Libraries\DSP2833x_PieVect.obj" "DSP2833x_Libraries\DSP2833x_SysCtrl.obj" "DSP2833x_Libraries\DSP2833x_usDelay.obj" "User\main.obj" 
	-$(RM) "APP\epwm\epwm.d" "APP\leds\leds.d" "APP\time\time.d" "DSP2833x_Libraries\DSP2833x_CpuTimers.d" "DSP2833x_Libraries\DSP2833x_DefaultIsr.d" "DSP2833x_Libraries\DSP2833x_EPwm.d" "DSP2833x_Libraries\DSP2833x_GlobalVariableDefs.d" "DSP2833x_Libraries\DSP2833x_Gpio.d" "DSP2833x_Libraries\DSP2833x_PieCtrl.d" "DSP2833x_Libraries\DSP2833x_PieVect.d" "DSP2833x_Libraries\DSP2833x_SysCtrl.d" "User\main.d" 
	-$(RM) "DSP2833x_Libraries\DSP2833x_ADC_cal.d" "DSP2833x_Libraries\DSP2833x_CodeStartBranch.d" "DSP2833x_Libraries\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

