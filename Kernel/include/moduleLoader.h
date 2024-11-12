#ifndef MODULELOADER_H
#define MODULELOADER_H

/**
 * @brief Loads modules from a payload into specified target addresses.
 *
 * @param payload_start Pointer to the start of the payload containing the modules.
 * @param module_target_address Array of pointers to the target addresses where the modules will be loaded.
 */
void load_modules(void * payload_start, void ** module_target_address);

#endif