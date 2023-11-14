################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Atmega32_Drivers/SPI.c 

OBJS += \
./Atmega32_Drivers/SPI.o 

C_DEPS += \
./Atmega32_Drivers/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Atmega32_Drivers/%.o: ../Atmega32_Drivers/%.c Atmega32_Drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Mostafa\C and Embedded\Embedded Systems Diploma KS\Unit 8 - MCU Interfacing\Lesson 4\Assignments\Atmega32_SPI_Driver\Atmega32_SPI_Eclipse\Atmega32_Drivers\inc" -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


