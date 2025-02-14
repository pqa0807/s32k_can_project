################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/CAN/Can.c \
../Driver/CAN/Can_Cfg.c 

OBJS += \
./Driver/CAN/Can.o \
./Driver/CAN/Can_Cfg.o 

C_DEPS += \
./Driver/CAN/Can.d \
./Driver/CAN/Can_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/CAN/%.o: ../Driver/CAN/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Driver/CAN/Can.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


