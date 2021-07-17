#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    stack s = stack_empty();
    stack_elem *array = NULL;
    stack_elem i = 0u;
    s = stack_push(s, 3);
    s = stack_pop(s);
    array = stack_to_array(s);
    if(array == NULL){
        printf("holi\n");
    }
    s = stack_push(s, 4);
    for(i = 0u; i < 7; ++i){
        s = stack_push(s,i);
    }
    array = stack_to_array(s);
    for(i = 0u; i < 8 ; ++i){
        printf(" %d ,", array[i]);
    }
    stack_destroy(s);
    return 0;
}