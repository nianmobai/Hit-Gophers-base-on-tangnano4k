################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CORE/core_cm3.c 

OBJS += \
./CORE/core_cm3.o 

C_DEPS += \
./CORE/core_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
CORE/%.o: ../CORE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\CORE" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\PERIPHERAL\Includes" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\SYSTEM" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\USER" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


