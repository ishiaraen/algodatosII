#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char *w1 = "ab";
    char *w2 = "bb";
    char *w3 = "bc";
    int i = strcmp(w1,w3) ; 
    int j = strcmp(w2,w2);
    int k = strcmp(w3,w2);
    printf("menor=%d igual=%d mayor=%d\n", i, j, k);
}
//cmp devuelve negativo si s1 es menor que s2
