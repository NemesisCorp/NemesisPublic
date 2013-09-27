################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SPI2.c \
../src/adc.c \
../src/cr_startup_lpc176x.c \
../src/ece471.c \
../src/lcd.c \
../src/main.c \
../src/socket.c \
../src/ssp.c \
../src/tcp.c \
../src/udp.c \
../src/util.c \
../src/w5200.c 

OBJS += \
./src/SPI2.o \
./src/adc.o \
./src/cr_startup_lpc176x.o \
./src/ece471.o \
./src/lcd.o \
./src/main.o \
./src/socket.o \
./src/ssp.o \
./src/tcp.o \
./src/udp.o \
./src/util.o \
./src/w5200.o 

C_DEPS += \
./src/SPI2.d \
./src/adc.d \
./src/cr_startup_lpc176x.d \
./src/ece471.d \
./src/lcd.d \
./src/main.d \
./src/socket.d \
./src/ssp.d \
./src/tcp.d \
./src/udp.d \
./src/util.d \
./src/w5200.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\Evan\Desktop\ECE471_Public\Labs\Lab1\CMSISv2p00_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC17xx -I"C:\Users\Evan\Desktop\ECE471_Public\Labs\Lab1\CMSISv2p00_LPC17xx\inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


