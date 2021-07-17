#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef int list_elem;
typedef struct _node * list;

//Constructors
list empty();
/* Create list of type list_elem */
list addl(list l, list_elem e);
/* add element e to the beginning of the list*/

//Operations
bool is_empty(list l);
/* Return True if list is empty */

list_elem head(list l);
/* Return first elem of list l */

list tail(list l);
/* remove first element of list l */

list addr(list l, list_elem e);
/* add an element to the end of the list */

unsigned int length(list l);
/* Return the size of list l*/

list concat(list l, list l1);
/* add to the end of the list l the elements of l1*/

list_elem  index(list l, unsigned int n);
/* Returns the element of the n-posicion to list l*/

list take(list l, unsigned int n);
/* removes all elements from list l located in positions greater than or equal to n */

list drop(list l, unsigned int n);
/* removes all elements from list l located in positions less than to n*/

list copy_list(list l);
/* returns a copy of list l*/

//Destroy
list destroy(list l);
/*Destroy list l*/

#endif
