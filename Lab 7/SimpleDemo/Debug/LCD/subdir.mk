################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD/lcd.c 

OBJS += \
./LCD/lcd.o 

C_DEPS += \
./LCD/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
LCD/%.o: ../LCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\Evan\Desktop\Evan_Pederson\SimpleDemo" -I"C:\Users\Evan\Desktop\Evan_Pederson\CMSISv1p30_LPC17xx\inc" -I"C:\Users\Evan\Desktop\Evan_Pederson\FreeRTOS_Library\include" -I"C:\Users\Evan\Desktop\Evan_Pederson\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


