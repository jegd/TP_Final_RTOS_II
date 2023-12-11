################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/src/RGB.c \
../src/app/src/app.c 

OBJS += \
./src/app/src/RGB.o \
./src/app/src/app.o 

C_DEPS += \
./src/app/src/RGB.d \
./src/app/src/app.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/src/%.o src/app/src/%.su src/app/src/%.cyclo: ../src/app/src/%.c src/app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/src/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/src/hal/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/src/lib/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/Supporting_Functions/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-app-2f-src

clean-src-2f-app-2f-src:
	-$(RM) ./src/app/src/RGB.cyclo ./src/app/src/RGB.d ./src/app/src/RGB.o ./src/app/src/RGB.su ./src/app/src/app.cyclo ./src/app/src/app.d ./src/app/src/app.o ./src/app/src/app.su

.PHONY: clean-src-2f-app-2f-src

