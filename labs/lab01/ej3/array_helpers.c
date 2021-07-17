#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[], unsigned int size, char *filepath){
    FILE *file_input;
    file_input = fopen(filepath, "r");
    fscanf(file_input, "%u" , &size);
        if (file_input == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0; i < size; i++){
        fscanf(file_input, "%d" , &array[i]);
    }
    fclose(file_input);
    
    return size;
}

unsigned int array_from_stdin(int array[], unsigned int max_size, const char *filepath) {
    filepath = filepath;
    FILE *input_tecleado;
    input_tecleado = stdin;
    fscanf(input_tecleado , "%u", &max_size);
    if(max_size > 100000){
        printf("El numero tiene que ser menor o igual a %u \n", 100000);
        exit(EXIT_FAILURE);
    }
    for(unsigned int i=0; i < max_size; i++){
        fscanf(input_tecleado , "%d", &array[i]);
    }
    return max_size;
}

void array_dump(int a[], unsigned int length) {

    printf("[");
    for(unsigned int i=0 ; i< length; i++){
        printf(" %d ",a[i]);
    }
    printf("]");
}