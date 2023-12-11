################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/src/delayAntibloqueo.c \
../src/lib/src/eboard.c \
../src/lib/src/eringbuffer.c \
../src/lib/src/euart.c 

OBJS += \
./src/lib/src/delayAntibloqueo.o \
./src/lib/src/eboard.o \
./src/lib/src/eringbuffer.o \
./src/lib/src/euart.o 

C_DEPS += \
./src/lib/src/delayAntibloqueo.d \
./src/lib/src/eboard.d \
./src/lib/src/eringbuffer.d \
./src/lib/src/euart.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/src/%.o src/lib/src/%.su src/lib/src/%.cyclo: ../src/lib/src/%.c src/lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/src/app/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/src/hal/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/src/lib/inc" -I"D:/Especialidad sistemas embebidos UBA/RTOS (II)/TPfinal/Tp3/Supporting_Functions/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-lib-2f-src

clean-src-2f-lib-2f-src:
	-$(RM) ./src/lib/src/delayAntibloqueo.cyclo ./src/lib/src/delayAntibloqueo.d ./src/lib/src/delayAntibloqueo.o ./src/lib/src/delayAntibloqueo.su ./src/lib/src/eboard.cyclo ./src/lib/src/eboard.d ./src/lib/src/eboard.o ./src/lib/src/eboard.su ./src/lib/src/eringbuffer.cyclo ./src/lib/src/eringbuffer.d ./src/lib/src/eringbuffer.o ./src/lib/src/eringbuffer.su ./src/lib/src/euart.cyclo ./src/lib/src/euart.d ./src/lib/src/euart.o ./src/lib/src/euart.su

.PHONY: clean-src-2f-lib-2f-src

