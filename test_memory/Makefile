MODULE = test_mm

GCC = gcc

GCCFLAGS = -Wall -g

INCLUDE = ./include
KERNEL_INCLUDE = ../Kernel/include/memory

SOURCES = $(wildcard *.c)
KERNEL_SOURCES = ../Kernel/memory/bitmapMemoryManager.c

OBJECTS = $(SOURCES:.c=.o)
KERNEL_OBJECTS = $(KERNEL_SOURCES:.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(KERNEL_OBJECTS)
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(KERNEL_INCLUDE) $(OBJECTS) $(KERNEL_OBJECTS) -o $(MODULE) -lc

%.o: %.c
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(KERNEL_INCLUDE) -c $< -o $@

clean:
	rm -rf *.o $(MODULE)

.PHONY: all clean