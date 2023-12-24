################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP_LAYER/Lane_Keep/Lane_Keep.c 

OBJS += \
./APP_LAYER/Lane_Keep/Lane_Keep.o 

C_DEPS += \
./APP_LAYER/Lane_Keep/Lane_Keep.d 


# Each subdirectory must supply rules for building sources it contributes
APP_LAYER/Lane_Keep/%.o: ../APP_LAYER/Lane_Keep/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


