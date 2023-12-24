################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TMR0/TMR0_Program.c 

OBJS += \
./MCAL/TMR0/TMR0_Program.o 

C_DEPS += \
./MCAL/TMR0/TMR0_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TMR0/%.o: ../MCAL/TMR0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Softlaptop\Desktop\ATMega128_control" -I"C:\Users\Softlaptop\Desktop\ATMega128_control" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


