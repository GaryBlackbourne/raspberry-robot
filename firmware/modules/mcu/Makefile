# MCU Makefile

INCLUDES = $(wildcard inc/*.h)

GCC_FLAGS += -Iinc

all: obj/system_stm32f1xx.o obj/startup_stm32f103c8tx.o

obj/%.o: src/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@ 

obj/%.o: src/%.s
	$(CC) $(GCC_FLAGS) -c $^ -o $@ 

clean:
	@rm obj/*
.PHONY: clean

