SOURCES=$(wildcard *.c) $(wildcard memory/*.c) ../../Kernel/memory/bitmapMemoryManager.c

withKernel ?= false

ifeq ($(withKernel),false)
    SOURCES += noKernel/mainMemory.c
else
    SOURCES += kernel.c
endif

OBJECTS=$(SOURCES:.c=.o)

GCC=gcc

GCCFLAGS=-g -fPIE -I./include -I../../Kernel/include -m64 -fno-exceptions -std=c99 -Wall
LDFLAGS=-pie

all: test_mm

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

test_mm: $(OBJECTS)
	$(GCC) $(LDFLAGS) $(OBJECTS) -o test_mm

clean:
	rm -rf *.o ./process/*.o ./memory/*.o ./noKernel/*.o test_mm

.PHONY: all clean