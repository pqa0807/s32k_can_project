################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/LPUART/lpuart.c 

OBJS += \
./Driver/LPUART/lpuart.o 

C_DEPS += \
./Driver/LPUART/lpuart.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/LPUART/%.o: ../Driver/LPUART/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Driver/LPUART/lpuart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


