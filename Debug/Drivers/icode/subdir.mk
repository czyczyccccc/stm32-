################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/icode/oled.c \
../Drivers/icode/oledfont.c 

OBJS += \
./Drivers/icode/oled.o \
./Drivers/icode/oledfont.o 

C_DEPS += \
./Drivers/icode/oled.d \
./Drivers/icode/oledfont.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/icode/%.o Drivers/icode/%.su: ../Drivers/icode/%.c Drivers/icode/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/stmcubeide/code/free/Drivers/icode" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-icode

clean-Drivers-2f-icode:
	-$(RM) ./Drivers/icode/oled.d ./Drivers/icode/oled.o ./Drivers/icode/oled.su ./Drivers/icode/oledfont.d ./Drivers/icode/oledfont.o ./Drivers/icode/oledfont.su

.PHONY: clean-Drivers-2f-icode

