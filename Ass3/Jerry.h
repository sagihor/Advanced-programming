
#ifndef JERRY_H
#define JERRY_H
#include "Defs.h"

/*planet object contain its name and coordinate its location in space */
typedef struct Planet_t {
    char *name;
    double x;
    double y;
    double z;
}Planet;


/*this one describe an origin of a Jerry, in which planet the
 * jerry comes from and its dimension name
 */
typedef struct Origin_t {
    Planet* planet;
    char *dmn_name;
}Origin;


/*this one describes o phisycal treatment by a name and a numeric value*/
typedef struct Physical_characteristic_t {
    char *name;
    double val;
}Physical_characteristic;
/*a creature that has a name, id, level of happiness, a dynamic list of characteristics
 * and origin
 */


typedef struct Jerry_t {
    char *id;
    unsigned int happiness; //the range is 0-100 so im using unsigned to make sure it cant get negative numbers
    Origin *origin;
    Physical_characteristic **phi_arr; //a pointer to an array of characteristic every cell in the array is a pointer itself
    int arr_size;
}Jerry;

/*this one creates a jerry object*/
Jerry* create_jerry(char* id, unsigned int hap ,Origin* org, Physical_characteristic** phi_arr);

/*this one creates a Planet object*/
Planet* create_planet(char* name, double x, double y , double z);

/*this one creates a characteristic*/
Physical_characteristic* create_phi_char(char* name, double val);

/*this one creates an origin object and returns a status whether the creation was successful*/
Origin* create_origin(Planet* planet, char* dmn_name);

/*this ones checks if specific characteristic can be found in a Jerry*/
bool has_characteristics(Jerry* jerry, char name[20]);

/*this one adds a characteristic to a Jerry and indicates whether the addition was successful*/
status add_characteristics(Jerry* jerry, char* name, double val);

/*this one delets a characteristic to a Jerry and indicates whether the deletion was successful*/
status del_characteristics(Jerry* jerry, char name[20]);

/*this one creates a copy of a planet*/
Planet* copy_planet(Planet* planet);

/*this one destroy planet*/
void free_origin(Origin* origin);

/*this one destroy physical characteristic*/
void free_physical_characteristic(Physical_characteristic* phi_char);

/*this one destroy planet*/
void free_planet(Planet* planet);

/*this one destroy Jerry*/
void free_Jerry(Jerry* jerry);

/*this one prints a Jerry object according to a given format*/
void print_jerry(Jerry* jerry);

/*this one prints a Planet object according to a given format*/
void print_planet(Planet* planet);
#endif
