################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := LED_Blinking_Stm32f103c6t6
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LED_Blinking_Stm32f103c6t6.elf \

MAP_FILES += \
LED_Blinking_Stm32f103c6t6.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LED_Blinking_Stm32f103c6t6.list \

OBJCOPY_HEX += \
LED_Blinking_Stm32f103c6t6.hex \

OBJCOPY_BIN += \
LED_Blinking_Stm32f103c6t6.bin \


# All Target
all: main-build

# Main-build Target
main-build: LED_Blinking_Stm32f103c6t6.elf secondary-outputs

# Tool invocations
LED_Blinking_Stm32f103c6t6.elf LED_Blinking_Stm32f103c6t6.map: $(OBJS) $(USER_OBJS) D:\Mostafa\C\ and\ Embedded\Embedded\ Systems\ Diploma\ KS\Unit\ 3\ -\ Embedded\ C\Lesson\ 1\Assignement\LED\ Blinking\LED_Blinking_Stm32f103c6t6\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "LED_Blinking_Stm32f103c6t6.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Mostafa\C and Embedded\Embedded Systems Diploma KS\Unit 3 - Embedded C\Lesson 1\Assignement\LED Blinking\LED_Blinking_Stm32f103c6t6\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LED_Blinking_Stm32f103c6t6.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LED_Blinking_Stm32f103c6t6.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LED_Blinking_Stm32f103c6t6.list"
	@echo 'Finished building: $@'
	@echo ' '

LED_Blinking_Stm32f103c6t6.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "LED_Blinking_Stm32f103c6t6.hex"
	@echo 'Finished building: $@'
	@echo ' '

LED_Blinking_Stm32f103c6t6.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "LED_Blinking_Stm32f103c6t6.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) LED_Blinking_Stm32f103c6t6.bin LED_Blinking_Stm32f103c6t6.elf LED_Blinking_Stm32f103c6t6.hex LED_Blinking_Stm32f103c6t6.list LED_Blinking_Stm32f103c6t6.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
