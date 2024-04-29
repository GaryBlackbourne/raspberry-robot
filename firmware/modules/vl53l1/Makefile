# MCU makefiles

INCLUDES = $(wildcard inc/*.h)

GCC_FLAGS += -Icore
GCC_FLAGS += -Iplatform
GCC_FLAGS += -I../hal/inc
GCC_FLAGS += -I../mcu/inc

SOURCES = $(notdir $(wildcard core/*.c))
SOURCES += $(notdir $(wildcard platform/*.c))
OBJECTS = $(foreach src, $(SOURCES), $(notdir $(basename $(src))).o)
TARGETS = $(foreach object, $(OBJECTS), obj/$(object))

all: $(TARGETS)

obj/%.o: core/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

obj/%.o: platform/%.c
	$(CC) $(GCC_FLAGS) -c $^ -o $@

clean:
	if [ -n $(ls -A obj/) ]; then rm obj/*; fi
.PHONY: clean

