################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GI/GI_Program.c 

OBJS += \
./MCAL/GI/GI_Program.o 

C_DEPS += \
./MCAL/GI/GI_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GI/%.o: ../MCAL/GI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Softlaptop\Desktop\ATMega128_control" -I"C:\Users\Softlaptop\Desktop\ATMega128_control" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


