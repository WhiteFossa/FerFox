################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/l2hal/drivers/dds/ad9835/src/l2hal_ad9835.c 

C_DEPS += \
./src/l2hal/drivers/dds/ad9835/src/l2hal_ad9835.d 

OBJS += \
./src/l2hal/drivers/dds/ad9835/src/l2hal_ad9835.o 


# Each subdirectory must supply rules for building sources it contributes
src/l2hal/drivers/dds/ad9835/src/%.o: ../src/l2hal/drivers/dds/ad9835/src/%.c src/l2hal/drivers/dds/ad9835/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I../libs/tjpgd -I../src/l2hal/drivers/display/gc9a01_local_framebuffer/include -I../src/fmgl/include -I../src/fmgl/fonts/include -I../src/fmgl/charsets/include -I../src/l2hal/drivers/internal/crc/include -I../src/l2hal/drivers/dds/ad9835/include -I../src/l2hal/drivers/display/gc9a01/include -I../src/l2hal/drivers/display/ssd1306/include -I../src/l2hal/drivers/display/ssd1327/include -I../src/l2hal/drivers/eeprom/24x/include -I../src/l2hal/drivers/input/buttons/include -I../src/l2hal/drivers/input/encoders/include -I../src/l2hal/drivers/ram/ly68l6400/include -I../src/l2hal/drivers/ram/ly68l6400_qspi/include -I../src/l2hal/drivers/sdcard/include -I../src/l2hal/drivers/bluetooth/hc06/include -I../src/l2hal/drivers/dac/ad5245/include -I../src/l2hal/include -I../src/l2hal/mcu_dependent -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -isystem../libs/fatfs -isystem../libs/fatfs -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


