################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TemperatureMonitoring.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc8xx.cpp \
../src/delay.cpp \
../src/display.cpp \
../src/swm.cpp \
../src/tm.cpp 

C_SRCS += \
../src/crp.c \
../src/i2c.c \
../src/mtb.c \
../src/sysinit.c 

OBJS += \
./src/TemperatureMonitoring.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc8xx.o \
./src/crp.o \
./src/delay.o \
./src/display.o \
./src/i2c.o \
./src/mtb.o \
./src/swm.o \
./src/sysinit.o \
./src/tm.o 

CPP_DEPS += \
./src/TemperatureMonitoring.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc8xx.d \
./src/delay.d \
./src/display.d \
./src/swm.d \
./src/tm.d 

C_DEPS += \
./src/crp.d \
./src/i2c.d \
./src/mtb.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM0 -DCPP_USE_HEAP -D__LPC8XX__ -I"/mnt/hgfs/P/LPCXpresso/workspace/SQAT_embedded_TM/inc" -I"/mnt/hgfs/P/LPCXpresso/workspace/lpc_chip_8xx/inc" -I"/mnt/hgfs/P/LPCXpresso/workspace/CMSIS_DSPLIB_CM0/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM0 -DCPP_USE_HEAP -D__LPC8XX__ -I"/mnt/hgfs/P/LPCXpresso/workspace/SQAT_embedded_TM/inc" -I"/mnt/hgfs/P/LPCXpresso/workspace/lpc_chip_8xx/inc" -I"/mnt/hgfs/P/LPCXpresso/workspace/CMSIS_DSPLIB_CM0/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


