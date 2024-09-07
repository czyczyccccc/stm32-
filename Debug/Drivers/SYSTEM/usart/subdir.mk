################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SYSTEM/usart/usart.c 

OBJS += \
./Drivers/SYSTEM/usart/usart.o 

C_DEPS += \
./Drivers/SYSTEM/usart/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SYSTEM/usart/%.o Drivers/SYSTEM/usart/%.su: ../Drivers/SYSTEM/usart/%.c Drivers/SYSTEM/usart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/stmcubeide/code/free/Drivers/icode" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-SYSTEM-2f-usart

clean-Drivers-2f-SYSTEM-2f-usart:
	-$(RM) ./Drivers/SYSTEM/usart/usart.d ./Drivers/SYSTEM/usart/usart.o ./Drivers/SYSTEM/usart/usart.su

.PHONY: clean-Drivers-2f-SYSTEM-2f-usart

