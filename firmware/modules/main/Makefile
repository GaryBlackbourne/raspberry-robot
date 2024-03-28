# Main Makefile

GCC_FLAGS += -I../FreeRTOS/Source/include
GCC_FLAGS += -I../FreeRTOS/Source/portable/GCC/ARM_CM3

GCC_FLAGS += -Iinc
GCC_FLAGS += -Iinc/irq
GCC_FLAGS += -Iinc/bsp
GCC_FLAGS += -I../mcu/inc
GCC_FLAGS += -I../hal/inc

SOURCES = $(wildcard src/*.c)
SOURCES += $(wildcard src/*/*.c)
OBJECTS = $(foreach src, $(SOURCES), $(notdir $(basename $(src))).o)
TARGETS = $(foreach object, $(OBJECTS), obj/$(object))

all:  $(TARGETS)

obj/%.o: src/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

obj/%.o: src/*/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

clean:
	if [ -n $(ls -A obj/) ]; then rm obj/*; fi
.PHONY: clean
