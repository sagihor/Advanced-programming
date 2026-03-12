
#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h";

struct hashTable_s{
    int size;
    LinkedList* table;
    TransformIntoNumberFunction transformIntoNumberFunc;
    CopyFunction copy_key;
    CopyFunction copy_value;
    EqualFunction equal_key_func;
    PrintFunction print_key_func;
    PrintFunction print_value_func;
    FreeFunction free_key_func;
    FreeFunction free_value_func;
};

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
    CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
    EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    if (copyKey == NULL || freeKey == NULL || printKey == NULL ||
        copyValue == NULL || freeValue == NULL || equalKey == NULL) {return NULL;}
    if (hashNumber < 1){return NULL;}


    hashTable ht = malloc(sizeof(struct hashTable_s));
    if (ht == NULL) {printf("A memory problem has been detected in the program"); return NULL;}
    ht->size = hashNumber;
    ht->table = malloc(sizeof(LinkedList) * ht->size);
    if (ht->table == NULL) {printf("A memory problem has been detected in the program"); return NULL;}

    //resets all the values in table
    for (int i = 0; i < ht->size; i++) {ht->table[i] = NULL;}

    ht->copy_key = copyKey;
    ht->copy_value = copyValue;
    ht->equal_key_func = equalKey;
    ht->print_key_func = printKey;
    ht->print_value_func = printValue;
    ht->free_key_func = freeKey;
    ht->free_value_func = freeValue;
    ht->transformIntoNumberFunc = transformIntoNumber;
    return ht;
}

status destroyHashTable(hashTable ht) {
    if (ht->table == NULL) {return failure;}
    for (int i = 0; i < ht->size; i++) {
            destroyLinkedList(ht->table[i]);
    }
    free(ht->table);
    free(ht);
    return success;
}

status addToHashTable(hashTable ht, Element key, Element value) {
    if (key == NULL || value == NULL) {return failure;}
    //creating key-value pair
    KeyValuePair kvp = createKeyValuePair(ht->copy_key, ht->copy_value,
        ht->free_key_func,ht->free_value_func,
        ht->print_key_func, ht->print_value_func,
        ht->equal_key_func, key, value);
    if (kvp == NULL) {return failure;}

    int index = ht->transformIntoNumberFunc(key) % ht->size;
    if (ht->table[index] == NULL) {
        ht->table[index] = createLinkedList(ht->copy_key, ht->free_key_func, ht->equal_key_func, ht->print_key_func);
    }
    appendNode(ht->table[index], kvp);
    return success;
}

Element lookupInHashTable(hashTable ht, Element key) {
    if (key == NULL || ht->equal_key_func == NULL) {return NULL;}
    //Getting the needed index by using hash function
    int index = ht->transformIntoNumberFunc(key) % ht->size;

    if (ht->table[index] == NULL) {return NULL;}
    KeyValuePair kvp = searchByKeyInList(ht->table[index], key);
    if (kvp == NULL) {return NULL;}

    return getValue(kvp);
}

status removeFromHashTable(hashTable ht, Element key) {
    if (ht == NULL) {return failure;}
    int index = ht->transformIntoNumberFunc(key) % ht->size;
    if (index > ht->size) {return failure;}
    if (ht->table[index] == NULL) {return failure;}
    return deleteNode(ht->table[index], key);
}

status displayHashElements(hashTable ht) {
    if (ht == NULL) {return failure;}
    for (int i = 0; i < ht->size; i++) {
        displayList(ht->table[i]);
    }
}
