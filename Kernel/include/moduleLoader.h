#ifndef MODULELOADER_H
#define MODULELOADER_H

/**
 * @brief Loads modules from a payload into specified target addresses.
 *
 * @param payloadStart Pointer to the start of the payload containing the modules.
 * @param moduleTargetAddress Array of pointers to the target addresses where the modules will be loaded.
 */
void load_modules(void * payloadStart, void ** moduleTargetAddress);

#endif