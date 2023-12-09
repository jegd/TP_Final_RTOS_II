################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src2/app/src/app.c \
../src2/app/src/driver_i2c1.c \
../src2/app/src/driver_lcd.c 

OBJS += \
./src2/app/src/app.o \
./src2/app/src/driver_i2c1.o \
./src2/app/src/driver_lcd.o 

C_DEPS += \
./src2/app/src/app.d \
./src2/app/src/driver_i2c1.d \
./src2/app/src/driver_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
src2/app/src/%.o src2/app/src/%.su src2/app/src/%.cyclo: ../src2/app/src/%.c src2/app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../App/Inc -I../Supporting_Functions/Inc -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/RTOSII_tpfinal/src2/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/RTOSII_tpfinal/src2/hal/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/RTOSII_tpfinal/src2/lib/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src2-2f-app-2f-src

clean-src2-2f-app-2f-src:
	-$(RM) ./src2/app/src/app.cyclo ./src2/app/src/app.d ./src2/app/src/app.o ./src2/app/src/app.su ./src2/app/src/driver_i2c1.cyclo ./src2/app/src/driver_i2c1.d ./src2/app/src/driver_i2c1.o ./src2/app/src/driver_i2c1.su ./src2/app/src/driver_lcd.cyclo ./src2/app/src/driver_lcd.d ./src2/app/src/driver_lcd.o ./src2/app/src/driver_lcd.su

.PHONY: clean-src2-2f-app-2f-src

