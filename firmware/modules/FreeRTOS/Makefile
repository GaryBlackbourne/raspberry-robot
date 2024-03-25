# FreeRTOS Makefile

INCLUDES = $(wildcard Soure/include)

# heap version:
HEAP_VERSION = heap_1.c

GCC_FLAGS += -Iinc
GCC_FLAGS += -ISource/include
GCC_FLAGS += -ISource/portable/GCC/ARM_CM3

SOURCES = $(wildcard Source/*.c)

OBJECTS = $(foreach src, $(SOURCES), $(notdir $(basename $(src)).o))
OBJECTS += heap.o
OBJECTS += port.o

TARGETS = $(foreach object, $(OBJECTS), obj/$(object))

all: $(TARGETS)

obj/%.o: Source/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

obj/port.o: Source/portable/GCC/ARM_CM3/port.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

obj/heap.o: Source/portable/MemMang/$(HEAP_VERSION)
	$(CC) $(GCC_FLAGS) -c $^ -o $@

clean:
	if [ -n $(ls -A obj) ]; then rm obj/*; fi
.PHONY: clean
