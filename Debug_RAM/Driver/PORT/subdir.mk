################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/PORT/port.c 

OBJS += \
./Driver/PORT/port.o 

C_DEPS += \
./Driver/PORT/port.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/PORT/%.o: ../Driver/PORT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Driver/PORT/port.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


