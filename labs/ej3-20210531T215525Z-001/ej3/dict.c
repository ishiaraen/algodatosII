#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool check_greater(dict_t d, key_t word) {
    bool greater = true;
    if (d != NULL) {
        greater = key_less(d->key, word) && 
                  check_greater(d->left, word) &&
                  check_greater(d->right, word);
    }
    return greater;
}

static bool check_smaller(dict_t d, key_t word) {
    bool smaller = true;
    if (d != NULL) {
        smaller = key_less(word, d->key) &&
                  check_smaller(d->left, word) &&
                  check_smaller(d->right, word);
    }
    return smaller;
}

static bool keyValue(dict_t d) {
    bool definition = true;
    if (d->key != NULL) {
        definition = (d->value != NULL);
    }
    return definition;
}

static bool invrep(dict_t d) {
    bool valid = true;
    if (d == NULL) {
        valid = true;
    } else {
        valid = check_greater(d->left, d->key) &&
                check_smaller(d->right, d->key) &&
                keyValue(d) &&
                invrep(d->left) && invrep(d->right); 
    }
    return valid;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict));
    assert(dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict == NULL) {
        dict = malloc(sizeof(*dict_t));
        dict->key = word;
        dict->value = def;
        dict->right = dict_empty();
        dict->left = dict_empty();
    } else {
        if (key_less(word, dict->key)) {
            dict->left = dict_add(dict->left, word, def);
        } else if (key_less(dict->key, word)) {
            dict->right = dict_add(dict->right, word, def);
        } else {
            dict->value = value_destroy(dict->value);
            dict->value = def;
        }
    }
    assert(invrep(dict));
    assert(key_eq(def, dict_search(dict,word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    assert(word != NULL);
    key_t def = NULL;
    if (key_eq(word, dict->key)) {
        def = dict->value;
    } else if (key_less(word, dict->key)) {
        def = dict_search(dict->left, word);
    } else {
        def = dict_search(dict->right, word);
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    assert(word != NULL);
    bool exists = false;
    if (dict != NULL) {
        exists = (key_eq(word, dict->key)) || dict_exists(dict->left, word) || dict_exists(dict->right, word);
    }
    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length = 0u;
    if (dict != NULL) {
        length = dict_length(dict->right) + 1u + dict_length(dict->left);
    }
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    assert(word != NULL);
    if (dict == NULL) {
        return dict;
    }
    if (key_less(dict->key, word)) {
        dict->left = dict_remove(dict->left, word);
    } else if (key_less(word, dict->key)) {
        dict->right = dict_remove(dict->right, word);
    } else {
        /* Case 1: one left child*/
        if (dict->left == NULL) {
            dict_t aux = dict->right;
            free(dict);
            return aux;
        } 
        /* Case 2: one right child*/
        else if (dict->right == NULL) {
            dict_t aux = dict->left;
            free(dict);
            return aux;
        } 
        key_t wordAux = key_min(dict->right);
        dict->key = wordAux;
        dict->right = dict_remove(dict->right,dict->key);
    }
    assert(invrep(dict));
    assert(!dict_exists(dict, word));
    return dict;
}

key_t key_min(dict_t dict) {
    assert(invrep(dict));
    key_t min_word = NULL; 
    if (dict->left != NULL) {
        while (dict->left != NULL) {
            dict = dict->left;
        }
        min_word = dict->key;
    } else {
        min_word = dict->key;
    }    
    return min_word;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
    }
    assert(invrep(dict));
    assert(dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    assert(file != NULL);
    if (dict != NULL) {
        fprintf(file, "%s : %s\n", string_ref(dict->key), string_ref(dict->value));
        dict_dump(dict->left, file);
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL) {
        dict->left = dict_destroy(dict->left);
        dict->right = dict_destroy(dict->right);
        free(dict->left);
        dict->left = NULL;
        free(dict->right);
        dict->right = NULL;
    }
    free(dict);
    dict = NULL;
    assert(dict == NULL);
    return dict;
}

