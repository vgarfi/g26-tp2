MODULE = test_mm

GCC = gcc

GCCFLAGS = -Wall -g

INCLUDE = ./include

SOURCES = $(wildcard *.c)
MEMORY_SOURCES = ./memory/buddyMemoryManager.c

OBJECTS = $(SOURCES:.c=.o)
KERNEL_OBJECTS = $(MEMORY_SOURCES:.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(KERNEL_OBJECTS)
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) $(OBJECTS) $(KERNEL_OBJECTS) -o $(MODULE) -lc -lm

%.o: %.c
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o $(MODULE) ./memory/bitmapMemoryManager.o ./memory/buddyMemoryManager.o

.PHONY: all clean