#ifndef _INCLUDE_IRAND_H_
#define _INCLUDE_IRAND_H_

/*----------------------------------------------------------------------------*/
/* include */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mt19937ar.h"
#include "gamma.h"

/*----------------------------------------------------------------------------*/
/* for short */
/*----------------------------------------------------------------------------*/
#define psi(x) (iprob_digamma(x))

/*----------------------------------------------------------------------------*/
/* typedef */
/*----------------------------------------------------------------------------*/
typedef long double prob;

/*----------------------------------------------------------------------------*/
/* ary */
/*----------------------------------------------------------------------------*/
prob *iprob_new_ary(int _n, prob _v);
void iprob_init_ary(int _n, prob *_p, prob _v);
void iprob_copy_ary(int _n, prob *_p, prob *_q);
void iprob_rand_ary(int _n, prob *_p);
prob iprob_sum_ary(int _n, prob *_p);
void iprob_normalize_ary(int _n, prob *_p);
prob iprob_inner_product(int _n, prob *_p, prob *_q);

/*----------------------------------------------------------------------------*/
/* matrix */
/*----------------------------------------------------------------------------*/
prob **iprob_new_matrix(int _n, int _m, prob _v);
void iprob_free_matrix(int _n, prob **_p);
void iprob_init_matrix(int _n, int _m, prob **_p, prob _v);
void iprob_init_matrix_by_ary(int _n, int _m, prob **_p, prob *_v);
void iprob_rand_matrix(int _n, int _m, prob **_p);

/*----------------------------------------------------------------------------*/
/* log sum exp */
/*----------------------------------------------------------------------------*/
prob iprob_log_sum(prob _x, prob _y, int _f);
prob iprob_log_diff(prob _x, prob _y, int _f);
prob iprob_log_sum_ary(int _n, prob *_lth);
prob iprob_log_inner_product(int _n, prob *_lth, prob *_lph);

/*----------------------------------------------------------------------------*/
/* math */
/*----------------------------------------------------------------------------*/
/* gamma */
prob iprob_gamma(prob x);
prob iprob_gammal(prob lx);
prob iprob_lgamma(prob x);
prob iprob_lgammal(prob lx);
/* *-gamma*/
prob iprob_digamma(prob x);
prob iprob_digammal(prob lx);
prob iprob_trigamma(prob x);
/* util */
prob iprob_log(prob x);
prob iprob_exp(prob x);
prob iprob_min(prob a, prob b);
prob iprob_max(prob a, prob b);

/*----------------------------------------------------------------------------*/
/* irand */
/*----------------------------------------------------------------------------*/
/* srand */
void isrand(unsigned long _s);

/* uniform */
prob irand_uni_r(void);       /* [0..1] */
int  irand_uni_i(int _max);   /* {0,..._max-1} */

/* categorical */
int irand_cat(int _n, prob *_th);
int irand_catl(int _n, prob *_lth);

/* dirichlet */
void irand_dir(int _n, prob *_th, prob *_a);
prob irand_dir_kld(int _n, prob *_a, prob *_b);
prob irand_dir_log_z(int _n, prob *_a);
void irand_dirl(int _n, prob *_lth, prob *_la);
prob irand_dirl_kld(int _n, prob *_la, prob *_lb);
prob irand_dirl_log_z(int _n, prob *_a);

/* gamma */
prob irand_gam(prob _a);

#endif
