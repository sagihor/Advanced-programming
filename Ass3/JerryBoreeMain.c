#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "Jerry.h"
#include "MultiValueHashTable.h"
#include "KeyValuePair.h"

typedef struct {
    hashTable jerries_hash_table;
    LinkedList planet_linked_list;
    MultiValueHashTable char_mv_hash_table;
    int planet_number;
}Reader;
status parse_planets(Reader* reader, char *line);
status parse_characteristics(Reader* reader, char *line);
status parse_jerries(Reader* reader, char *line);
Reader *parse_config_file(int size_planets, char *file_name);
//functions to send to create Linked List of planets
Element copy_planet_linked_list(Element);
status free_planet_linked_list(Element);
bool planets_equal(Element, Element);
status print_planet_linked_list(Element);
//functions to send to create hash table of Jerries with JerryID as key
Element copy_jerryID(Element);
status print_jerryID(Element);
status free_jerryID(Element);
Element copy_jerry(Element);
status print_jerry_hash_table(Element);
status free_jerry_hash_table (Element);
bool equal_jerryID(Element, Element);
int transformintoNumberJerryID(Element);
//functions to send to create multi value hash table with Characteristic name as a key
Element copy_phiChar_name(Element);
status print_phiChar_name(Element);
status free_phiChar_name(Element);
Element copy_Jerry_LL(Element);
status print_Jerry_LL(Element);
status free_Jerry_LL(Element);
bool equal_phiChar_name(Element, Element);
int transformintoNumberPhiChar_name(Element);


//implemeting four functions for my Linked List that contains planets
Element copy_planet_linked_list(Element planet) {
    Planet* p1 = planet;
    char *cpy_name = malloc(strlen(p1->name) + 1);
    strcpy(cpy_name, p1->name);
    return create_planet(cpy_name, p1->x, p1->y, p1->z);
}
status free_planet_linked_list(Element planet) {
    Planet* p1 = planet;
    if (p1 == NULL) {return failure;}
    free_planet(p1);
    return success;
}
bool planets_equal(Element planet1, Element planet2) {
    Planet* p1 = planet1;
    Planet* p2 = planet2;
    return strcmp(p1->name, p2->name) == 0;
}
status print_planet_linked_list(Element planet) {
    Planet* p1 = planet;
    if (p1 == NULL) {return failure;}
    print_planet(p1);
    return success;
}


//implement the functions to send to Jerries hash table with JerryID as a key and Jerry as value
Element copy_jerryID(Element jerry) {
    Jerry* jerry1 = jerry;
    char* name = malloc(strlen(jerry1->id) + 1);
    if (name == NULL) {printf("A memory problem has been detected in the program"); return NULL; }
    strcpy(name, jerry1->id);
    return name;
}

status print_jerryID(Element jerry) {
    Jerry* jerry1 = jerry;
    if (jerry == NULL) {return failure;}
    printf("Jerry ID:%s", jerry1->id);
    return success;
}

status free_jerryID(Element jerry) {
    Jerry* jerry1 = jerry;
    if (jerry == NULL) {return failure;}
    free(jerry1->id);
    return success;
}

Element copy_jerry(Element jerry) {
    Jerry* jerry1 = jerry;
    char* name = malloc(strlen(jerry1->id) + 1);
    if (name == NULL) {
        printf("A memory problem has been detected in the program");
        return NULL;
    }
    strcpy(name, jerry1->id);
    Physical_characteristic** new_phi_char = malloc(jerry1->arr_size * sizeof(Physical_characteristic*));
    for (int i = 0; i < jerry1->arr_size; i++) {
        new_phi_char[i] = create_phi_char(jerry1->phi_arr[i]->name, jerry1->phi_arr[i]->val);
    }
    return create_jerry(name, jerry1->happiness, jerry1->origin, new_phi_char);
}

status free_jerry_hash_table(Element jerry) {
    Jerry* jerry1 = jerry;
    if (jerry1 == NULL) {return failure;}
    free_Jerry(jerry1);
    return success;
}

status print_jerry_hash_table(Element jerry) {
    Jerry* jerry1 = jerry;
    if (jerry1 == NULL) {return failure;}
    print_jerry(jerry1);
    return success;
}

bool equal_jerryID(Element j1, Element j2) {
    Jerry* jerry1 = j1;
    Jerry* jerry2 = j2;
    return strcmp(jerry1->id, jerry2->id) == 0;
}

int transformintoNumberJerryID(Element jerry) {
    Jerry* jerry1 = jerry;
    int sum = 0;
    for (int i = 0; i < strlen(jerry1->id); i++) {
        sum = sum + jerry1->id[i];
    }
    return sum;
}
//

