################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../system/src/newlib/cxx.cpp 

C_SRCS += \
../system/src/newlib/assert.c \
../system/src/newlib/exit.c \
../system/src/newlib/sbrk.c \
../system/src/newlib/startup.c \
../system/src/newlib/syscalls.c 

C_DEPS += \
./system/src/newlib/assert.d \
./system/src/newlib/exit.d \
./system/src/newlib/sbrk.d \
./system/src/newlib/startup.d \
./system/src/newlib/syscalls.d 

OBJS += \
./system/src/newlib/assert.o \
./system/src/newlib/cxx.o \
./system/src/newlib/exit.o \
./system/src/newlib/sbrk.o \
./system/src/newlib/startup.o \
./system/src/newlib/syscalls.o 

CPP_DEPS += \
./system/src/newlib/cxx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/newlib/%.o: ../system/src/newlib/%.c system/src/newlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I../libs/tjpgd -I../src/l2hal/drivers/display/gc9a01_local_framebuffer/include -I../src/fmgl/include -I../src/fmgl/fonts/include -I../src/fmgl/charsets/include -I../src/l2hal/drivers/internal/crc/include -I../src/l2hal/drivers/dds/ad9835/include -I../src/l2hal/drivers/display/gc9a01/include -I../src/l2hal/drivers/display/ssd1306/include -I../src/l2hal/drivers/display/ssd1327/include -I../src/l2hal/drivers/eeprom/24x/include -I../src/l2hal/drivers/input/buttons/include -I../src/l2hal/drivers/input/encoders/include -I../src/l2hal/drivers/ram/ly68l6400/include -I../src/l2hal/drivers/ram/ly68l6400_qspi/include -I../src/l2hal/drivers/sdcard/include -I../src/l2hal/drivers/bluetooth/hc06/include -I../src/l2hal/drivers/dac/ad5245/include -I../src/l2hal/include -I../src/l2hal/mcu_dependent -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -isystem../libs/fatfs -isystem../libs/fatfs -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/newlib/%.o: ../system/src/newlib/%.cpp system/src/newlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/newlib/startup.o: ../system/src/newlib/startup.c system/src/newlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F767xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -DOS_INCLUDE_STARTUP_INIT_MULTIPLE_RAM_SECTIONS -I"../include" -I../libs/tjpgd -I../src/l2hal/drivers/display/gc9a01_local_framebuffer/include -I../src/fmgl/include -I../src/fmgl/fonts/include -I../src/fmgl/charsets/include -I../src/l2hal/drivers/internal/crc/include -I../src/l2hal/drivers/dds/ad9835/include -I../src/l2hal/drivers/display/gc9a01/include -I../src/l2hal/drivers/display/ssd1306/include -I../src/l2hal/drivers/display/ssd1327/include -I../src/l2hal/drivers/eeprom/24x/include -I../src/l2hal/drivers/input/buttons/include -I../src/l2hal/drivers/input/encoders/include -I../src/l2hal/drivers/ram/ly68l6400/include -I../src/l2hal/drivers/ram/ly68l6400_qspi/include -I../src/l2hal/drivers/sdcard/include -I../src/l2hal/drivers/bluetooth/hc06/include -I../src/l2hal/drivers/dac/ad5245/include -I../src/l2hal/include -I../src/l2hal/mcu_dependent -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f7-hal" -isystem../libs/fatfs -isystem../libs/fatfs -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


