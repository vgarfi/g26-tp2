#include <memory/memoryManagerADT.h>
#include <kernelManagement.h>
#include <process/process.h>
#include <videoDriver.h>
#include <interrupts.h>
#include <string.h>

char* shell_args[] = {SHELL_PROCESS, 0};
char* idle_args[] = {IDLE_PROCESS, 0};

MemoryManagerADT memory_manager;

typedef int (*EntryPoint)();

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const memoryBaseAddress = (void*)0x600000;


void initialize_management(void){
	memory_manager = initialize_mm(memoryBaseAddress, 1024*1024*1024, 1024*1024);
    create_process(IDLE_PROCESS, 0, idle_args, IDLE_PRIORITY, &idle_process);
    vdPrint("\nPasado la creación del IDLE", 0x00FFFFFF);
	//create_process(SHELL_PROCESS, 0, shell_args, SHELL_PRIORITY, (EntryPoint)sampleCodeModuleAddress);
    //vdPrint("\nPasado la creación de SHELL", 0x00FFFFFF);
}

int64_t idle_process(int argc, char* argv){
    while (1) {
        vdPrint("\nIDLE", 0x00FFFFFF);
        _hlt();
    }
}

void initial_printing(){
	MemoryDiagnostic diagnostic = get_diagnostic_mm(memory_manager);
	char buffer[32];

    vdPrint("-----------------------------------", 0x00FFFFFF);
    vdPrint("Total Memory: ", 0x00FFFFFF);
    itoa(diagnostic.total_memory, buffer, 10);
    vdPrint(buffer, 0x00FFFFFF);
    vdPrint("\n", 0x00FFFFFF);
    
    vdPrint("Used Memory: ", 0x00FFFFFF);
    itoa(diagnostic.used_memory, buffer, 10);
    vdPrint(buffer, 0x00FFFFFF);
    vdPrint("\n", 0x00FFFFFF);
    
    vdPrint("Free Memory: ", 0x00FFFFFF);
    itoa(diagnostic.free_memory, buffer, 10);
    vdPrint(buffer, 0x00FFFFFF);
    vdPrint("\n", 0x00FFFFFF);
    
    vdPrint("Total Blocks: ", 0x00FFFFFF);
    itoa(diagnostic.total_blocks, buffer, 10);
    vdPrint(buffer, 0x00FFFFFF);
    vdPrint("\n", 0x00FFFFFF);
    
    vdPrint("Used Blocks: ", 0x00FFFFFF);
    itoa(diagnostic.used_blocks, buffer, 10);
    vdPrint(buffer, 0x00FFFFFF);
    vdPrint("\n", 0x00FFFFFF);
    
    vdPrint("Free Blocks: ", 0x00FFFFFF);
    itoa(diagnostic.free_blocks, buffer, 10);
    vdPrint(buffer, 0x00FFFFFF);
    vdPrint("\n", 0x00FFFFFF);
	vdPrint("-----------------------------------", 0x00FFFFFF);


	
}