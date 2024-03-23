# MCU makefiles

INCLUDES = $(wildcard inc/*.h)

GCC_FLAGS += -Iinc

all: obj/system_stm32f1xx.o obj/startup_stm32f103c8tx.o

obj/system_stm32f1xx.o: src/system_stm32f1xx.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@ 

obj/startup_stm32f103c8tx.o: src/startup_stm32f103c8tx.s
	$(CC) $(GCC_FLAGS) -c $^ -o $@ 

clean:
	@rm obj/*
.PHONY: clean

