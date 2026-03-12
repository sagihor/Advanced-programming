#include "KeyValuePair.h"
#include <stdio.h>
#include <stdlib.h>

struct KeyValuePair_t{
    Element key;
    Element value;
    CopyFunction copy_key;
    CopyFunction copy_value;
    EqualFunction equal_key_func;
    PrintFunction print_key_func;
    PrintFunction print_value_func;
    FreeFunction free_key_func;
    FreeFunction free_value_func;
};

FreeFunction get_free_value_func(KeyValuePair pair) {
    return pair->free_value_func;
}

PrintFunction get_print_value_func(KeyValuePair pair) {
    return pair->print_value_func;
}

CopyFunction get_copy_value_func(KeyValuePair pair) {
    return pair->copy_value;
}

EqualFunction get_equal_value_func(KeyValuePair pair) {
    return pair->equal_key_func;
}


KeyValuePair createKeyValuePair(CopyFunction copy_key_function, CopyFunction copy_value_function,
                                FreeFunction free_key_function, FreeFunction free_value_function,
                                PrintFunction print_key_function, PrintFunction print_value_function,
                                EqualFunction equal_key_function, Element key, Element value) {
    if (free_key_function == NULL ||free_value_function == NULL ||
        copy_key_function == NULL || copy_value_function ==NULL ||
        print_key_function == NULL ||print_value_function == NULL ||
        equal_key_function == NULL) { return NULL; }
    KeyValuePair key_value_pair = malloc(sizeof(struct KeyValuePair_t));
    if (key_value_pair == NULL) {printf("A memory problem has been detected in the program");
        return NULL;}
    key_value_pair->copy_key = copy_key_function;
    key_value_pair->copy_value = copy_value_function;
    key_value_pair->equal_key_func = equal_key_function;
    key_value_pair->print_key_func = print_key_function;
    key_value_pair->print_value_func = print_value_function;
    key_value_pair->free_key_func = free_key_function;
    key_value_pair->free_value_func = free_value_function;
    key_value_pair->key = key;
    key_value_pair->value = value;
    return key_value_pair;
}

FreeFunction destroyKeyValuePair(KeyValuePair key_value_pair) {
    if (key_value_pair == NULL) {return NULL;}
    key_value_pair->free_key_func(key_value_pair->key);
    key_value_pair->free_value_func(key_value_pair->value);
    free(key_value_pair);
}

PrintFunction printKeyValuePair(KeyValuePair key_value_pair) {
    if (key_value_pair == NULL) {return NULL;}
    key_value_pair->print_key_func(key_value_pair->key);
    printf(" : ");
    key_value_pair->print_value_func(key_value_pair->value);
}

void displayValue(KeyValuePair key_value_pair) {
    if (key_value_pair == NULL) {return;}
    key_value_pair->print_value_func(key_value_pair->value);
}

void displayKey(KeyValuePair key_value_pair) {
    if (key_value_pair == NULL) {return;}
    key_value_pair->print_key_func(key_value_pair->key);
}

Element getValue(KeyValuePair key_value_pair) {
    if (key_value_pair == NULL) {return NULL;}
    return key_value_pair->value;
}

Element getKey(KeyValuePair key_value_pair) {
    if (key_value_pair == NULL) {return NULL;}
    return key_value_pair->key;
}

bool isEqualKey(KeyValuePair key_value_pair1, Element key) {
    if (key_value_pair1 == NULL) {return false;}
    return key_value_pair1->equal_key_func(key_value_pair1->key, key);
}
