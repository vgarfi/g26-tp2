include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(filter-out ./memory/bitmapMemoryManager.c ./memory/buddyMemoryManager.c, $(wildcard *.c) $(wildcard memory/*.c) $(wildcard process/*.c) $(wildcard scheduler/*.c) $(wildcard structures/*.c))
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
OBJDIR=obj
STATICLIBS=

TEST_SOURCES=./memory/test_mm.c ./memory/test_util.c ./memory/syscall.c
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
TEST_EXEC=test_mm

CFLAGS += -I./include -msse2

MEMORY_MANAGER ?= bitmap

ifeq ($(MEMORY_MANAGER), bitmap)
    SOURCES += ./memory/bitmapMemoryManager.c
    CFLAGS += -DUSE_BITMAP_MEMORY_MANAGER
else ifeq ($(MEMORY_MANAGER), buddy)
    SOURCES += ./memory/buddyMemoryManager.c
    CFLAGS += -DUSE_BUDDY_MEMORY_MANAGER
else
    $(error "MEMORY_MANAGER debe ser 'bitmap' o 'buddy'")
endif

# Aquí debes asegurarte de no incluir el administrador de memoria en los test
ifeq ($(MEMORY_MANAGER), bitmap)
    TEST_SOURCES := $(filter-out ./memory/buddyMemoryManager.c, $(TEST_SOURCES))
else ifeq ($(MEMORY_MANAGER), buddy)
    TEST_SOURCES := $(filter-out ./memory/bitmapMemoryManager.c, $(TEST_SOURCES))
endif

all: $(KERNEL) move_objects $(TEST_EXEC)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

# Cambia la regla para crear archivos .o y colócalos en OBJDIR
%.o: %.c
	$(GCC) $(GCCFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	chmod 777 $(OBJDIR) 

move_objects: $(OBJDIR)
	mv *.o $(OBJDIR) || true
	mv asm/*.o $(OBJDIR) || true
clean:
	rm -rf $(OBJDIR) *.bin
	
.PHONY: all clean