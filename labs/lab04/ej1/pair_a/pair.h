#ifndef _PAIR_H
#define _PAIR_H

typedef struct s_pair_t pair_t;

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y);
/*
 * DESC: Creates a new pair with components (x, y)
 *
 * POS: {p --> (x, y)}
 */

int pair_first(pair_t p);
/*
 * DESC: Returns the first component of p
 *
 * PRE: {p --> (x, y)}
 *
 *  fst = pair_first(p);
 *
 * POS: {fst == x}
 */

int pair_second(pair_t p);
/*
 * DESC: Returns the second component of p
 *
 * PRE: {p --> (x, y)}
 *
 *  fst = pair_first(p);
 *
 * POS: {fst == x}
 */

pair_t pair_swapped(pair_t p);
/*
 * DESC: Return pair with p its components swapped
 *
 * PRE: {p --> (x, y)}
 *
 *  q = pair_invert(p)
 *
 * POS: {q --> (y, x)}
 *
 */

pair_t pair_destroy(pair_t p);
/*
 * DESC: Free memory if its necesary
 *
 */


#endif
