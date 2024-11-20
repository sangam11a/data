################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Drivers/flash/MT25QL.c \
../Core/Drivers/flash/internal_flash.c \
../Core/Drivers/flash/memory_addressing.c 

OBJS += \
./Core/Drivers/flash/MT25QL.o \
./Core/Drivers/flash/internal_flash.o \
./Core/Drivers/flash/memory_addressing.o 

C_DEPS += \
./Core/Drivers/flash/MT25QL.d \
./Core/Drivers/flash/internal_flash.d \
./Core/Drivers/flash/memory_addressing.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Drivers/flash/%.o: ../Core/Drivers/flash/%.c Core/Drivers/flash/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F427xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

