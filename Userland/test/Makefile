SOURCES_MM=$(wildcard *.c) $(wildcard memory/*.c) ../../Kernel/memory/bitmapMemoryManager.c
SOURCES_PROC= $(wildcard process/*.c)

withKernel ?= false

GCCFLAGS=-include ../SampleCodeModule/include/syscalls.h -g -fPIE -I./include -I../../Kernel/include -m64 -fno-exceptions -std=c99 -Wall

ifeq ($(withKernel),false)
    SOURCES_MM += noKernel/mainMemory.c
else
    SOURCES_MM += withKernel/mainMemory.c
	GCCFLAGS += -DNO_STDDEF -ffreestanding -nostdlib -fno-common -mno-red-zone -mno-mmx -mno-sse -mno-sse2
endif

OBJECTS_MM=$(SOURCES_MM:.c=.o)
OBJECTS_PROC=$(SOURCES_PROC:.c=.o)

GCC=gcc

LDFLAGS=-pie

all: test_mm test_priorities test_processes

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

test_mm: $(OBJECTS_MM)
	$(GCC) $(LDFLAGS) $(OBJECTS_MM) -o test_mm

test_processes: $(OBJECTS_PROC)
	$(GCC) $(LDFLAGS) $(OBJECTS_PROC) -o test_processes

clean:
	rm -rf *.o ./process/*.o ./memory/*.o ./noKernel/*.o ./withKernel/*.o test_mm test_processes

.PHONY: all clean