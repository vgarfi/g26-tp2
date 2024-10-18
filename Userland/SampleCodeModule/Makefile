include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:asm/%.asm=obj/%.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM) ../../Kernel/memory/bitmapMemoryManager.o
	$(GCC) $(GCCFLAGS) -I./include -I../../Kernel/include/memory -T sampleCodeModule.ld _loader.c $(SOURCES) $(SOURCES_MM) $(SOURCES_PROC) $(OBJECTS_ASM) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -no-pie -I./include -I../../Kernel/include/memory -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) $(OBJECTS_ASM) -o ../0000-sampleCodeModule.elf

obj/%.o : asm/%.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@
	
clean:
	rm -rf *.o
	rm -rf obj/*.o

.PHONY: all clean print