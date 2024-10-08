################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/MT25Q.c \
../Core/Src/adc.c \
../Core/Src/command_parser.c \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/imu.c \
../Core/Src/internal_adc.c \
../Core/Src/lfs.c \
../Core/Src/lfs_port.c \
../Core/Src/lfs_util.c \
../Core/Src/main.c \
../Core/Src/nor.c \
../Core/Src/nor_ids.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/MT25Q.o \
./Core/Src/adc.o \
./Core/Src/command_parser.o \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/imu.o \
./Core/Src/internal_adc.o \
./Core/Src/lfs.o \
./Core/Src/lfs_port.o \
./Core/Src/lfs_util.o \
./Core/Src/main.o \
./Core/Src/nor.o \
./Core/Src/nor_ids.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/MT25Q.d \
./Core/Src/adc.d \
./Core/Src/command_parser.d \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/imu.d \
./Core/Src/internal_adc.d \
./Core/Src/lfs.d \
./Core/Src/lfs_port.d \
./Core/Src/lfs_util.d \
./Core/Src/main.d \
./Core/Src/nor.d \
./Core/Src/nor_ids.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F427xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -IC:/Users/sanga/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/sanga/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/sanga/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/sanga/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -IC:/Users/sanga/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/sanga/STM32Cube/Repository/STM32Cube_FW_F4_V1.26.2/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

