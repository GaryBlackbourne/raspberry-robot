# MCU makefiles

INCLUDES = $(wildcard inc/*.h)

GCC_FLAGS += -Iinc

all: $(OBJECT_DIR)/system_stm32f1xx.o $(OBJECT_DIR)/startup_stm32f103c8tx.o

$(OBJECT_DIR)/system_stm32f1xx.o: src/system_stm32f1xx.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@ 

$(OBJECT_DIR)/startup_stm32f103c8tx.o: src/startup_stm32f103c8tx.s
	$(CC) $(GCC_FLAGS) -c $^ -o $@ 
