# MCU makefiles

INCLUDES = $(wildcard inc/*.h)

GCC_FLAGS += -Iinc
GCC_FLAGS += -I../mcu/inc

SOURCES = $(notdir $(wildcard src/*.c))
OBJECTS = $(foreach src, $(SOURCES), $(notdir $(basename $(src))).o)
TARGETS = $(foreach object, $(OBJECTS), obj/$(object))

all: $(TARGETS)

obj/%.o: src/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

clean:
	if [ -n $(ls -A obj/) ]; then rm obj/*; fi
.PHONY: clean

