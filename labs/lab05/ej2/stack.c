#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

static bool invrep(stack s){
   return s->size <= s->capacity;
}

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->elems = (stack_elem *)calloc(1u , sizeof(stack_elem));
    s->capacity = 1u;
    s->size = 0u;
    assert(invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    if(s->size == s->capacity){
        s->elems = realloc(s->elems, 2 * (s->capacity) * sizeof(stack_elem));
        s->capacity = 2u * s->capacity;
    }
    ++s->size;
    s->elems[s->size - 1u] = e;
    assert(invrep(s));
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    assert(!stack_is_empty(s));
    --s->size;
    assert(invrep(s));
    return s;
}   

unsigned int stack_size(stack s){
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1u];
}

bool stack_is_empty(stack s){
    assert(invrep(s));
    return s->size == 0u;
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    stack_elem *array = NULL;
    if(!stack_is_empty(s)){
        array = calloc(s->size, sizeof(stack_elem));
        for (unsigned int i = 0u; i < s->size; ++i){
            array[i] = s->elems[i];
        }
    }
    return array;
}

stack stack_destroy(stack s){
    assert(invrep(s));
    free(s->elems);
    free(s);
    return NULL;  
}