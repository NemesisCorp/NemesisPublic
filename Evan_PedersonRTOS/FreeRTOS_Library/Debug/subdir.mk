################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../list.c \
../queue.c \
../tasks.c \
../timers.c 

OBJS += \
./list.o \
./queue.o \
./tasks.o \
./timers.o 

C_DEPS += \
./list.d \
./queue.d \
./tasks.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -I"C:\Users\Evan\Desktop\Evan_Pederson\Evan_PedersonRTOS\FreeRTOS_Library\include" -I"C:\Users\Evan\Desktop\Evan_Pederson\Evan_PedersonRTOS\CMSISv1p30_LPC17xx\inc" -I"C:\Users\Evan\Desktop\Evan_Pederson\Evan_PedersonRTOS\FreeRTOS_Library\portable" -I"C:\Users\Evan\Desktop\Evan_Pederson\Evan_PedersonRTOS\SimpleDemo" -O1 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


