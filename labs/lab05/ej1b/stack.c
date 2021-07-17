#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    stack next; 
    int size;
};

static bool invrep(stack s){
    return s->size >= 0;
}

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->next = NULL;
    s->size = 0u;
    assert(invrep(s));
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(invrep(s));
    if(s->size == 0){
        s->size = 1;
        s->elem = e;
    }
    else{
        stack p = malloc(sizeof(struct _s_stack));
        p->elem = e;
        p->next = s;
        p->size = s->size + 1;
        s = p;
        p = NULL;
    }
    assert(invrep(s));
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s));
    assert(!stack_is_empty(s));
    stack t = s;
    s = s->next;
    s->size = t->size - 1;
    free(t);
    t = NULL;
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
    return s->elem;
}

bool stack_is_empty(stack s){
    assert(invrep(s));
    return s->size == 0u;
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));
    stack_elem *array = NULL;
    if(!stack_is_empty(s)){
        array = calloc(stack_size(s),sizeof(stack_elem));
        for(int i = stack_size(s) - 1u; i >= 0 ; --i){
            array[i] = s->elem;
            s = s->next;
        }
    }
    assert(invrep(s));
    return array;
}

stack stack_destroy(stack s){
    assert(invrep(s));
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