################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/PORT/Port.c \
../MCAL/PORT/Port_Cfg.c 

OBJS += \
./MCAL/PORT/Port.o \
./MCAL/PORT/Port_Cfg.o 

C_DEPS += \
./MCAL/PORT/Port.d \
./MCAL/PORT/Port_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PORT/%.o: ../MCAL/PORT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Softlaptop\Desktop\ATMega128_control" -I"C:\Users\Softlaptop\Desktop\ATMega128_control" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


