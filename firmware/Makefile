
MAKEFLAGS = --jobs=$(shell nproc) # allow multiple thread to be run when compiling
# MAKEFLAGS += --output-sync=target # buffer commands outputs

INCLUDE_DIRS = inc
INCLUDE_FREERTOS = FreeRTOS/Source/include
FREERTOS_SRC_DIR = FreeRTOS/Source
FREERTOS_PORTABLE_DIR = FreeRTOS/Source/portable/GCC/ARM_CM3

OUTPUT_DIR = output
OBJECTS_DIR = $(OUTPUT_DIR)/objects

DEVICE = -DSTM32F103xB # may not be correct
LINKERSCRIPT = STM32F103C8TX_FLASH.ld
MEMORY_START_ADDR = 0x8000000

## project files
SOURCES = src/main.c
SOURCES += src/pro_tasks.c
SOURCES += src/pro_driver.c
SOURCES += src/pro_helpers.c
SOURCES += src/pro_IRQ.c

## MCU files
SOURCES += src/startup_stm32f103c8tx.s
SOURCES += src/system_stm32f1xx.c				

## FreeRTOS files
SOURCES += $(FREERTOS_SRC_DIR)/tasks.c
SOURCES += $(FREERTOS_SRC_DIR)/queue.c				
SOURCES += $(FREERTOS_SRC_DIR)/list.c				
SOURCES += $(FREERTOS_SRC_DIR)/timers.c				
SOURCES += $(FREERTOS_SRC_DIR)/portable/MemMang/heap_1.c
SOURCES += $(FREERTOS_PORTABLE_DIR)/port.c			# freeRTOS port for ARM CM3

# compiler (and precompiler) options:
GCC_FLAGS = $(DEVICE) # specify target MCU
GCC_FLAGS += -I$(INCLUDE_DIRS) # specify include directory
GCC_FLAGS += -I$(INCLUDE_FREERTOS) # specify directory for freeRTOS
GCC_FLAGS += -I$(FREERTOS_PORTABLE_DIR) # specify port directory (portmacro.h)
GCC_FLAGS += -Wall # enable all warnings
GCC_FLAGS += -ggdb # use maximum amount of info for gdb debugger
GCC_FLAGS += -mcpu=cortex-m3 # specify CPU core
GCC_FLAGS += --specs=nano.specs # better newlib implementation (whatever that means?) (not nosys.specs)
GCC_FLAGS += -mthumb # use thumb instructions

# magic fp shit from (https://embeddedartistry.com/blog/2017/10/11/demystifying-arm-floating-point-compiler-options/) :
FPU_FLAGS += -mfloat-abi=soft # no FPU in uC
# FPU_FLAGS += -mfpu=fpv4-sp-d16 # specify fpu for hard fp abi

GCC_FLAGS += $(FPU_FLAGS)

# linker options: (-Wl passes options to linker)
# LD_FLAGS = $(FPU_FLAGS)
LD_FLAGS = -T"$(LINKERSCRIPT)" # specify linker script
LD_FLAGS += -Wl,-Map=$(OUTPUT_DIR)/"program.map" #specify .map file
LD_FLAGS += -Wl,--gc-sections # linker doesnt link dead code
LD_FLAGS += -Wl,--start-group -lc -lm -Wl,--end-group # add -l switches and archive files (source: GNU ld manual)
LD_FLAGS += -static # static linking? (not confirmed)

all: bin

bin: $(OUTPUT_DIR)/program.elf
	arm-none-eabi-objcopy -O binary output/program.elf output/program.bin

flash: 
	st-flash write output/program.bin $(MEMORY_START_ADDR)

$(OUTPUT_DIR)/program.elf: $(SOURCES)
	arm-none-eabi-gcc $(GCC_FLAGS) $^ -o $@ $(LD_FLAGS)

command:
	@echo $(FREERTOS_PORTABLE_DIR)/port.c

clean:
	@rm $(OUTPUT_DIR)/*
	@echo "Build outputs deleted!"

.PHONY: flash command clean
