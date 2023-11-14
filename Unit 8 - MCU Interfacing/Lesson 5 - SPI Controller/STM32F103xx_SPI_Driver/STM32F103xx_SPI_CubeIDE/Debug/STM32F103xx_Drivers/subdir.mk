################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103xx_Drivers/STM32F103C6T6_EXTI_Driver.c \
../STM32F103xx_Drivers/STM32F103C6T6_GPIO_Driver.c \
../STM32F103xx_Drivers/STM32F103C6T6_RCC_Driver.c \
../STM32F103xx_Drivers/STM32F103C6T6_SPI_Driver.c \
../STM32F103xx_Drivers/STM32F103C6T6_UART_Driver.c 

OBJS += \
./STM32F103xx_Drivers/STM32F103C6T6_EXTI_Driver.o \
./STM32F103xx_Drivers/STM32F103C6T6_GPIO_Driver.o \
./STM32F103xx_Drivers/STM32F103C6T6_RCC_Driver.o \
./STM32F103xx_Drivers/STM32F103C6T6_SPI_Driver.o \
./STM32F103xx_Drivers/STM32F103C6T6_UART_Driver.o 

C_DEPS += \
./STM32F103xx_Drivers/STM32F103C6T6_EXTI_Driver.d \
./STM32F103xx_Drivers/STM32F103C6T6_GPIO_Driver.d \
./STM32F103xx_Drivers/STM32F103C6T6_RCC_Driver.d \
./STM32F103xx_Drivers/STM32F103C6T6_SPI_Driver.d \
./STM32F103xx_Drivers/STM32F103C6T6_UART_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103xx_Drivers/%.o STM32F103xx_Drivers/%.su: ../STM32F103xx_Drivers/%.c STM32F103xx_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Mostafa/C and Embedded/Embedded Systems Diploma KS/Unit 8 - MCU Interfacing/Lesson 5/Assignments/STM32F103xx_SPI_Driver/STM32F103xx_SPI_CubeIDE/STM32F103xx_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32F103xx_Drivers

clean-STM32F103xx_Drivers:
	-$(RM) ./STM32F103xx_Drivers/STM32F103C6T6_EXTI_Driver.d ./STM32F103xx_Drivers/STM32F103C6T6_EXTI_Driver.o ./STM32F103xx_Drivers/STM32F103C6T6_EXTI_Driver.su ./STM32F103xx_Drivers/STM32F103C6T6_GPIO_Driver.d ./STM32F103xx_Drivers/STM32F103C6T6_GPIO_Driver.o ./STM32F103xx_Drivers/STM32F103C6T6_GPIO_Driver.su ./STM32F103xx_Drivers/STM32F103C6T6_RCC_Driver.d ./STM32F103xx_Drivers/STM32F103C6T6_RCC_Driver.o ./STM32F103xx_Drivers/STM32F103C6T6_RCC_Driver.su ./STM32F103xx_Drivers/STM32F103C6T6_SPI_Driver.d ./STM32F103xx_Drivers/STM32F103C6T6_SPI_Driver.o ./STM32F103xx_Drivers/STM32F103C6T6_SPI_Driver.su ./STM32F103xx_Drivers/STM32F103C6T6_UART_Driver.d ./STM32F103xx_Drivers/STM32F103C6T6_UART_Driver.o ./STM32F103xx_Drivers/STM32F103C6T6_UART_Driver.su

.PHONY: clean-STM32F103xx_Drivers

