all: $(OUTPUT_DIR)/program.elf
	arm-none-eabi-objcopy -O binary $^ $(OUTPUT_DIR)/program.bin

objects = $(wildcard $(OBJECT_DIR)/*.o)

$(OUTPUT_DIR)/program.elf: $(objects)
	$(LD) $^ -o $@ $(LD_FLAGS)

flash: $(OUTPUT_DIR)/program.bin
	st-flash write $^ $(MEMORY_START_ADDR)

command:
	@echo $(SOURCES)

term:
	@screen /dev/ttyUSB0 115200


