################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app.c \
../Core/Src/ball.c \
../Core/Src/connect.c \
../Core/Src/delay.c \
../Core/Src/gameLogic.c \
../Core/Src/lcd.c \
../Core/Src/lcd_pins.c \
../Core/Src/main.c \
../Core/Src/maps.c \
../Core/Src/mpu6050.c \
../Core/Src/procudure.c \
../Core/Src/score.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/timer.c 

OBJS += \
./Core/Src/app.o \
./Core/Src/ball.o \
./Core/Src/connect.o \
./Core/Src/delay.o \
./Core/Src/gameLogic.o \
./Core/Src/lcd.o \
./Core/Src/lcd_pins.o \
./Core/Src/main.o \
./Core/Src/maps.o \
./Core/Src/mpu6050.o \
./Core/Src/procudure.o \
./Core/Src/score.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/timer.o 

C_DEPS += \
./Core/Src/app.d \
./Core/Src/ball.d \
./Core/Src/connect.d \
./Core/Src/delay.d \
./Core/Src/gameLogic.d \
./Core/Src/lcd.d \
./Core/Src/lcd_pins.d \
./Core/Src/main.d \
./Core/Src/maps.d \
./Core/Src/mpu6050.d \
./Core/Src/procudure.d \
./Core/Src/score.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

