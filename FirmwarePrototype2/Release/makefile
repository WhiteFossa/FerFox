################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/src/stm32f7-hal/subdir.mk
-include system/src/newlib/subdir.mk
-include system/src/diag/subdir.mk
-include system/src/cortexm/subdir.mk
-include system/src/cmsis/subdir.mk
-include src/l2hal/src/subdir.mk
-include src/l2hal/mcu_dependent/mcus/stm32f767zit6u/drivers/input/buttons/src/subdir.mk
-include src/l2hal/mcu_dependent/mcus/stm32f767zit6u/subdir.mk
-include src/l2hal/drivers/sdcard/src/subdir.mk
-include src/l2hal/drivers/ram/ly68l6400_qspi/src/subdir.mk
-include src/l2hal/drivers/ram/ly68l6400/src/subdir.mk
-include src/l2hal/drivers/internal/crc/src/subdir.mk
-include src/l2hal/drivers/input/encoders/src/subdir.mk
-include src/l2hal/drivers/input/buttons/src/subdir.mk
-include src/l2hal/drivers/eeprom/24x/src/subdir.mk
-include src/l2hal/drivers/display/ssd1327/src/subdir.mk
-include src/l2hal/drivers/display/ssd1306/src/subdir.mk
-include src/l2hal/drivers/display/gc9a01_local_framebuffer/src/subdir.mk
-include src/l2hal/drivers/display/gc9a01/src/subdir.mk
-include src/l2hal/drivers/dds/ad9835/src/subdir.mk
-include src/l2hal/drivers/dac/ad5245/src/subdir.mk
-include src/l2hal/drivers/bluetooth/hc06/src/subdir.mk
-include src/fmgl/src/subdir.mk
-include src/fmgl/fonts/src/subdir.mk
-include src/subdir.mk
-include libs/tjpgd/subdir.mk
-include libs/libhwjpeg/subdir.mk
-include libs/fatfs/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := FerFoxPrototype2
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
FerFoxPrototype2.hex \

SECONDARY_SIZE += \
FerFoxPrototype2.siz \


# All Target
all: main-build

# Main-build Target
main-build: FerFoxPrototype2.elf secondary-outputs

# Tool invocations
FerFoxPrototype2.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Arm Cross C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"FerFoxPrototype2.map" --specs=nano.specs -o "FerFoxPrototype2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

FerFoxPrototype2.hex: FerFoxPrototype2.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU Arm Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "FerFoxPrototype2.elf"  "FerFoxPrototype2.hex"
	@echo 'Finished building: $@'
	@echo ' '

FerFoxPrototype2.siz: FerFoxPrototype2.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU Arm Cross Print Size'
	arm-none-eabi-size --format=berkeley "FerFoxPrototype2.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CCM_DEPS)$(C_UPPER_DEPS)$(SECONDARY_SIZE)$(CXXM_DEPS)$(C_DEPS)$(CC_DEPS)$(SX_DEPS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(SECONDARY_FLASH)$(ASM_DEPS)$(S_UPPER_DEPS)$(C++M_DEPS)$(CPP_DEPS) FerFoxPrototype2.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
