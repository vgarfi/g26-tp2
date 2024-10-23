#include <string.h>
#include <synchro/synchro.h>
#include <memory/memoryManagerADT.h>
#include <structures/listADT.h>
#include <structures/queueADT.h>
#include <scheduler/scheduler.h>
#include <process/process.h>
#include <videoDriver.h>

extern MemoryManagerADT memory_manager;

TListADT semaphore_list;

int compare_sempaphore(const void* sem_1, const void* sem_2) {
    return strcmp(((TSemaphore*)sem_1)->name, ((TSemaphore*)sem_2)->name);
}

char initialize_synchro(void) {
    semaphore_list = create_list(compare_sempaphore);
    if (semaphore_list == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

TSemaphore* create_sem(char* name, uint64_t initial_value) {
    TSemaphore* new_semaphore = (TSemaphore*) malloc_mm(memory_manager, sizeof(TSemaphore));
    if (new_semaphore == NULL) {
        return NULL;
    }

	new_semaphore->name = (char *) malloc_mm(memory_manager, strlen(name) + 1);
	if (new_semaphore->name == NULL) {
        free_mm(memory_manager, new_semaphore);
    	return NULL;
	}

	strcpy(new_semaphore->name, name);
    new_semaphore->value = initial_value;

    char insertion = insert_element(semaphore_list, new_semaphore);
    if (!insertion) {    
        vdPrint("Semaforo ", 0x00FF0000);
        vdPrint(name, 0x00FF0000);
        vdPrint(" no se pudo ingresar a la lista\n", 0x00FF0000);
        free_mm(memory_manager, new_semaphore->name);
        free_mm(memory_manager, new_semaphore);
        return NULL;
    }
    
    vdPrint("Semaforo ", 0x00FFFFFF);
    vdPrint(name, 0x00FFFFFF);
    vdPrint(" ingresado a la lista con exito\n", 0x00FFFFFF);
    return new_semaphore;
}

TSemaphore* get_sem(char* name) {
    TSemaphore temp_semaphore;
    temp_semaphore.name = name;

    TSemaphore* looked_semaphore = (TSemaphore*) get_element(semaphore_list, &temp_semaphore);

    if (looked_semaphore != NULL) {
    vdPrint("Semaforo ", 0x00FFFFFF);
    vdPrint(name, 0x00FFFFFF);
    vdPrint(" geteado con exito\n", 0x00FFFFFF);
    } else {
        
        vdPrint("Semaforo ", 0x00FF0000);
        vdPrint(name, 0x00FF0000);
        vdPrint(" no se pudo getear\n", 0x00FF0000);
    }
    

    return looked_semaphore;
}

void wait_sem(char* name) {
    TSemaphore* looked_semaphore = get_sem(name);    
    if (looked_semaphore == NULL){
        
        vdPrint("Semaforo ", 0x00FF0000);
        vdPrint(name, 0x00FF0000);
        vdPrint(" no se pudo hacer wait\n", 0x00FF0000);
        return;
    }

    if(looked_semaphore->value > 0){
        looked_semaphore->value--;
            
        vdPrint("Semaforo ", 0x00FFFFFF);
        vdPrint(name, 0x00FFFFFF);
        vdPrint(" decrementado con exito\n", 0x00FFFFFF);
    }else{
        uint8_t current_pid = get_current_pid();
        enqueue(looked_semaphore->waiting_processes, current_pid);
            
        vdPrint("Semaforo ", 0x00FFFFFF);
        vdPrint(name, 0x00FFFFFF);
        vdPrint(" hizo que el proceso actual se bloquee\n", 0x00FFFFFF);
        block_process(current_pid); // TODO: handle de la salida no exitosa
    }
    return;
}

void post_sem(char* name) {
    TSemaphore* looked_semaphore = get_sem(name);   
    if (looked_semaphore == NULL){
        return;
    }

    if(is_empty(looked_semaphore->waiting_processes)){
        looked_semaphore->value = looked_semaphore->value + 1;
        
        vdPrint("Semaforo ", 0x00FFFFFF);
        vdPrint(name, 0x00FFFFFF);
        vdPrint(" aumentado con exito\n", 0x00FFFFFF);
    } else {
        uint8_t first_pid = dequeue(looked_semaphore->waiting_processes);
        
        vdPrint("Semaforo ", 0x00FFFFFF);
        vdPrint(name, 0x00FFFFFF);
        vdPrint(" hizo que el proceso actual se desbloquee\n", 0x00FFFFFF);
        unblock_process(first_pid);
    }
    return;
}

void delete_sem(char* name) {
    TSemaphore* looked_semaphore = get_sem(name);
    if (looked_semaphore == NULL){
        
        vdPrint("Semaforo ", 0x00FF0000);
        vdPrint(name, 0x00FF0000);
        vdPrint(" no se pudo hacer delete\n", 0x00FF0000);
        return;
    }

    while (!is_empty(looked_semaphore->waiting_processes)) // TODO chequear que is_empty funciona bien
    {
        uint8_t first_pid = dequeue(looked_semaphore->waiting_processes);
        unblock_process(first_pid);
        vdPrint("Semaforo ", 0x00FFFFFF);
        vdPrint(name, 0x00FFFFFF);
        vdPrint(" ha desbloqueado un proceso (loop)\n", 0x00FFFFFF);
        
        vdPrint("El looked vale ", 0x00FFFFFF);
        vdPrint(looked_semaphore->name, 0x00FFFFFF);
        vdPrint("\n", 0x00FFFFFF);
        
        dump(looked_semaphore->waiting_processes);
    }
    
    free_mm(memory_manager, looked_semaphore->name);
    free_mm(memory_manager, looked_semaphore);

    
    vdPrint("Semaforo ", 0x00FFFFFF);
    vdPrint(name, 0x00FFFFFF);
    vdPrint(" ha sido eliminado\n", 0x00FFFFFF);

    return;
}