/**
*Generic ADT to linked list that holds generic values and pointer to the next
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Defs.h"
typedef void* Element;
typedef Element (*CopyFunction)(Element);
typedef status (*FreeFunction)(Element);
typedef bool (*EqualFunction)(Element, Element);
typedef status (*PrintFunction)(Element);
typedef struct LinkedList_t* LinkedList;
/**create the LinkedList and returns pointer to the list*/
LinkedList createLinkedList(CopyFunction, FreeFunction, EqualFunction, PrintFunction);
/**destroy and free the memory given a pointer to a linked list*/
FreeFunction destroyLinkedList(LinkedList);
/**append a given element to the end of the list*/
void appendNode(LinkedList, Element);
/**delete a given element a returns a status whether the deletion was successful*/
status deleteNode(LinkedList, Element);
/**prints the list*/
void displayList(LinkedList);
/**returns the content of a node according to a given index*/
Element getDataByIndex(LinkedList, int index);
/**returns the size of the list*/
int getLengthList(LinkedList);
/**search an Element in the list and returns the element otherwise returns NULL*/
Element searchByKeyInList(LinkedList, Element);
#endif //LINKEDLIST_H
