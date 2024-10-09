include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c) $(wildcard process/*.c) $(wildcard scheduler/*.c) $(wildcard structures/*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

CFLAGS += -I./include -msse2

MEMORY_MANAGER ?= buddy

ifeq ($(MEMORY_MANAGER), bitmap)
    SOURCES += ./memory/bitmapMemoryManager.c
else ifeq ($(MEMORY_MANAGER), buddy)
    SOURCES += ./memory/buddyMemoryManager.c
else
    $(error "MEMORY_MANAGER debe ser 'bitmap' o 'buddy'")
endif

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf *.bin *.o ./structures/*.o ./scheduler/*.o ./process/*.o ./memory/*.o
	
.PHONY: all clean