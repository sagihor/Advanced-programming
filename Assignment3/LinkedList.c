/*The implementation file of LinkedList*/
#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
/*Node struct represents a block that contains Data and pointer to the next*/
typedef struct node_t {
    Element data;
    struct node_t* next;
}Node;
/* a structure that represents a generic Linked List*/
struct LinkedList_t {
    /* The LinkedList is implemented by a pointer to its head and tail. and each
     * addition or deletion its head/tail is updated
     */
    Node* head;
    Node* tail;
    CopyFunction copy_func;
    FreeFunction free_func;
    EqualFunction equal_func;
    PrintFunction print_func;
};

LinkedList createLinkedList(CopyFunction copy_function, FreeFunction free_function,
    EqualFunction equal_function, PrintFunction print_function) {
    if (copy_function == NULL || free_function == NULL ||
        equal_function == NULL || print_function == NULL) {return NULL;}
    LinkedList linked_list = malloc(sizeof(struct LinkedList_t));
    if (linked_list == NULL) {printf("A memory problem has been detected in the program"); return NULL;}
    linked_list->head = NULL;
    linked_list->tail = NULL;
    linked_list->equal_func = equal_function;
    linked_list->copy_func = copy_function;
    linked_list->free_func = free_function;
    linked_list->print_func = print_function;
    return linked_list;
}

FreeFunction destroyLinkedList(LinkedList lst) {
    Node* tmp;
    tmp = lst->head;
    while (tmp != NULL) {
        Node* next_node = tmp->next;  // Save the next node before freeing
        lst->free_func(tmp->data);    // Free the data of the node
        free(tmp);                    // Free the node itself
        tmp = next_node;              // Move to the next node
    }
    free(lst);
}

void appendNode(LinkedList list, Element elem) {
    Node* new_node = malloc(sizeof(struct node_t));
    if (new_node == NULL) {printf("A memory problem has been detected in the program"); return;}
    new_node->data = elem;
    new_node->next = NULL;

    if (list -> tail == NULL) {//the list is empty
        list -> tail = new_node;
        list -> head = new_node;
    }
    else {
        list ->tail->next = new_node;
        list -> tail = new_node;
    }
}

status deleteNode(LinkedList list, Element elem) {
    if (list == NULL || list->head == NULL || list->tail == NULL || elem == NULL) {
        return failure;
    }

    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (list->equal_func(temp->data, elem)) {
            if (prev == NULL) {  // If deleting the head node
                list->head = temp->next;
                if (list->head == NULL) {  // If the list becomes empty
                    list->tail = NULL;
                }
            } else {  // If deleting a middle or tail node
                prev->next = temp->next;
                if (temp == list->tail) {
                    list->tail = prev;
                }
            }
            list->free_func(temp->data);  // Free the data
            free(temp);                   // Free the node
            return success;
        }
        prev = temp;
        temp = temp->next;
    }

    return failure;
}

void displayList(LinkedList list){
    Node* temp = list->head;
    while (temp != NULL) {
        list->print_func(temp->data);
        temp = temp->next;
    }
}

Element getDataByIndex(LinkedList list, int index) {
    int i;
    i = 0;
    if (list == NULL || list->head == NULL || list->tail == NULL) {return NULL;}
    Node* temp = list->head;
    while (temp != NULL) {
        if (index == i) {return temp->data;}
        temp = temp->next;
        i = i + 1;
    }
    return NULL;
}

int getLengthList(LinkedList list){
        int length = 0;
        Node* temp = list->head;
        while (temp != NULL) {
            length++;
            temp = temp->next;
        }
        return length;
}

Element searchByKeyInList(LinkedList list, Element elem) {
    if (list == NULL || list->head == NULL || list->tail == NULL) {return NULL;}
    Node* temp = list->head;
    while (temp != NULL) {
        if (list->equal_func(temp->data, elem) == 0) {
            return temp->data;
        }
        temp = temp->next;
    }
    return NULL;
}
