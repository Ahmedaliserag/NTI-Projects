################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Services/PORT/subdir.mk
-include OS/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMERS/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/MotorDriver/subdir.mk
-include HAL/CANMCB/subdir.mk
-include APP/control/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
CarControl.lss \

FLASH_IMAGE += \
CarControl.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: CarControl.elf secondary-outputs

# Tool invocations
CarControl.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CarControl.map -mmcu=atmega128 -o "CarControl.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CarControl.lss: CarControl.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CarControl.elf  >"CarControl.lss"
	@echo 'Finished building: $@'
	@echo ' '

CarControl.hex: CarControl.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex CarControl.elf  "CarControl.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CarControl.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 CarControl.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) CarControl.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
