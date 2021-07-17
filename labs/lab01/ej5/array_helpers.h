#ifndef ARRAY_HELPERS
#define ARRAY_HELPERS

unsigned int array_from_stdin(int array[], unsigned int max_size, const char *filepath);
/*
    Cumple una las veces de funcion y de procedimiento.
    Toma los datos de stdin (el archivo asociado con la terminal), es decir le pide al usuario los datos
    Como funcion: devuelve un unsigned int, este numero es el tamñod el arreglo que llenaremos
    Como procedimiento: recorre el arreglo hasta size-1 llenandolo con los valores ingresados
*/
unsigned int array_from_file(int array[], unsigned int size, char *filepath);
/*
    Cumple una las veces de funcion y de procedimiento.
    Toma los datos de un archivo.in 
    Como funcion: devuelve un unsigned int, este numero es el tamñod el arreglo que llenaremos
    Como procedimiento: recorre el arreglo hasta size-1 llenandolo con los valores ingresados
*/

void array_dump(int a[], unsigned int length);
/*
    Impreme en una arreglo de la siquiente manera 
    [ a[0] a[1] . . . ap[length - 1] ]
*/
boolean array_is_sorted(int a[], unsigned int max_size);
/*
    Te dice si el arreglo esta ordenado
*/
#endif