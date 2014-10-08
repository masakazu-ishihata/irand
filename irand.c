#include "irand.h"

/*----------------------------------------------------------------------------*/
/* ary */
/*----------------------------------------------------------------------------*/
prob *iprob_new_ary(int _n, prob _v)
{
  prob *p = (prob *)malloc(_n * sizeof(prob));
  if(p == NULL){
    printf("error @ iprob_new_ary : fail malloc\n");
    exit(1);
  }
  iprob_init_ary(_n, p, _v);
  return p;
}
void iprob_init_ary(int _n, prob *_p, prob _v)
{
  int i;
  for(i=0; i<_n; i++) _p[i]=_v;
}
void iprob_copy_ary(int _n, prob *_p, prob *_q)
{
  int i;
  for(i=0; i<_n; i++) _p[i] = _q[i];
}
void iprob_rand_ary(int _n, prob *_p)
{
  int i;
  for(i=0; i<_n; i++) _p[i] = irand_uni_r();
  iprob_normalize_ary(_n, _p);
}
prob iprob_sum_ary(int _n, prob *_p)
{
  int i;
  prob sum = 0;
  for(i=0; i<_n; i++) sum+=_p[i];
  return sum;
}
void iprob_normalize_ary(int _n, prob *_p)
{
  int i;
  prob sum = iprob_sum_ary(_n, _p);
  for(i=0; i<_n; i++) _p[i] /= sum;
}
prob iprob_inner_product(int _n, prob *_p, prob *_q)
{
  int i;
  prob sum = 0;
  for(i=0; i<_n; i++) sum += _p[i] * _q[i];
  return sum;
}

/*----------------------------------------------------------------------------*/
/* matrix */
/*----------------------------------------------------------------------------*/
prob **iprob_new_matrix(int _n, int _m, prob _v)
{
  int i;
  prob **p = (prob **)malloc(_n * sizeof(prob *));
  if(p == NULL){
    printf("error @ iprob_new_matrix : fail malloc\n");
    exit(1);
  }
  for(i=0; i<_n; i++) p[i] = iprob_new_ary(_m, _v);

  return p;
}
void iprob_free_matrix(int _n, prob **_p)
{
  int i;
  for(i=0; i<_n; i++) free(_p[i]);
  free(_p);
}
void iprob_init_matrix(int _n, int _m, prob **_p, prob _v)
{
  int i;
  for(i=0; i<_n; i++) iprob_init_ary(_m, _p[i], _v);
}
void iprob_init_matrix_by_ary(int _n, int _m, prob **_p, prob *_v)
{
  int i;
  for(i=0; i<_n; i++) iprob_copy_ary(_m, _p[i], _v);
}
void iprob_rand_matrix(int _n, int _m, prob **_p)
{
  int i;
  for(i=0; i<_n; i++) iprob_rand_ary(_m, _p[i]);
}

/*----------------------------------------------------------------------------*/
/* log sum exp */
/*----------------------------------------------------------------------------*/
prob iprob_log_sum(prob _x, prob _y, int _f)
{
  if(_f)       return _y;
  if(_x == _y) return _x + 0.693147180559945309;

  double max = _x, min = _y;
  if(_x < _y){
    max = _y;
    min = _x;
  }
  return max + logl( 1.0 + expl(min - max) );
}
prob iprob_log_diff(prob _x, prob _y, int _f)
{
  if(_f) return _y;
  if(_x == _y) return logl(0);
  double max = _x, min = _y;
  if(_x < _y){
    max = _y;
    min = _x;
  }
  return max + logl( 1.0 - expl(min - max) );
}
prob iprob_log_sum_ary(int _n, prob *_lth)
{
  int i;
  prob max, sum;

  /* max */
  for(i=1, max=_lth[0]; i<_n; i++)
    if(max < _lth[i]) max = _lth[i];

  /* sum */
  for(i=0, sum=0; i<_n; i++)
    sum += expl(_lth[i] - max);

  return max + logl(sum);
}
prob iprob_log_inner_product(int _n, prob *_lth, prob *_lph)
{
  int i;
  prob max, sum;

  /* max */
  for(i=1,max=_lth[0]+_lph[0]; i<_n; i++)
    if(max < _lth[i] + _lph[i]) max = _lth[i] + _lph[i];

  /* sum */
  for(i=0,sum=0; i<_n; i++)
    sum += expl(_lth[i] + _lph[i] - max);

  return log(sum) + max;
}

/*----------------------------------------------------------------------------*/
/* math */
/*----------------------------------------------------------------------------*/
/* gamma */
prob iprob_gamma(prob x)
{
  return iprob_exp( iprob_lgamma(x) );
}
prob iprob_gammal(prob lx)
{
  return iprob_exp( iprob_lgammal(lx) );
}
prob iprob_lgamma(prob x)
{
  return (prob)lgammal(x);
}
prob iprob_lgammal(prob lx)
{
  return (prob)lgammal( expl(lx) );
}
/* digamma */
prob iprob_digamma(prob x)
{
  return (prob)digamma( (double)x );
}
prob iprob_digammal(prob lx)
{
  return (prob)digamma( (double)expl(lx) );
}
prob iprob_trigamma(prob x)
{
  return (prob)trigamma( (double)x );
}
/* log, exp, min, max */
prob iprob_log(prob x)
{
  return (prob)logl((long double)x);
}
prob iprob_exp(prob x)
{
  return (prob)expl((long double)x);
}
prob iprob_min(prob a, prob b)
{
  if(a < b) return a;
  else      return b;
}
prob iprob_max(prob a, prob b)
{
  if(a < b) return b;
  else      return a;
}

