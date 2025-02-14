################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CAR_dbc/honda_civic.c \
../CAR_dbc/honda_crv.c \
../CAR_dbc/huynhdai_elantra.c \
../CAR_dbc/mazda_cx5.c 

OBJS += \
./CAR_dbc/honda_civic.o \
./CAR_dbc/honda_crv.o \
./CAR_dbc/huynhdai_elantra.o \
./CAR_dbc/mazda_cx5.o 

C_DEPS += \
./CAR_dbc/honda_civic.d \
./CAR_dbc/honda_crv.d \
./CAR_dbc/huynhdai_elantra.d \
./CAR_dbc/mazda_cx5.d 


# Each subdirectory must supply rules for building sources it contributes
CAR_dbc/%.o: ../CAR_dbc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@CAR_dbc/honda_civic.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


