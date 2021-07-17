#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node {
    list_elem elem;
    list next;
};

list empty(){
    return NULL;
}

list addl(list l, list_elem e){
    list p = malloc(sizeof(struct node));
    p->elem = e;
    p->next = l;
    l = p;
    return p;
}

list destroy(list l){
    list p = l;
    while (p!=NULL){
        p = l->next;
        free(l);
        l = p;
    }
    l = NULL;
    return(l);    
}

bool is_empty(list l){
    return(l==NULL);
}

list_elem head(list l){
    assert(!is_empty(l));
    return(l->elem);
}

list tail(list l){
    assert(!is_empty(l));
    list p = l;
    l = l->next;
    free(p);
    return(l);
}

list addr(list l, list_elem e){
    list p, q;
    q = malloc(sizeof(struct node));
    q->elem = e;
    q->next = NULL;
    
    if (!is_empty(l)) {
        p = l;
        while (p->next!=NULL) {
            p = p->next;
        }
        p->next = q;
    } else {
        l = q;
    }
    return l;
}

list_elem length(list l){
    list pointer = l;
    unsigned int n = 0u;

    while (pointer!=NULL) {
        n = n+1;
        pointer = pointer->next;
    }
    return n;
}

list concat(list l, list l_0){
    list p, q;
    q = l_0;
    if (!is_empty(l))
    {
        p = l;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = malloc(sizeof(struct node));
        p->next = q;
    } else {
        l = q;
    }   
    return(l); 
}

list_elem index(list l, list_elem n){
    assert(length(l) > n);
    list p = l;
    list_elem i = 0;
    while (i < n)
    {
        p = p->next;
        i = i+1;
    }
    return(p->elem);
}

list take(list l, list_elem n){
    list p = l;
    list_elem i = 0; 
    while (i<=n && !is_empty(l))
    {
        p = p->next;
        i = i+1;
    }
    destroy(p);
    return (l);
}

list drop(list l, list_elem n){
    list p;
    list_elem i = 0;
    while (i < n && l!=NULL)
    {
        p = l;
        l = p->next;
        free(p);
        i = i+1;
    }
    return(l);    
}

list copy_list(list l){
    list l_aux = l; 
    list l_copy = NULL;

    if (l == NULL) {
        l_copy = NULL;
    } else {
        list l_copy_aux = NULL;
        l_copy = malloc(sizeof(struct node));  //reservo espacio para l (l_aux = l)
        l_copy->elem = l_aux->elem;    //copio el elemento de l (l_aux = l)
        l_copy->next = NULL;            // !!!!!!! next = NULL
        l_copy_aux = l_copy;        //asigno l_copy a l_copy_aux (l_copy_aux tiene el primer elemento de l)

        l_aux = l_aux->next;        //avanzo al siguiente casillero

        while (l_aux != NULL)       //mientras l / l_aux no sea vacia
        {
            list new_node = malloc(sizeof(struct node));            // nuevo puntero, reservo espacio
            new_node->elem = l_aux->elem;                       // le asigno el mismo elemento que l_aux
            new_node->next = NULL;                          // !!!! next = null
            l_copy_aux->next = new_node;
            l_copy_aux = new_node;
            l_aux = l_aux->next;
        }  
    }
    return l_copy;
}

