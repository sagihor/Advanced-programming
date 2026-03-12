
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MultiValueHashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "HashTable.h"
struct MultiValueHashTable_s {
    hashTable hashTable;
    CopyFunction copy_val;
    FreeFunction free_val;
    PrintFunction print_val;
    EqualFunction equal_key;
};

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
    CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
    TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    if (copyKey == NULL || freeKey == NULL || printKey == NULL
        || copyValue == NULL || freeValue == NULL || transformIntoNumber == NULL
        ||equalKey == NULL || printValue == NULL){return NULL;}
    if (hashNumber < 1) {return NULL;}
    MultiValueHashTable multihashTable;
    multihashTable = (MultiValueHashTable)malloc(sizeof(struct MultiValueHashTable_s));
    if (multihashTable == NULL) {return NULL;}
    multihashTable ->hashTable = createHashTable(copyKey, freeKey, printKey, copyValue,
        freeValue, printValue, equalKey, transformIntoNumber, hashNumber);
    multihashTable -> copy_val = copyValue;
    multihashTable -> free_val = freeValue;
    multihashTable -> print_val = printValue;
    multihashTable -> equal_key = equalKey;
    if (multihashTable -> hashTable == NULL) {return NULL;}
    return multihashTable;
}

status destroyMultiValueHashTable(MultiValueHashTable multiValueHashTable) {
    if (multiValueHashTable == NULL){return failure;}
    destroyHashTable(multiValueHashTable -> hashTable);
    free(multiValueHashTable);
    return success;
}

status addToMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element value) {
    if (multiValueHashTable == NULL){return failure;}
    if (key == NULL || value == NULL){return failure;}
    if (multiValueHashTable -> hashTable == NULL) {return failure;}
    KeyValuePair pair =(KeyValuePair) lookupInHashTable(multiValueHashTable -> hashTable, key);
    if (pair == NULL) {//need to add key value pair
        LinkedList list = createLinkedList(multiValueHashTable -> copy_val , multiValueHashTable -> free_val,
            multiValueHashTable -> equal_key, multiValueHashTable -> print_val);
        if (list == NULL) {printf("A memory problem has been detected in the program");
            return failure;}
        addToHashTable(multiValueHashTable -> hashTable, key, list);
    }
    else { //add to existing list
        appendNode(getValue(pair), value);
    }
    return success;
}

LinkedList lookupinMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key) {
  if (multiValueHashTable == NULL){return NULL;}
  if (key == NULL){return NULL;}
  if (lookupInHashTable(multiValueHashTable -> hashTable, key) == NULL) {
      return NULL;
  }
   LinkedList list = lookupInHashTable(multiValueHashTable -> hashTable, key);
    return list;
}

status removeFromMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element value) {
  if (multiValueHashTable == NULL){return failure;}
  if (key == NULL || value == NULL){return failure;}
  if (multiValueHashTable -> hashTable == NULL) {return failure;}
    // Look up the list of values for the given key
    LinkedList list = (LinkedList)lookupInHashTable(multiValueHashTable->hashTable, key);
    if (list == NULL) { return failure; }

    // Remove the value from the linked list
    status status = deleteNode(list, value);
    if (status == failure) { return failure; }

    // If the list is empty after removal, remove the key-value pair from the hash table
    if (getLengthList(list) == 0) {
        removeFromHashTable(multiValueHashTable->hashTable, key);
    }

    return success;
}

void printMultiValueHashTable(MultiValueHashTable multiValueHashTable) {
  if (multiValueHashTable == NULL){return;}
  if (multiValueHashTable -> hashTable == NULL){return;}
  displayHashElements(multiValueHashTable -> hashTable);
}
