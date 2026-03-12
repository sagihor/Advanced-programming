#include "Jerry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Jerry * create_jerry(char *id, unsigned int hap, Origin *org, Physical_characteristic **phi_arr) {
    Jerry *jerryP = (Jerry *) malloc(sizeof(Jerry));
    if (jerryP == NULL) {
        return NULL;
    } //allocation wasn't successful
    jerryP->id = (char*) malloc(strlen(id) + 1); //adding 1 for null terminator
    if (jerryP->id == NULL) {printf("Memory Problem\n"); free_Jerry(jerryP); return NULL;} //allocation failed
    strcpy(jerryP->id, id);
    jerryP->happiness = hap;
    jerryP->origin = org;
    jerryP->phi_arr = phi_arr;
    jerryP->arr_size = 0;
    return jerryP;
}

Planet * create_planet(char *name, double x, double y, double z) {
    Planet * planetP = (Planet *) malloc(sizeof(Planet));
    if (planetP == NULL) {
        return NULL;
    }
    planetP->name =(char*) malloc(strlen(name) + 1);
    if (planetP->name == NULL) {printf("Memory Problem\n");free_planet(planetP); return NULL;}
    strcpy(planetP->name, name);
    planetP->x = x;
    planetP->y = y;
    planetP->z = z;
    return planetP;
}

Physical_characteristic * create_phi_char(char *name, double val) {
    Physical_characteristic * phi_charP = (Physical_characteristic *) malloc(sizeof(Physical_characteristic));
    if (phi_charP == NULL) {
        return NULL;
    } //allocation wasn't successful
    phi_charP->name =(char*) malloc(strlen(name) + 1);
    if (phi_charP->name == NULL) {printf("Memory Problem\n"); free_physical_characteristic(phi_charP); return NULL;} //allocation failed
    strcpy(phi_charP->name, name);
    phi_charP->val = val;
    return phi_charP;
}

Origin * create_origin(Planet *planet, char *dmn_name) {
    Origin * originP = (Origin *) malloc(sizeof(Origin));
    if (originP == NULL) {
        return NULL;
    } //allocation wasn't successful
    originP->dmn_name = (char*) malloc(strlen(dmn_name) + 1);
    if (originP->dmn_name == NULL) {printf("Memory Problem\n"); free_origin(originP); return NULL;} //allocation failed
    strcpy(originP->dmn_name, dmn_name);
    originP->planet = planet;
    return originP;
}

void free_planet(Planet *planet) {
    if (planet == NULL) {return;}
    free(planet->name);
    free(planet);
}

void free_origin(Origin *origin) {
    if (origin == NULL) {return;}
    free(origin->dmn_name);
    free_planet(origin->planet);
    free(origin);
}

void free_physical_characteristic(Physical_characteristic *phi_char) {
    if (phi_char == NULL) {return;}
    free(phi_char->name);
    free(phi_char);
    phi_char = NULL;
}

void free_Jerry(Jerry *jerry) { //releasing memory inside-out
    if (jerry == NULL) {return;}
    free(jerry->id);
    free_origin(jerry->origin);
    //Destroy the content of each characteristic
    for (int i = 0; i < jerry->arr_size; i++) {
        free_physical_characteristic(jerry->phi_arr[i]);
    }
    //Destroy the pointer to the characteristic array
    free(jerry->phi_arr);
    free(jerry);
}

bool has_characteristics(Jerry *jerry, char* name) {
    if (jerry == NULL) { //Jerry object is empty
        return false;
    }
    Physical_characteristic** arr = jerry->phi_arr;
    for (int i = 0; i < jerry->arr_size; i++) {
        if (strcmp(arr[i]->name, name) == 0) {
            return true;
        }
    }
    return false;
}

status add_characteristics(Jerry *jerry, char* name, double val) {
    if (jerry == NULL || name == NULL) {
        return failure;
    }

    // Create a new Physical_characteristic object
    Physical_characteristic* phi_char = create_phi_char(name, val);
    if (phi_char == NULL) {
        printf("Memory problem\n");
        return failure;
    }

    // Increase the array size by 1
    jerry->arr_size++;

    // Reallocate memory for the new size
    jerry->phi_arr = (Physical_characteristic**) realloc(jerry->phi_arr, sizeof(Physical_characteristic*) * jerry->arr_size);
    if (jerry->phi_arr == NULL) {
        printf("Memory problem\n");
        free_physical_characteristic(phi_char);
        return failure;  // Allocation failed
    }

    // Add the new characteristic to the last position
    jerry->phi_arr[jerry->arr_size - 1] = phi_char;

    return success;
}

status del_characteristics(Jerry *jerry, char name[20]) {
    if (jerry == NULL || jerry->phi_arr == NULL || jerry->arr_size == 0) {
        return failure;  // No characteristics to delete
    }
    int index_to_delete = -1;

    // Find the characteristic to delete
    for (int i = 0; i < jerry->arr_size; i++) {
        if (strcmp(jerry->phi_arr[i]->name, name) == 0) {
            index_to_delete = i;
            break;
        }
    }

    // Characteristic not found
    if (index_to_delete == -1) {
        return failure;
    }
    free_physical_characteristic(jerry->phi_arr[index_to_delete]);
    for (int i = index_to_delete; i < jerry->arr_size - 1; i++) {
        jerry->phi_arr[i] = jerry->phi_arr[i + 1];
    }
    if (jerry->arr_size - 1 != 0) {
        jerry->phi_arr[jerry->arr_size - 1] = NULL;
    }
    jerry->arr_size--;

    //if I removed the last one - no need to realloc
    if (jerry->arr_size != 0) {
        jerry->phi_arr = (Physical_characteristic**) realloc(jerry->phi_arr, sizeof(Physical_characteristic*) * jerry->arr_size);
        if (jerry->phi_arr == NULL) {return failure;}
    }
    return success;
}
Planet* copy_planet(Planet* planet) {
    if (planet == NULL) {return NULL;}
    Planet* planetP = (Planet*) malloc(sizeof(Planet));
    if (planetP == NULL) {printf("Memory problem\n");return NULL;}
    planetP->x = planet->x;
    planetP->y = planet->y;
    planetP->z = planet->z;
    planetP->name = (char*)malloc(strlen(planet->name) + 1);
    strcpy(planetP->name, planet->name);
    if (planetP->name == NULL) {
        free_planet(planet);
        printf("Memory problem\n");
        return NULL;}
    return planetP;
}
    void print_jerry(Jerry *jerry){
        if (jerry == NULL) {return;}
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %u \n", jerry->happiness);
    printf("Origin : %s \n", jerry->origin->dmn_name);
    printf("Planet : %s (%.2f,%.2f,%.2f) ", jerry->origin->planet->name, jerry->origin->planet->x,
           jerry->origin->planet->y, jerry->origin->planet->z);
    if (jerry->arr_size != 0) {
        printf("\n");
        printf("Jerry's physical Characteristics available : \n");
        printf("\t");
        for (int i = 0; i < jerry->arr_size; i++) {
            if (i == jerry->arr_size - 1) {
                // No trailing comma after the last element
                printf("%s : %.2f ", jerry->phi_arr[i]->name, jerry->phi_arr[i]->val);
            } else {
                printf("%s : %.2f , ", jerry->phi_arr[i]->name, jerry->phi_arr[i]->val);
            }
        }
    }
}

void print_planet(Planet *planet) {
    if(planet == NULL){return;}
    printf("Planet : %s (", planet->name);
    printf("%.2f, ", planet->x);
    printf("%.2f, ", planet->y);
    printf("%.2f) ", planet->z);
    printf("\n");
}


