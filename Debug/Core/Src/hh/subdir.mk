################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hh/main.c \
../Core/Src/hh/stm32f10x_it.c \
../Core/Src/hh/system_stm32f10x.c 

OBJS += \
./Core/Src/hh/main.o \
./Core/Src/hh/stm32f10x_it.o \
./Core/Src/hh/system_stm32f10x.o 

C_DEPS += \
./Core/Src/hh/main.d \
./Core/Src/hh/stm32f10x_it.d \
./Core/Src/hh/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/hh/%.o Core/Src/hh/%.su: ../Core/Src/hh/%.c Core/Src/hh/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-hh

clean-Core-2f-Src-2f-hh:
	-$(RM) ./Core/Src/hh/main.d ./Core/Src/hh/main.o ./Core/Src/hh/main.su ./Core/Src/hh/stm32f10x_it.d ./Core/Src/hh/stm32f10x_it.o ./Core/Src/hh/stm32f10x_it.su ./Core/Src/hh/system_stm32f10x.d ./Core/Src/hh/system_stm32f10x.o ./Core/Src/hh/system_stm32f10x.su

.PHONY: clean-Core-2f-Src-2f-hh

