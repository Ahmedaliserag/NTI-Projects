################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SERVICES/PORT/subdir.mk
-include OS/subdir.mk
-include MCAL/TMR1/subdir.mk
-include MCAL/TMR0/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/UltraSonic/subdir.mk
-include HAL/Sensor/subdir.mk
-include HAL/MCP/subdir.mk
-include APP_LAYER/Lane_Keep/subdir.mk
-include APP_LAYER/Emer_Break/subdir.mk
-include APP_LAYER/Distance_ReadStart/subdir.mk
-include APP_LAYER/CAN_Communication/subdir.mk
-include APP_LAYER/ACC_Ctrl/subdir.mk
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
ADAS.lss \

FLASH_IMAGE += \
ADAS.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: ADAS.elf secondary-outputs

# Tool invocations
ADAS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ADAS.map -mmcu=atmega128 -o "ADAS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ADAS.lss: ADAS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ADAS.elf  >"ADAS.lss"
	@echo 'Finished building: $@'
	@echo ' '

ADAS.hex: ADAS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ADAS.elf  "ADAS.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ADAS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 ADAS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ADAS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
