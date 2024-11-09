/**
 * @file listADT.h
 * @brief Definition of the List Abstract Data Type (ADT) and related functions.
 */

#ifndef TListADT_H
#define TListADT_H

/**
 * @typedef TListADT
 * @brief A pointer to a concrete structure representing the list.
 */
typedef struct TListCDT* TListADT;

/**
 * @brief Creates a new list.
 *
 * @param cmp_func A comparison function to compare elements in the list.
 * @return A new initialized TListADT.
 */
TListADT create_list(int (*cmp_func)(const void*, const void*));

/**
 * @brief Inserts an element into the list.
 *
 * @param list The list.
 * @param element The element to insert.
 * @return 1 on success, 0 on failure.
 */
char insert_element(TListADT list, void* element);

/**
 * @brief Removes an element from the list.
 *
 * @param list The list.
 * @param element The element to remove.
 * @return 1 on success, 0 on failure.
 */
char remove_element(TListADT list, void* element);

/**
 * @brief Gets an element from the list.
 *
 * @param list The list.
 * @param element The element to get.
 * @return A pointer to the element, or NULL if the element is not found.
 */
void* get_element(TListADT list, void* element);

/**
 * @brief Destroys the list and frees all associated memory.
 *
 * @param list The list to destroy.
 */
void destroy_list(TListADT list);

#endif