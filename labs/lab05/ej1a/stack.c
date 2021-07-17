#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    stack next; 
};

stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    s = p;
    p = NULL;
    return s;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    stack t = s;
    s = s->next;
    free(t);
    t = NULL;
    return s;
}

unsigned int stack_size(stack s){
    stack t = s;
    unsigned int size = 0u;
    while(t != NULL)
    {
        t = t->next;
        size = size + 1u;
    }
    return size;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    stack_elem *array = NULL;
    if(!stack_is_empty(s)){
        array = calloc(stack_size(s),sizeof(stack_elem));
        for(int i = stack_size(s) - 1u; i >= 0 ; --i){
            array[i] = s->elem;
            s = s->next;
        }
    }
    return array;
}

stack stack_destroy(stack s){
    stack d = s;
    while (d != NULL)
    {
        d = d->next;
        free(s);
        s = d;
    }
    s = NULL;  
    return s;
}