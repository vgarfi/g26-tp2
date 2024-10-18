#include <string.h>
#include <synchro/synchro.h>
#include <memory/memoryManagerADT.h>
#include <structures/listADT.h>

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
    
}
void wait_sem(char* name) {

}
void post_sem(char* name) {

}
void delete_sem(char* name) {

}