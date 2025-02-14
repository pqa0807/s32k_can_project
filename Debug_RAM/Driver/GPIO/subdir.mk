################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/GPIO/gpio.c 

OBJS += \
./Driver/GPIO/gpio.o 

C_DEPS += \
./Driver/GPIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/GPIO/%.o: ../Driver/GPIO/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Driver/GPIO/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


