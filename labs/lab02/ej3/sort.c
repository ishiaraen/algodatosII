#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    /* Needs implementation */
    unsigned int piv = izq;
    unsigned int i = izq + 1;
    unsigned int j = der;
    while(goes_before(i,j)){
        if (goes_before(a[i],a[piv])){
            i = i + 1;
        }
        if(goes_before(a[piv],a[j])){
            j = j - 1;
        }
        else if (goes_before(a[piv],a[i]) && goes_before(a[j],a[piv])){
            swap(a,i,j);
            i = i + 1;
            j = j - 1;
        }
    }
    swap(a,piv,j);
    piv = j;
    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */
    return piv;
    
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = 0u;
    if(izq < der){
        ppiv = partition(a,izq,der);
        if(ppiv>izq){
            quick_sort_rec(a,izq, ppiv - 1);
        }
        if (ppiv < der){
            quick_sort_rec(a,ppiv + 1,der);
        }
    }
    
}


void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

