################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/PCC/pcc.c 

OBJS += \
./Driver/PCC/pcc.o 

C_DEPS += \
./Driver/PCC/pcc.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/PCC/%.o: ../Driver/PCC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Driver/PCC/pcc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


