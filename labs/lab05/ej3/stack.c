#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack
{
    stack_elem elem; //valor de la estructura en cada elem
    stack next; //puntero al siguiente nodo
    int size;
};

static bool invrep(stack s){
    return s->size >= 0;
}

stack stack_empty(void){
    stack s = malloc(sizeof(struct _s_stack));
    s->next = NULL;
    s->size = 0;
    assert(invrep(s));    
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    if(stack_empty()){
        s->elem = e;
        s->size = 1;
    }
    else{
        stack s_temp = malloc(sizeof(struct _s_stack));
        s_temp->elem = e;
        s_temp->next = s;
        s_temp->size = s->size + 1;
        s = s_temp;
    }
    assert(invrep(s));
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    stack s_elem;
    if(s->size > 1){
        s_elem = s;
        s = s->next;
        s->size = s->size - 1;
        free(s_elem);
    }
    else{
        s->size = 0;
        s->next = NULL;
    }
    assert(invrep(s));    
    return s;
}

unsigned int stack_size(stack s){
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s){
    assert(invrep(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    bool empty = true;
    empty = (s==NULL);
    return empty;
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    stack_elem *array;
    array = (stack_elem *)calloc(stack_size(s),sizeof(stack_elem));
    for(int i=stack_size(s)-1u; i >= 0; i--){
       array[i] = s->elem;
       s->size = s->size + 1;
       s = s->next;
    }
    assert(invrep(s));
    return array;
}

stack stack_destroy(stack s){
    assert(invrep(s));
   	stack s_temp = s;
    while(s != stack_empty()){
        if(s->size > 1){
            s = s -> next;
            free(s_temp);
            s_temp = s;
        }
        else{
            s->next = NULL;
            s->size = 0;
            free(s);
        }
    }
    s = NULL;
    return s;
} 

    


    