//implementation of functions  to create Multi value hash table with physical characteristic name as a key and jerries that has this characteristic as value
Element copy_phiChar_name(Element phi_char) {
    Physical_characteristic* phi_char1 = phi_char;
    char* name = malloc(strlen(phi_char1->name) + 1);
    strcpy(name, phi_char1->name);
    return name;
}

status print_phiChar_name(Element phi_char) {
    Physical_characteristic* phi_char1 = phi_char;
    printf("%s\n", phi_char1->name);
    return success;
}

status free_phiChar_name(Element phi_char) {
    Physical_characteristic* phi_char1 = phi_char;
    free(phi_char1->name);
    return success;
}

Element copy_Jerry_LL(Element) {
    return ;
}

status print_Jerry_LL(Element list) {
    LinkedList list1 = list;
    if (list1 == NULL) {return failure;}
    displayList(list1);
    return success;
}

status free_Jerry_LL(Element) {
    return success;
}

bool equal_phiChar_name(Element phichar1, Element phichar2) {
    Physical_characteristic* p_char1 = phichar1;
    Physical_characteristic* p_char2 = phichar2;
    return strcmp(p_char1->name, p_char2->name) == 0;
}

int transformintoNumberPhiChar_name(Element phichar) {
    Physical_characteristic* p_char1 = phichar;
    int sum = 0;
    char *char_name = p_char1->name;
    for (int i = 0; i < strlen(char_name); i++) {
        sum = sum + char_name[i];
    }
    return sum;
}

//

status parse_planets(Reader* reader, char *line) {
    char name[50];
    double x, y, z;
    if (sscanf(line, "%49[^,],%lf,%lf,%lf", name, &x, &y, &z) == 4) {
        appendNode(reader->planet_linked_list, create_planet(name, x, y, z));
    }
    return success;
}

status parse_characteristics(Reader* reader, char *line) {
}

status parse_jerries(Reader* reader, char *line) {
    char id[50];
    char planet_name[50];
    char dmn_name[50];
    unsigned int happiness;
    if (reader == NULL) {return failure;}
    if (line == NULL) {return failure;}
    if (sscanf(line, "%49[^,],%49[^,],%49[^,],%u", id, dmn_name, planet_name, &happiness) == 4) {
    }
}

Reader *parse_config_file(int size_planets, char *file_name){
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("problem with file num %s\n", file_name);
        return NULL;
    }
    Reader *reader = malloc(sizeof(Reader));
    if(reader == NULL) {
        printf("Memory allocation error");
        fclose(file);
        return NULL;
    }
    reader->planet_linked_list = createLinkedList(copy_planet_linked_list, free_planet_linked_list, planets_equal, print_planet_linked_list);
    if(reader->planet_linked_list == NULL) {
        printf("A memory problem has been detected in the program");
        fclose(file);
        return NULL;
    }
    reader->jerries_hash_table = createHashTable(copy_jerryID, free_jerryID,
        print_jerryID, copy_jerry, free_jerry_hash_table, print_jerry_hash_table,
        equal_jerryID, transformintoNumberJerryID, 11);
    if(reader->jerries_hash_table == NULL) {
        printf("Memory allocation error");
        fclose(file);
        return NULL;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) { //reading the file line-by-line until EOF
        if (strncmp(line, "Planets", strlen("Planets")) == 0) {//we reached the Planets section
            while (strncmp(line, "Jerries", 7) != 0) {
                fgets(line, sizeof(line), file); //go to the next line
                parse_planets(reader->planet_linked_list, line);
            }
        }
        if (strncmp(line, "Jerries", strlen("Jerries")) == 0) {
            while (fgets(line, sizeof(line), file)) {
                if (line[0] == '\t') { //recognize a tab so we parse characteristic
                    parse_characteristic(reader->jerries[reader->jerries_count - 1], line);
                }
                else {
                    parse_jerries(reader, line, &(reader->jerries_count));
                }
            }
        }
        return reader;
    }
}

void load_menu() {
    printf("Welcome Rick, what are your Jerry's needs today ? \n");
    printf("1 : Take this Jerry away from me \n");
    printf("2 : I think I remember something about my Jerry \n");
    printf("3 : Oh wait. That can't be right \n");
    printf("4 : I guess I will take back my Jerry now \n");
    printf("5 : I can't find my Jerry. Just give me a similar one \n");
    printf("6 : I lost a bet. Give me your saddest Jerry \n");
    printf("7 : Show me what you got \n");
    printf("8 : Let the Jerries play \n");
    printf("9 : I had enough. Close this place \n");
}

int main(int argc, char *argv[]) {
    Reader* reader = parse_config_file(2, "configuration_file(1).txt");
    displayList(reader->planet_linked_list);
}