################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6T6_Drivers/STM32F103C6T6_GPIO_Driver.c 

OBJS += \
./STM32F103C6T6_Drivers/STM32F103C6T6_GPIO_Driver.o 

C_DEPS += \
./STM32F103C6T6_Drivers/STM32F103C6T6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6T6_Drivers/%.o STM32F103C6T6_Drivers/%.su: ../STM32F103C6T6_Drivers/%.c STM32F103C6T6_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Mostafa/C and Embedded/Embedded Systems Diploma KS/Unit 7 - MCU Essential Peripherals/Lesson 3/Assignment/STM32F103C6T6_GPIO_DRIVER/STM32F103C6T6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32F103C6T6_Drivers

clean-STM32F103C6T6_Drivers:
	-$(RM) ./STM32F103C6T6_Drivers/STM32F103C6T6_GPIO_Driver.d ./STM32F103C6T6_Drivers/STM32F103C6T6_GPIO_Driver.o ./STM32F103C6T6_Drivers/STM32F103C6T6_GPIO_Driver.su

.PHONY: clean-STM32F103C6T6_Drivers

