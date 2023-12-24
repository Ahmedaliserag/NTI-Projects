################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP_LAYER/Emer_Break/Emer_Break.c 

OBJS += \
./APP_LAYER/Emer_Break/Emer_Break.o 

C_DEPS += \
./APP_LAYER/Emer_Break/Emer_Break.d 


# Each subdirectory must supply rules for building sources it contributes
APP_LAYER/Emer_Break/%.o: ../APP_LAYER/Emer_Break/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


