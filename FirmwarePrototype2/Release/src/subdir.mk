################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal.c \
../src/interrupts.c \
../src/main.c \
../src/stm32f7xx_hal_msp.c \
../src/write.c 

C_DEPS += \
./src/hal.d \
./src/interrupts.d \
./src/main.d \
./src/stm32f7xx_hal_msp.d \
./src/write.d 

OBJS += \
./src/hal.o \
./src/interrupts.o \
./src/main.o \
./src/stm32f7xx_hal_msp.o \
./src/write.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -Wall -Wextra -g -DNDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I../src/fmgl/include -I../src/fmgl/fonts/include -I../src/fmgl/charsets/include -I../src/l2hal/drivers/internal/crc/include -I../src/l2hal/drivers/dds/ad9835/include -I../src/l2hal/drivers/display/gc9a01/include -I../src/l2hal/drivers/display/ssd1306/include -I../src/l2hal/drivers/display/ssd1327/include -I../src/l2hal/drivers/eeprom/24x/include -I../src/l2hal/drivers/input/buttons/include -I../src/l2hal/drivers/input/encoders/include -I../src/l2hal/drivers/ram/ly68l6400/include -I../src/l2hal/drivers/ram/ly68l6400_qspi/include -I../src/l2hal/drivers/sdcard/include -I../src/l2hal/drivers/bluetooth/hc06/include -I../src/l2hal/drivers/dac/ad5245/include -I../src/l2hal/include -I../src/l2hal/mcu_dependent -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/stm32f7xx_hal_msp.o: ../src/stm32f7xx_hal_msp.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -Wall -Wextra -g -DNDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I../src/fmgl/include -I../src/fmgl/fonts/include -I../src/fmgl/charsets/include -I../src/l2hal/drivers/internal/crc/include -I../src/l2hal/drivers/dds/ad9835/include -I../src/l2hal/drivers/display/gc9a01/include -I../src/l2hal/drivers/display/ssd1306/include -I../src/l2hal/drivers/display/ssd1327/include -I../src/l2hal/drivers/eeprom/24x/include -I../src/l2hal/drivers/input/buttons/include -I../src/l2hal/drivers/input/encoders/include -I../src/l2hal/drivers/ram/ly68l6400/include -I../src/l2hal/drivers/ram/ly68l6400_qspi/include -I../src/l2hal/drivers/sdcard/include -I../src/l2hal/drivers/bluetooth/hc06/include -I../src/l2hal/drivers/dac/ad5245/include -I../src/l2hal/include -I../src/l2hal/mcu_dependent -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -std=gnu11 -Wno-padded -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


