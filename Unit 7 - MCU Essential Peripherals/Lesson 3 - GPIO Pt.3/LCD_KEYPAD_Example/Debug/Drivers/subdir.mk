################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Keypad.c \
../Drivers/LCD.c \
../Drivers/STM32F103C8T6_GPIO_Driver.c 

OBJS += \
./Drivers/Keypad.o \
./Drivers/LCD.o \
./Drivers/STM32F103C8T6_GPIO_Driver.o 

C_DEPS += \
./Drivers/Keypad.d \
./Drivers/LCD.d \
./Drivers/STM32F103C8T6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o Drivers/%.su: ../Drivers/%.c Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Mostafa/C and Embedded/Embedded Systems Diploma KS/Unit 7 - MCU Essential Peripherals/Lesson 3/Assignment/STM32F103C6T6_LCD_KEYPAD/Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/Keypad.d ./Drivers/Keypad.o ./Drivers/Keypad.su ./Drivers/LCD.d ./Drivers/LCD.o ./Drivers/LCD.su ./Drivers/STM32F103C8T6_GPIO_Driver.d ./Drivers/STM32F103C8T6_GPIO_Driver.o ./Drivers/STM32F103C8T6_GPIO_Driver.su

.PHONY: clean-Drivers

