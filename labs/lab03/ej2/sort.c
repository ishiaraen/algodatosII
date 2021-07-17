/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return (x.rank <= y.rank);
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}


static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int piv = izq;
    unsigned int i = izq + 1;
    unsigned int j = der;
    while(i <= j){
        if (goes_before(a[i],a[piv])){
            i = i + 1;
        }
        else if(goes_before(a[piv],a[j])){
            j = j - 1;
        }
        else if (!goes_before(a[piv],a[j]) && !goes_before(a[i],a[piv])){
            swap(a,i,j);
        }
    }
    swap(a, piv, j);
    piv = j;
    return piv;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = 0u;
    if(izq < der){
        ppiv = partition(a,izq,der);
        if(ppiv > izq){
            quick_sort_rec(a,izq, ppiv - 1);
            quick_sort_rec(a, ppiv + 1, der);
        }
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

