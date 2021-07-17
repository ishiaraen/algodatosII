#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
 
struct _node {
    list_elem elem;
    list next;
};

list empty(){
    return NULL;
}

list addl(list l, list_elem e){
    list p = malloc(sizeof(struct _node));
    p->elem = e;
    p->next = l;
    return p;
}

bool is_empty(list l){
    bool b = l == NULL;
    return b;
}

list destroy(list l){
    list rm = l;
    while(!is_empty(l)){
        l = rm->next;
        free(rm);
        rm = l;
    }
    return NULL;
}

list copy_list(list l){
    list l_copy = malloc(sizeof(struct _node));
    list init = l_copy;
    while (l != NULL){
        l_copy->next = malloc(sizeof(struct _node));
        l_copy->elem = l->elem;
        l = l->next;
        l_copy = l_copy->next;
    }
    free(l_copy);
    l_copy = NULL;
    return init;
}

list_elem head(list l){
    assert(!is_empty(l));
    return l->elem;
}

list tail(list l){
    assert(!is_empty(l));
    list p = l->next;
    free(l);
    l = NULL;
    return p;
}

list addr(list l, list_elem e){
    list p, q;
    p = malloc(sizeof(struct _node));
    p->next = NULL;
    p->elem = e;
    if(!is_empty(l)){
        q = l;
        while(q!=NULL){
            q = q->next;
        }
        q = p;
    }
    else{
        l = p;
    }   
    return l;
} 

unsigned int length(list l){
    unsigned int i = 0u;
    list p = l;
    while(p != NULL){
        p = p->next;
        i = i + 1u;
    }
    return i;
}

list concat(list l,list l1){
    list p = copy_list(l);
    list ret = p;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = copy_list(l1); 
    return ret;
}

list_elem index(list l, unsigned int n){
    assert(n < length(l));
    list p = l;
    unsigned int i = 0u;
    while(i < n)
    {
        p = p->next;
        i = i + 1u;
    }
    return p->elem;
}

list take(list l, unsigned int n){
    list p =l;
    list t = empty();
    for (unsigned int i = 0u; i < n ;i++){
        t = addr(t,l->elem);
        p = p->next;
    }
    return t;
}

list drop(list l, unsigned int n){
    list d = empty();
    list p = l;
    for(unsigned int i=0u;i < n; i++){
        p = p->next;
    }
    for (unsigned int i=n; i < length(l); i++){
        d = addr(d,p->elem);
        p = p->next;
    }
    return d;
}


// se pueden borrar las variables creadas con list p con el unico objetivo de recorrer las lista sin
// modificar los valores de l, pues, la variable l en cada funcion es una variable interna
// y modificar ese valor no cambia el valor del valor de entrada
