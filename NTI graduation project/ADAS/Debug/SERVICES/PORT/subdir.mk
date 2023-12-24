################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERVICES/PORT/Port.c \
../SERVICES/PORT/Port_Cfg.c 

OBJS += \
./SERVICES/PORT/Port.o \
./SERVICES/PORT/Port_Cfg.o 

C_DEPS += \
./SERVICES/PORT/Port.d \
./SERVICES/PORT/Port_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
SERVICES/PORT/%.o: ../SERVICES/PORT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


