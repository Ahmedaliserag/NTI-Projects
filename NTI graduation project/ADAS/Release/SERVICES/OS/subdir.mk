################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SERVICES/OS/OS.c \
../SERVICES/OS/OS_Config.c \
../SERVICES/OS/Tasks.c 

OBJS += \
./SERVICES/OS/OS.o \
./SERVICES/OS/OS_Config.o \
./SERVICES/OS/Tasks.o 

C_DEPS += \
./SERVICES/OS/OS.d \
./SERVICES/OS/OS_Config.d \
./SERVICES/OS/Tasks.d 


# Each subdirectory must supply rules for building sources it contributes
SERVICES/OS/%.o: ../SERVICES/OS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


