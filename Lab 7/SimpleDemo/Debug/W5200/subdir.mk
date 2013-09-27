################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../W5200/SPI2.c \
../W5200/md5.c \
../W5200/socket.c \
../W5200/udp.c \
../W5200/util.c \
../W5200/w5200.c 

OBJS += \
./W5200/SPI2.o \
./W5200/md5.o \
./W5200/socket.o \
./W5200/udp.o \
./W5200/util.o \
./W5200/w5200.o 

C_DEPS += \
./W5200/SPI2.d \
./W5200/md5.d \
./W5200/socket.d \
./W5200/udp.d \
./W5200/util.d \
./W5200/w5200.d 


# Each subdirectory must supply rules for building sources it contributes
W5200/%.o: ../W5200/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\Evan\Desktop\Evan_Pederson\SimpleDemo" -I"C:\Users\Evan\Desktop\Evan_Pederson\CMSISv1p30_LPC17xx\inc" -I"C:\Users\Evan\Desktop\Evan_Pederson\FreeRTOS_Library\include" -I"C:\Users\Evan\Desktop\Evan_Pederson\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


