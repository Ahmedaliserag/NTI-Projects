################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Services/PORT/Port.c \
../Services/PORT/Port_Cfg.c 

OBJS += \
./Services/PORT/Port.o \
./Services/PORT/Port_Cfg.o 

C_DEPS += \
./Services/PORT/Port.d \
./Services/PORT/Port_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Services/PORT/%.o: ../Services/PORT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


