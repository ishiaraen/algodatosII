#include <stdio.h>
#include "string.h"
/*
int main(){
    char *v1 = "ab";
    char *v2 = "bb";
    char *v3 = "bc";
    string w1= string_create(v1);
    string w2= string_create(v2);
    string w3= string_create(v3);
    bool i = string_less(w1,w3); 
    bool j = string_eq(w2,w2);
    bool k = string_less(w3,w2);
    if(j){
        printf("son iguales =D\n");
    }
    if(i){
        printf("w1 es mas chico que w3\n");
    }
    if(!k){
        printf("w3 es mas grande que w2\n");
    }
}
*/

int main(){
    bool b;
    char *word1 = "asdsdasd";
    char *word2 = "holisss";
    string str1 = string_create(word1);
    string str2 = string_create(word2);
    b = string_eq(str1, str2);
    if(!b){
        printf("no son iguales kpo");
    }   
    return 0;
}
