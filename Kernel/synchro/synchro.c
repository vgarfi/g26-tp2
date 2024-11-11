// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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

void acquire(uint8_t* lock);
void release(uint8_t* lock);

uint8_t create_lock = 1;

int compare_sempaphore(const void* sem_1, const void* sem_2) {
    if (sem_1 == NULL || sem_2 == NULL) return 0;
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
    acquire(&create_lock);

    TSemaphore* sem = get_sem(name);
    if (sem != NULL) { 
        release(&create_lock);
        return sem;
    }

    TSemaphore* new_semaphore = (TSemaphore*) malloc_mm(memory_manager, sizeof(TSemaphore));
    if (new_semaphore == NULL || name == NULL) {
        release(&create_lock);
        return NULL;
    }

    new_semaphore->waiting_processes = create_queue();
    new_semaphore->lock = 1;

	new_semaphore->name = (char *) malloc_mm(memory_manager, strlen(name) + 1);
	if (new_semaphore->name == NULL) {
        release(&create_lock);
        free_mm(memory_manager, new_semaphore);
    	return NULL;
	}

	strcpy(new_semaphore->name, name);
    new_semaphore->value = initial_value;

    char insertion = insert_element(semaphore_list, new_semaphore);
    if (!insertion) {
        release(&create_lock);
        free_mm(memory_manager, new_semaphore->name);
        free_mm(memory_manager, new_semaphore);
        return NULL;
    }
    
    release(&create_lock);
    return new_semaphore;
}

TSemaphore* get_sem(char* name) {
    TSemaphore temp_semaphore;
    temp_semaphore.name = name;

    TSemaphore* looked_semaphore = (TSemaphore*) get_element(semaphore_list, &temp_semaphore);

    return looked_semaphore;
}

void wait_sem(char* name) {
    TSemaphore* looked_semaphore = get_sem(name);
    if (looked_semaphore == NULL){
        return;
    }

    acquire(&looked_semaphore->lock);

    if (looked_semaphore->value == 0) {
        uint8_t current_pid = get_current_pid();
        enqueue(looked_semaphore->waiting_processes, current_pid);
        release(&looked_semaphore->lock);
        block_process(current_pid);
        return;
    } else looked_semaphore->value--;

    release(&looked_semaphore->lock);

    return;
}

void post_sem(char* name) {
    TSemaphore* looked_semaphore = get_sem(name);   
    if (looked_semaphore == NULL){
        return;
    }

    acquire(&looked_semaphore->lock);

    if(!is_empty(looked_semaphore->waiting_processes)){
        uint8_t first_pid = (uint8_t)(uintptr_t)dequeue(looked_semaphore->waiting_processes);
        unblock_process(first_pid);
    } else looked_semaphore->value++;

    release(&looked_semaphore->lock);

    return;
}

void delete_sem(char* name) {
    TSemaphore* looked_semaphore = get_sem(name);
    if (looked_semaphore == NULL){
        return;
    }

    acquire(&looked_semaphore->lock);
    while (!is_empty(looked_semaphore->waiting_processes))
    {
        uint8_t first_pid = (uint8_t)(uintptr_t)dequeue(looked_semaphore->waiting_processes);
        unblock_process(first_pid);
    }

    destroy_queue(looked_semaphore->waiting_processes);

    remove_element(semaphore_list, looked_semaphore);
    
    free_mm(memory_manager, looked_semaphore->name);
    free_mm(memory_manager, looked_semaphore);
    return;
}