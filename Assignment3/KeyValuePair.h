/**
*generic ADT to key and value pair
 */
#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H
#include "Defs.h"
typedef void* Element;
// typedef Element (*CopyFunction)(Element);
// typedef status (*FreeFunction)(Element);
// typedef bool (*EqualFunction)(Element, Element);
// typedef status (*PrintFunction)(Element);
//pointer to the struct
typedef struct KeyValuePair_t* KeyValuePair;
/**
 *create KeyValuePair
 */
KeyValuePair createKeyValuePair(CopyFunction copy_key,CopyFunction copy_val,
 FreeFunction free_key,FreeFunction free_val, PrintFunction print_key,
 PrintFunction print_val, EqualFunction equal_key_function, Element key, Element val);
/**
 *destroy KeyValuePair
 */
FreeFunction destroyKeyValuePair(KeyValuePair);
/**
 * print the value only
 */
PrintFunction printKeyValuePair(KeyValuePair);


void displayValue(KeyValuePair);
/**
 *print the key only
 */
void displayKey(KeyValuePair);
/**
 *This function receives pointer to KeyValuePair and returns the value
 */
Element getValue(KeyValuePair);
/**
 *This function receives pointer to KeyValuePair and returns the key
 */
Element getKey(KeyValuePair);
/**
 *This function indicates whether a given key is equal to a key in keyValuePair object
 */
bool isEqualKey(KeyValuePair, Element);

FreeFunction get_free_value_func(KeyValuePair);
PrintFunction get_print_value_func(KeyValuePair);
CopyFunction get_copy_value_func(KeyValuePair);
EqualFunction get_equal_value_func(KeyValuePair);
#endif //KEYVALUEPAIR_H
