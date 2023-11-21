################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DR_ADC.c \
../Core/Src/DR_Buck.c \
../Core/Src/Mde_MPPT_In.c \
../Core/Src/Mde_MPPT_Out.c \
../Core/Src/PR_Buck.c \
../Core/Src/PR_UART.c \
../Core/Src/Timers.c \
../Core/Src/main.c \
../Core/Src/serial.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/DR_ADC.o \
./Core/Src/DR_Buck.o \
./Core/Src/Mde_MPPT_In.o \
./Core/Src/Mde_MPPT_Out.o \
./Core/Src/PR_Buck.o \
./Core/Src/PR_UART.o \
./Core/Src/Timers.o \
./Core/Src/main.o \
./Core/Src/serial.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/DR_ADC.d \
./Core/Src/DR_Buck.d \
./Core/Src/Mde_MPPT_In.d \
./Core/Src/Mde_MPPT_Out.d \
./Core/Src/PR_Buck.d \
./Core/Src/PR_UART.d \
./Core/Src/Timers.d \
./Core/Src/main.d \
./Core/Src/serial.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/DR_ADC.d ./Core/Src/DR_ADC.o ./Core/Src/DR_ADC.su ./Core/Src/DR_Buck.d ./Core/Src/DR_Buck.o ./Core/Src/DR_Buck.su ./Core/Src/Mde_MPPT_In.d ./Core/Src/Mde_MPPT_In.o ./Core/Src/Mde_MPPT_In.su ./Core/Src/Mde_MPPT_Out.d ./Core/Src/Mde_MPPT_Out.o ./Core/Src/Mde_MPPT_Out.su ./Core/Src/PR_Buck.d ./Core/Src/PR_Buck.o ./Core/Src/PR_Buck.su ./Core/Src/PR_UART.d ./Core/Src/PR_UART.o ./Core/Src/PR_UART.su ./Core/Src/Timers.d ./Core/Src/Timers.o ./Core/Src/Timers.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/serial.d ./Core/Src/serial.o ./Core/Src/serial.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

