#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <fonts.h>
#include <time.h>
#include <defs.h>
#include <interrupts.h>
#include <memory/memoryManagerADT.h>
#include <process/process.h>


void load_idt(void);

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax);

MemoryManagerADT memory_manager;

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;


static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const memoryBaseAddress = (void*)0x600000;

typedef int (*EntryPoint)();

char* shell_args[] = {SHELL_PROCESS, 0};


void clearBSS(void * bssAddress, uint64_t bssSize) {
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main() {
	memory_manager = initialize_mm(memoryBaseAddress, 1024*1024*1024, 1024*1024);
	MemoryDiagnostic diagnostic = get_diagnostic_mm(memory_manager);

	char buffer[32];
	
	load_idt();
	// initializeTimer();
	initializeVideoDriver();
	initFontManager();
	
	// vdPrint("-----------------------------------", 0x00FFFFFF);
    // vdPrint("Total Memory: ", 0x00FFFFFF);
    // itoa(diagnostic.total_memory, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);
    // vdPrint("\n", 0x00FFFFFF);
    
    // vdPrint("Used Memory: ", 0x00FFFFFF);
    // itoa(diagnostic.used_memory, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);
    // vdPrint("\n", 0x00FFFFFF);
    
    // vdPrint("Free Memory: ", 0x00FFFFFF);
    // itoa(diagnostic.free_memory, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);
    // vdPrint("\n", 0x00FFFFFF);
    
    // vdPrint("Total Blocks: ", 0x00FFFFFF);
    // itoa(diagnostic.total_blocks, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);
    // vdPrint("\n", 0x00FFFFFF);
    
    // vdPrint("Used Blocks: ", 0x00FFFFFF);
    // itoa(diagnostic.used_blocks, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);
    // vdPrint("\n", 0x00FFFFFF);
    
    // vdPrint("Free Blocks: ", 0x00FFFFFF);
    // itoa(diagnostic.free_blocks, buffer, 10);
    // vdPrint(buffer, 0x00FFFFFF);
    // vdPrint("\n", 0x00FFFFFF);
	// vdPrint("-----------------------------------", 0x00FFFFFF);


	vdPrint("Hoooooooooooola", 0x00FFFFFF);
	vdPrint("\npase el inicio", 0x00FFFFFF);	
	//initialize_process_management();
	initialize_process_management();
	vdPrint("\npase el process managmente", 0x00FFFFFF);
	create_process(SHELL_PROCESS, 0, shell_args, SHELL_PRIORITY, (EntryPoint)sampleCodeModuleAddress); // TODO esto no va acá
	vdPrint("\npase la creación de shell", 0x00FFFFFF);
	requestSchedule();
	vdPrint("\npase el request schedule", 0x00FFFFFF);
	return 0;
}