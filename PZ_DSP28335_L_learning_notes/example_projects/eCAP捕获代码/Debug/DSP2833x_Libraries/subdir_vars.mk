################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../DSP2833x_Libraries/28335_RAM_lnk.cmd \
../DSP2833x_Libraries/DSP2833x_Headers_nonBIOS.cmd 

LIB_SRCS += \
../DSP2833x_Libraries/IQmath.lib 

ASM_SRCS += \
../DSP2833x_Libraries/DSP2833x_ADC_cal.asm \
../DSP2833x_Libraries/DSP2833x_CodeStartBranch.asm \
../DSP2833x_Libraries/DSP2833x_usDelay.asm 

C_SRCS += \
../DSP2833x_Libraries/DSP2833x_Adc.c \
../DSP2833x_Libraries/DSP2833x_CpuTimers.c \
../DSP2833x_Libraries/DSP2833x_DMA.c \
../DSP2833x_Libraries/DSP2833x_DefaultIsr.c \
../DSP2833x_Libraries/DSP2833x_ECap.c \
../DSP2833x_Libraries/DSP2833x_EPwm.c \
../DSP2833x_Libraries/DSP2833x_GlobalVariableDefs.c \
../DSP2833x_Libraries/DSP2833x_Gpio.c \
../DSP2833x_Libraries/DSP2833x_PieCtrl.c \
../DSP2833x_Libraries/DSP2833x_PieVect.c \
../DSP2833x_Libraries/DSP2833x_Sci.c \
../DSP2833x_Libraries/DSP2833x_Spi.c \
../DSP2833x_Libraries/DSP2833x_SysCtrl.c \
../DSP2833x_Libraries/DSP2833x_Xintf.c 

C_DEPS += \
./DSP2833x_Libraries/DSP2833x_Adc.d \
./DSP2833x_Libraries/DSP2833x_CpuTimers.d \
./DSP2833x_Libraries/DSP2833x_DMA.d \
./DSP2833x_Libraries/DSP2833x_DefaultIsr.d \
./DSP2833x_Libraries/DSP2833x_ECap.d \
./DSP2833x_Libraries/DSP2833x_EPwm.d \
./DSP2833x_Libraries/DSP2833x_GlobalVariableDefs.d \
./DSP2833x_Libraries/DSP2833x_Gpio.d \
./DSP2833x_Libraries/DSP2833x_PieCtrl.d \
./DSP2833x_Libraries/DSP2833x_PieVect.d \
./DSP2833x_Libraries/DSP2833x_Sci.d \
./DSP2833x_Libraries/DSP2833x_Spi.d \
./DSP2833x_Libraries/DSP2833x_SysCtrl.d \
./DSP2833x_Libraries/DSP2833x_Xintf.d 

OBJS += \
./DSP2833x_Libraries/DSP2833x_ADC_cal.obj \
./DSP2833x_Libraries/DSP2833x_Adc.obj \
./DSP2833x_Libraries/DSP2833x_CodeStartBranch.obj \
./DSP2833x_Libraries/DSP2833x_CpuTimers.obj \
./DSP2833x_Libraries/DSP2833x_DMA.obj \
./DSP2833x_Libraries/DSP2833x_DefaultIsr.obj \
./DSP2833x_Libraries/DSP2833x_ECap.obj \
./DSP2833x_Libraries/DSP2833x_EPwm.obj \
./DSP2833x_Libraries/DSP2833x_GlobalVariableDefs.obj \
./DSP2833x_Libraries/DSP2833x_Gpio.obj \
./DSP2833x_Libraries/DSP2833x_PieCtrl.obj \
./DSP2833x_Libraries/DSP2833x_PieVect.obj \
./DSP2833x_Libraries/DSP2833x_Sci.obj \
./DSP2833x_Libraries/DSP2833x_Spi.obj \
./DSP2833x_Libraries/DSP2833x_SysCtrl.obj \
./DSP2833x_Libraries/DSP2833x_Xintf.obj \
./DSP2833x_Libraries/DSP2833x_usDelay.obj 

