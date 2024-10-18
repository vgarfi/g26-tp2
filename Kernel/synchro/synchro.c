#include <string.h>
#include <synchro/synchro.h>
#include <memory/memoryManagerADT.h>
#include <structures/listADT.h>
#include <structures/queueADT.h>
#include <scheduler/scheduler.h>
#include <process/process.h>

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
    	return;
	}

	strcpy(new_semaphore->name, name);
    new_semaphore->value = initial_value;

    char insertion = insert_element(semaphore_list, new_semaphore);
    if (!insertion) {
        free_mm(memory_manager, new_semaphore);
        return NULL;
    }

    return new_semaphore;
}

TSemaphore* get_sem(char* name) {
    TSemaphore* new_semaphore = (TSemaphore*) malloc_mm(memory_manager, sizeof(TSemaphore));
    if(new_semaphore == NULL)
        return NULL;
    
    new_semaphore->name = name;

    TSemaphore* looked_semaphore = get_element(semaphore_list, new_semaphore);
    
    free_mm(memory_manager, new_semaphore);

    return (TSemaphore*) looked_semaphore;
}

void wait_sem(char* name) {
    TSemaphore* new_semaphore = (TSemaphore*) malloc_mm(memory_manager, sizeof(TSemaphore));
    if(new_semaphore == NULL)
        return NULL;
    
    new_semaphore->name = name;

    TSemaphore* looked_semaphore = get_element(semaphore_list, new_semaphore);
    
    free_mm(memory_manager, new_semaphore);

    if(looked_semaphore->value > 0){
        looked_semaphore--;
    }else{
        uint8_t current_pid = get_current_pid();
        enqueue(looked_semaphore->waiting_processes, current_pid);
        block_process(current_pid); // TODO: handle de la salida no exitosa
    }
    return;
}

void post_sem(char* name) {

}

void delete_sem(char* name) {

}