
#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H
#include "Defs.h"
#include "LinkedList.h"
typedef struct MultiValueHashTable_s* MultiValueHashTable;

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
    CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
    EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(MultiValueHashTable multiValueHashTable);
status addToMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element value);
LinkedList lookupinMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key);
status removeFromMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element value);
void printMultiValueHashTable(MultiValueHashTable multiValueHashTable);

#endif //MULTIVALUEHASHTABLE_H