/*----------------------------------------------------------------------------*/
/* irand */
/*----------------------------------------------------------------------------*/
/* srand */
void isrand(unsigned long _s)
{
  init_genrand(_s);
}

/*------------------------------------*/
/* uniform */
/*------------------------------------*/
prob irand_uni_r(void)
{
  return genrand_real1();
}
int irand_uni_i(int _max)
{
  return (int)(_max * genrand_real1());
}

/*------------------------------------*/
/* categorical */
/*------------------------------------*/
int irand_cat(int _n, prob *_th)
{
  int i;
  prob s, r;

  r = irand_uni_r();

  for(s=0, i=0; i<_n; i++){
    s += _th[i];
    if(r < s) break;
  }
  return i;
}
int irand_catl(int _n, prob *_lth)
{
  int i;
  prob lth_max, r, s;

  for(lth_max=_lth[0], i=1; i<_n; i++)
    if(lth_max < _lth[i]) lth_max = _lth[i];

  for(s=0, i=0; i<_n; i++) s += exp(_lth[i] - lth_max);
  r = s * irand_uni_r();
  for(s=0, i=0; i<_n; i++){
    s += exp(_lth[i] - lth_max);
    if(r < s) break;
  }
  return i;
}

/*------------------------------------*/
/* dirichlet */
/*------------------------------------*/
void irand_dir(int _n, prob *_th, prob *_a)
{
  int i;
  prob z = 0;
  for(i=0; i<_n; i++) z += (_th[i] = irand_gam(_a[i]));
  for(i=0; i<_n; i++) _th[i] /= z;
}
prob irand_dir_kld(int _n, prob *_a, prob *_b)
{
  int i;
  prob kl=0, a0=0, b0=0, ai, bi;

  /* a0, b0 */
  for(i=0; i<_n; i++){
    a0 += _a[i];
    b0 += _b[i];
  }

  /* log g(a_0) - log g(b_0) */
  kl += iprob_lgamma(a0) - iprob_lgamma(b0);

  for(i=0; i<_n; i++){
    ai = _a[i];
    bi = _b[i];

    /* - ( log g(a_i) - log g(b_i) )*/
    kl -= iprob_lgamma(ai) - iprob_lgamma(bi);

    /* (a_i - b_i)(dg(a_i) - dg(a_0)) */
    kl += (ai - bi) * (iprob_digamma(ai) - iprob_digamma(a0));
  }

  return kl;
}
prob irand_dir_log_z(int _n, prob *_a)
{
  int i;
  prob ln = 0, ld = 0;

  for(i=0; i<_n; i++){
    ln += iprob_lgamma(_a[i]); /* numerator */
    ld += _a[i];               /* denominator */
   }
  ld = iprob_lgamma(ld);

  return ln - ld;
}
/* Dir(log) */
void irand_dirl(int _n, prob *_lth, prob *_la)
{
  int i;
  prob z = 0;
  for(i=0; i<_n; i++) z += (_lth[i] = irand_gam( expl(_la[i]) ));
  for(i=0; i<_n; i++) _lth[i] = logl(_lth[i]) - logl(z);
}
prob irand_dirl_kld(int _n, prob *_la, prob *_lb)
{
  int i;
  prob kl=0, la0, lb0;

  /* log g(a_0) - log g(b_0) */
  la0 = iprob_log_sum_ary(_n, _la);
  lb0 = iprob_log_sum_ary(_n, _lb);
  kl += iprob_lgammal(la0) - iprob_lgammal(lb0);

  for(i=0; i<_n; i++){
    /* - ( log g(a_i) - log g(b_i) )*/
    kl -= iprob_lgammal(_la[i]) - iprob_lgammal(_lb[i]);

    /* (a_i - b_i)(dg(a_i) - dg(a_0)) */
    kl +=
      ( expl(_la[i]) - expl(_lb[i]) )
      * (iprob_digammal(_la[i]) - iprob_digammal(la0));
  }

  return kl;
}
prob irand_dirl_log_z(int _n, prob *_la)
{
  int i;
  prob ln = 0, ld = 0;

  for(i=0; i<_n; i++){
    ln += iprob_lgamma( expl(_la[i]) ); /* numerator */
    ld += expl(_la[i]);                 /* denominator */
   }
  ld = iprob_lgamma(ld);

  return ln - ld;
}

/*------------------------------------*/
/* gamma */
/*------------------------------------*/
prob irand_gam(prob _a)
{
  prob x, y, z;
  prob u, v, w, b, c, e;
  int accept = 0;

  if(_a < 1){
    /* Johnk's generator. Devroye (1986) p.418 */
    e = -logl( irand_uni_r() );
    do {
      x = powl(irand_uni_r(), 1 / _a);
      y = powl(irand_uni_r(), 1 / (1 - _a));
    } while (x + y > 1);
    return (e * x / (x + y));
  }else{
    /* Best's rejection algorithm. Devroye (1986) p.410 */
    b = _a - 1;
    c = 3 * _a - 0.75;
    do {
      /* generate */
      u = irand_uni_r();
      v = irand_uni_r();
      w = u * (1 - u);
      y = sqrtl(c / w) * (u - 0.5);
      x = b + y;
      if (x >= 0)
        {
          z = 64 * w * w * w * v * v;
          if (z <= 1 - (2 * y * y) / x)
            {
              accept = 1;
            } else {
            if (logl(z) < 2 * (b * logl(x / b) - y))
              accept = 1;
          }
        }
    } while (accept != 1);
    return x;
  }
}
