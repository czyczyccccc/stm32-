################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/beep.c \
../Drivers/BSP/esp8266.c \
../Drivers/BSP/rc522.c 

OBJS += \
./Drivers/BSP/beep.o \
./Drivers/BSP/esp8266.o \
./Drivers/BSP/rc522.o 

C_DEPS += \
./Drivers/BSP/beep.d \
./Drivers/BSP/esp8266.d \
./Drivers/BSP/rc522.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/stmcubeide/code/free/Drivers/icode" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/beep.d ./Drivers/BSP/beep.o ./Drivers/BSP/beep.su ./Drivers/BSP/esp8266.d ./Drivers/BSP/esp8266.o ./Drivers/BSP/esp8266.su ./Drivers/BSP/rc522.d ./Drivers/BSP/rc522.o ./Drivers/BSP/rc522.su

.PHONY: clean-Drivers-2f-BSP

