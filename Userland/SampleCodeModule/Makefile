include ../Makefile.inc

GCCFLAGS += -fPIE

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:asm/%.asm=obj/%.o)

SOURCES_MM=$(wildcard test/*.c) $(wildcard test/memory/*.c)
SOURCES_PROC=$(wildcard test/process/*.c)

all: $(MODULE)

$(MODULE): $(SOURCES) $(SOURCES_MM) $(SOURCES_PROC) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -I./include -I../../Kernel/include/memory -T sampleCodeModule.ld _loader.c $(SOURCES) $(SOURCES_MM) $(SOURCES_PROC) $(OBJECTS_ASM) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -I../../Kernel/include/memory -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) $(OBJECTS_ASM) -o ../0000-sampleCodeModule.elf

obj/%.o : asm/%.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -rf *.o
	rm -rf obj/*.o

.PHONY: all clean print