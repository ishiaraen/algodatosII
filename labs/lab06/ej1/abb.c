#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool check_greater(abb_elem e, abb tree){
    bool greater = true;
    if(tree != NULL){
        greater = elem_less(tree->elem, e) && 
                  check_greater(e, tree->left) &&
                  check_greater(e, tree->left);
    }
    return greater;
}

static bool check_smaller(abb_elem e, abb tree){
    bool smaller = true;
    if(tree != NULL){
        smaller = elem_less(e, tree->elem) && 
                  check_smaller(e, tree->left) &&
                  check_smaller(e, tree->left);
    }
    return smaller;
}

static bool invrep(abb tree) {
    bool inv = false;
    if(tree != NULL){
        inv = check_greater(tree->elem, tree->left) && 
                check_smaller(tree->elem, tree->right) && 
                invrep(tree->right) && invrep(tree->left);              
    }
    else{
        inv = true;
    }
    return inv;
}


abb abb_empty(void){
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL){
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }
    else{
        if (e < tree->elem){
            tree->left = abb_add(tree->left, e);
        }
        else if (e > tree->elem){
            tree->right = abb_add(tree->right, e);
        }
    }
    assert(invrep(tree)); 
    assert(abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if(elem_eq(e,tree->elem)){
        exists = true;
    }
    else if(elem_less(e,tree->elem)){
        exists = abb_exists(tree->left, e);
    }
    else{
        exists = abb_exists(tree->right, e);
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(tree != NULL){
        length =  1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) ||  length > 0));
    return length;
}

static abb sr_and_rm(abb tree){
    abb t1 = tree;
    abb t2 = tree;
    if (tree->left==NULL && tree->right==NULL) {
        free(tree);
        tree = NULL;
    } else if(tree->left != NULL){
        t1 = tree->left;
        if (t1->right == NULL) {
            tree->elem = t1->elem;
            tree->left = t1->left;
            free(t1);
        } else {
            while (t1->right != NULL) {
                t2 = t1;
                t1 = t1->right;
            }
            tree->elem = t1->elem;
            t2->right = t1->left;
            free(t1);
        }
    } else {
        t1 = tree->right;
        free(tree);
        tree = t1;
    }
    return tree;
}

abb abb_remove(abb tree, abb_elem e){
    abb ret = tree;
    abb temp = NULL;
    int side = 0;
    assert(invrep(tree));
    while (tree != NULL && !elem_eq(tree->elem, e)) {
        if (elem_less(e, tree->elem)) {
            temp = tree;
            side = -1;
            tree = tree->left;
        } else {
            temp = tree;
            side = 1;
            tree = tree->right;
        }
    }
    if (elem_eq(tree->elem, e)) {
        tree = sr_and_rm(tree);
        if (side == -1) {
            temp->left = tree;
        } else if (side == 1) {
            temp->right = tree;
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return ret;
}

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    max_e = tree->elem;
    if(tree->right != NULL){
        max_e = abb_max(tree->right);
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    min_e = tree->elem;
    if(tree->left != NULL){
        min_e = abb_min(tree->left);
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree != NULL){
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

