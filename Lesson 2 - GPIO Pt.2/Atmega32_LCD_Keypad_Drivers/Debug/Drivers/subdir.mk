################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Keypad.c \
../Drivers/LCD.c 

OBJS += \
./Drivers/Keypad.o \
./Drivers/LCD.o 

C_DEPS += \
./Drivers/Keypad.d \
./Drivers/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c Drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Mostafa\C and Embedded\Embedded Systems Diploma KS\Unit 7 - MCU Essential Peripherals\Lesson 2\Assignment\Atmega32_LCD_Keypad_Drivers\Drivers\inc" -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


