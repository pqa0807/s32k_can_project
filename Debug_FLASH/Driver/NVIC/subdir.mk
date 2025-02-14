################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/NVIC/nvic.c 

OBJS += \
./Driver/NVIC/nvic.o 

C_DEPS += \
./Driver/NVIC/nvic.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/NVIC/%.o: ../Driver/NVIC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Driver/NVIC/nvic.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


