#include <assert.h>
#include "dict.h"
#include "key_value.h"
#include <stdlib.h>

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool check_greater(key_t word, dict_t dict){
    bool greater = true;
    if(dict != NULL){
        greater = key_less(dict->key, word) && 
                  check_greater(word, dict->left) &&
                  check_greater(word, dict->right);
    }
    return greater;
}

static bool check_smaller(key_t word, dict_t dict){
    bool smaller = true;
    if(dict != NULL){
        smaller = key_less(word, dict->key) && 
                  check_smaller(word, dict->left) &&
                  check_smaller(word, dict->right);
    }
    return smaller;
}

static bool check_key_value(dict_t d){
    bool inv = true;
    if(d->key != NULL){
        inv = d->value != NULL;
    }
    return inv;
}

static bool invrep(dict_t d) {
    bool inv = false;
    if(d != NULL){
        inv = check_greater(d->key, d->left) && 
                check_smaller(d->key, d->right) &&
                check_key_value(d) && 
                invrep(d->right) && invrep(d->left);              
    }
    else{
        inv = true;
    }
    return inv;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict));
    assert(dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if(dict == NULL){
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = dict_empty();
        dict->right = dict_empty();
    }else{
        if(key_less(word,dict->key)){
            dict->left = dict_add(dict->left, word, def);
        }else if(key_eq(dict->key, word)){
            dict->value = value_destroy(dict->value);
            dict->value = def;
        }else{
            dict->right = dict_add(dict->right, word, def);
        } 
    }
    assert(invrep(dict));
    assert(key_eq(def, dict_search(dict,word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def = NULL;
    if(dict != NULL){
        if(key_eq(word, dict->key)){
            def = dict->value;
        }else if(key_less(word, dict->key)){
            def = dict_search(dict->left, word);
        }else{
            def = dict_search(dict->right, word);
        }
    }
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exist = false;
    exist = dict != NULL && 
            ( key_eq(word, dict->key) ||
            ( key_less(word, dict->key) && dict_exists(dict->left, word) )
            || dict_exists(dict->right, word) );
    return exist;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    if(dict != NULL){
        length = dict_length(dict->left) + 1u + dict_length(dict->right);
    }
    return length;
}

/*chequear despues*/

static dict_t sr_and_rm(dict_t dict){
    dict_t d1 = dict;
    dict_t d2 = dict;
    if (dict->left == NULL && dict->right == NULL) {
        free(dict);
        dict = NULL;
    } else if(dict->left != NULL){
        d1 = dict->left;
        if (d1->right == NULL) {
            dict->value = d1->value;
            dict->key = d1->key;
            dict->left = d1->left;
            free(d1);
        } else {
            while (d1->right != NULL) {
                d2 = d1;
                d1 = d1->right;
            }
            dict->key = d1->key;
            dict->value = d1->value;
            d2->right = d1->left;
            free(d1);
        }
    } else {
        d1 = dict->right;
        free(dict);
        dict = d1;
    }
    return dict;
}

dict_t dict_remove(dict_t dict, key_t word) {
    dict_t ret = dict;
    dict_t temp = NULL;
    int side = 0;
    assert(invrep(dict));
    while (dict != NULL && !key_eq(dict->key, word)) {
        if (key_less(word, dict->key)) {
            temp = dict;
            side = -1;
            dict = dict->left;
        } else {
            temp = dict;
            side = 1;
            dict = dict->right;
        }
    }
    if (key_eq(dict->key, word)) {
        dict = sr_and_rm(dict);
        if (side == -1) {
            temp->left = dict;
        } else if (side == 1) {
            temp->right = dict;
        }
    }
    assert(invrep(dict));
    assert(!dict_exists(dict, word));
    return ret;
}

/*hasta aca*/

dict_t dict_remove_all(dict_t dict) {
    if(dict != NULL){
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
    } 
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict_dump(dict->left, file);
        key_dump(dict->key , file);
        fprintf(file," = ");
        value_dump(dict->value, file);
        fprintf(file,"\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    if(dict != NULL){
        dict->left = dict_destroy(dict->left);
        dict->right = dict_destroy(dict->right);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }
    return dict;
}