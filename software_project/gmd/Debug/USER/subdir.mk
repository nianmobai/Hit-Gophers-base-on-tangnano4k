################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/Lcd_Driver.c \
../USER/NumandChar.c \
../USER/drv_gpio.c \
../USER/drv_timer.c \
../USER/drv_uart.c \
../USER/gw1ns4c_it.c \
../USER/main.c \
../USER/picture.c \
../USER/retarget.c 

OBJS += \
./USER/Lcd_Driver.o \
./USER/NumandChar.o \
./USER/drv_gpio.o \
./USER/drv_timer.o \
./USER/drv_uart.o \
./USER/gw1ns4c_it.o \
./USER/main.o \
./USER/picture.o \
./USER/retarget.o 

C_DEPS += \
./USER/Lcd_Driver.d \
./USER/NumandChar.d \
./USER/drv_gpio.d \
./USER/drv_timer.d \
./USER/drv_uart.d \
./USER/gw1ns4c_it.d \
./USER/main.d \
./USER/picture.d \
./USER/retarget.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.o: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\CORE" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\PERIPHERAL\Includes" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\SYSTEM" -I"F:\qq文件\530519499\FileRecv\gw1nsr_4c_mcu_demo\mcu_prj\gmd\USER" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


