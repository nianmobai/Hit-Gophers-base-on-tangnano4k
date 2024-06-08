################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SYSTEM/system_gw1ns4c.c 

OBJS += \
./SYSTEM/system_gw1ns4c.o 

C_DEPS += \
./SYSTEM/system_gw1ns4c.d 


# Each subdirectory must supply rules for building sources it contributes
SYSTEM/%.o: ../SYSTEM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\CORE" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\PERIPHERAL\Includes" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\SYSTEM" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\USER" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


