#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "irand.h"

#define N 1000   /* array length */
#define M 100    /* # of trial */
#define A 1.0e+5   /* Dirichlet A */
#define B 1.0e-5   /* Dirichlet B */

#define abs(a) ( (a) < 0 ? -(a) : (a) )

/*----------------------------------------------------------------------------*/
/* compare naive sum, repeating iprob_log_sum and iprob_log_sum_ary */
/*----------------------------------------------------------------------------*/
/* naive summ */
prob sum1(int _n, prob *_lth)
{
  int i;
  prob sum = 0;
  for(i=0; i<_n; i++) sum += iprob_exp( _lth[i] );
  return sum;
}
/* repeat log_sum */
prob sum2(int _n, prob *_lth)
{
  int i;
  prob lsum = 0;
  for(i=0; i<_n; i++) lsum = iprob_log_sum(lsum, _lth[i], i==0);
  return iprob_exp(lsum);
}
/* log_sum_ary */
prob sum3(int _n, prob *_lth)
{
  return iprob_exp( iprob_log_sum_ary(_n, _lth) );
}
/* test _sum _N times */
prob test(int _N, int _n, prob **_m, prob (_sum)(int, prob *))
{
  int i;
  prob sum = 0;
  for(i=0; i<_N; i++) sum += abs(1.0 - _sum(_n, _m[i]));
  return sum;
}
/* check */
void check(int _N, int _n, prob *_la)
{
  /* generate _N arys from Dir(_la) */
  int i;
  prob **m = iprob_new_matrix(_N, _n, 0);
  for(i=0; i<_N; i++) irand_dirl(_n, m[i], _la);

  /* test */
  printf("naive sum   : %.18Le\n", test(_N, _n, m, sum1));
  printf("log_sum     : %.18Le\n", test(_N, _n, m, sum2));
  printf("log_sum_ary : %.18Le\n", test(_N, _n, m, sum3));

  /* free */
  iprob_free_matrix(_N, m);
};

/*----------------------------------------------------------------------------*/
/* main */
/*----------------------------------------------------------------------------*/
int main(void)
{
  prob la[N]; /* for Dirichlet Dir(a) */
  prob lb[N]; /* for Dirichlet Dir(b) */

  isrand((unsigned int)time(NULL));
  printf("N = %d\n", N);
  printf("M = %d\n", M);

  /* Dirichlet Dir(a) */
  printf("#### check A ####\n");
  iprob_init_ary(N, la, iprob_log(A));
  check(M, N, la);

  /* Dirichlet Dir(b) */
  printf("#### check B ####\n");
  iprob_init_ary(N, lb, iprob_log(B));
  check(M, N, lb);

  /* KL(Dir(a) | Dir(b)  */
  printf("#### KL-divergence ####\n");
  printf("KL(a,b) = %Le\n", irand_dirl_kld(N, la, lb));

  return 0;
};
