include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c) $(wildcard memory/*.c) $(wildcard process/*.c) $(wildcard scheduler/*.c) $(wildcard structures/*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
OBJDIR=obj
STATICLIBS=

TEST_SOURCES=./memory/test_mm.c ./memory/buddyMemoryManager.c ./memory/test_util.c ./memory/syscall.c
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
TEST_EXEC=test_mm

CFLAGS += -I./include/memory -I./include/process -I./include/scheduler -I./include/structures -msse2

all: $(KERNEL) move_objects $(TEST_EXEC)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) $(CFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	chmod 777 $(OBJDIR) 

move_objects: $(OBJDIR)
	mv *.o $(OBJDIR)
	mv asm/*.o $(OBJDIR)
clean:
	rm -rf $(OBJDIR) *.bin

$(TEST_EXEC): $(TEST_SOURCES)
	$(GCC) -o $(TEST_EXEC) $(TEST_SOURCES) -I./include/memory -std=c99

.PHONY: all clean