ASM_DEPS += \
./DSP2833x_Libraries/DSP2833x_ADC_cal.d \
./DSP2833x_Libraries/DSP2833x_CodeStartBranch.d \
./DSP2833x_Libraries/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"DSP2833x_Libraries\DSP2833x_ADC_cal.obj" \
"DSP2833x_Libraries\DSP2833x_Adc.obj" \
"DSP2833x_Libraries\DSP2833x_CodeStartBranch.obj" \
"DSP2833x_Libraries\DSP2833x_CpuTimers.obj" \
"DSP2833x_Libraries\DSP2833x_DMA.obj" \
"DSP2833x_Libraries\DSP2833x_DefaultIsr.obj" \
"DSP2833x_Libraries\DSP2833x_ECap.obj" \
"DSP2833x_Libraries\DSP2833x_EPwm.obj" \
"DSP2833x_Libraries\DSP2833x_GlobalVariableDefs.obj" \
"DSP2833x_Libraries\DSP2833x_Gpio.obj" \
"DSP2833x_Libraries\DSP2833x_PieCtrl.obj" \
"DSP2833x_Libraries\DSP2833x_PieVect.obj" \
"DSP2833x_Libraries\DSP2833x_Sci.obj" \
"DSP2833x_Libraries\DSP2833x_Spi.obj" \
"DSP2833x_Libraries\DSP2833x_SysCtrl.obj" \
"DSP2833x_Libraries\DSP2833x_Xintf.obj" \
"DSP2833x_Libraries\DSP2833x_usDelay.obj" 

C_DEPS__QUOTED += \
"DSP2833x_Libraries\DSP2833x_Adc.d" \
"DSP2833x_Libraries\DSP2833x_CpuTimers.d" \
"DSP2833x_Libraries\DSP2833x_DMA.d" \
"DSP2833x_Libraries\DSP2833x_DefaultIsr.d" \
"DSP2833x_Libraries\DSP2833x_ECap.d" \
"DSP2833x_Libraries\DSP2833x_EPwm.d" \
"DSP2833x_Libraries\DSP2833x_GlobalVariableDefs.d" \
"DSP2833x_Libraries\DSP2833x_Gpio.d" \
"DSP2833x_Libraries\DSP2833x_PieCtrl.d" \
"DSP2833x_Libraries\DSP2833x_PieVect.d" \
"DSP2833x_Libraries\DSP2833x_Sci.d" \
"DSP2833x_Libraries\DSP2833x_Spi.d" \
"DSP2833x_Libraries\DSP2833x_SysCtrl.d" \
"DSP2833x_Libraries\DSP2833x_Xintf.d" 

ASM_DEPS__QUOTED += \
"DSP2833x_Libraries\DSP2833x_ADC_cal.d" \
"DSP2833x_Libraries\DSP2833x_CodeStartBranch.d" \
"DSP2833x_Libraries\DSP2833x_usDelay.d" 

ASM_SRCS__QUOTED += \
"../DSP2833x_Libraries/DSP2833x_ADC_cal.asm" \
"../DSP2833x_Libraries/DSP2833x_CodeStartBranch.asm" \
"../DSP2833x_Libraries/DSP2833x_usDelay.asm" 

C_SRCS__QUOTED += \
"../DSP2833x_Libraries/DSP2833x_Adc.c" \
"../DSP2833x_Libraries/DSP2833x_CpuTimers.c" \
"../DSP2833x_Libraries/DSP2833x_DMA.c" \
"../DSP2833x_Libraries/DSP2833x_DefaultIsr.c" \
"../DSP2833x_Libraries/DSP2833x_ECap.c" \
"../DSP2833x_Libraries/DSP2833x_EPwm.c" \
"../DSP2833x_Libraries/DSP2833x_GlobalVariableDefs.c" \
"../DSP2833x_Libraries/DSP2833x_Gpio.c" \
"../DSP2833x_Libraries/DSP2833x_PieCtrl.c" \
"../DSP2833x_Libraries/DSP2833x_PieVect.c" \
"../DSP2833x_Libraries/DSP2833x_Sci.c" \
"../DSP2833x_Libraries/DSP2833x_Spi.c" \
"../DSP2833x_Libraries/DSP2833x_SysCtrl.c" \
"../DSP2833x_Libraries/DSP2833x_Xintf.c" 


