#ifndef TListADT_H
#define TListADT_H


typedef struct TListCDT* TListADT;

TListADT create_list(int (*cmpFunc)(const void*, const void*));
char insert_element(TListADT list, void* element);
char remove_element(TListADT list, void* element);
void destroy_list(TListADT list);

#endif