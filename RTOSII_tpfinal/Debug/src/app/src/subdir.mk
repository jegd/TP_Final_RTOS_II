################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/src/app.c \
../src/app/src/driver_uart.c 

OBJS += \
./src/app/src/app.o \
./src/app/src/driver_uart.o 

C_DEPS += \
./src/app/src/app.d \
./src/app/src/driver_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/src/%.o src/app/src/%.su src/app/src/%.cyclo: ../src/app/src/%.c src/app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../App/Inc -I../Supporting_Functions/Inc -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/RTOSII_tpfinal/src/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-app-2f-src

clean-src-2f-app-2f-src:
	-$(RM) ./src/app/src/app.cyclo ./src/app/src/app.d ./src/app/src/app.o ./src/app/src/app.su ./src/app/src/driver_uart.cyclo ./src/app/src/driver_uart.d ./src/app/src/driver_uart.o ./src/app/src/driver_uart.su

.PHONY: clean-src-2f-app-2f-src

