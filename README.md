# irand

--------------------------------------------------------------------------------
## 概要
### iprob 系

確率ベクトル、確率行列を操作する。  
例えば動的確保や和、差、内積などを計算する。  
log sum exp 計算も可能。  
ただし、確率値がよほど小さくならないと愚直な sum より精度が低い。

### irand 系

Uniform 分布 や Categorical 分布、Dirichlet 分布を扱う。  
log 確率にも対応している。

--------------------------------------------------------------------------------
## array 系

ここで確率ベクトルとは prob 型配列の事であり、  
足して 1 に成る 0~1 の要素からなるベクトルとは限らない。

    prob *iprob_new_ary(int _n, prob _v);

長さ _n の確率ベクトルを生成する。  
ベクトルの要素は _v で初期化される。  

    void iprob_init_ary(int _n, prob *_p, prob _v);

長さ _n の確率ベクトル _p の各要素を _v に初期化する。

    void iprob_copy_ary(int _n, prob *_p, prob *_q);

長さ _n の確率ベクトル _p に確率ベクトル _q をコピーする。

    void iprob_rand_ary(int _n, prob *_p);

長さ _n の確率ベクトル _p を一様分布にしたがって初期化する。

    prob iprob_sum_ary(int _n, prob *_p);

長さ _n の確率ベクトル _p の総和を計算する。

    void iprob_normalize_ary(int _n, prob *_p);

長さ _n の確率ベクトル _p を正規化する。

    prob iprob_inner_product(int _n, prob *_p, prob *_q);

長さ _n の確率ベクトル _p と _q の内積を計算する。


--------------------------------------------------------------------------------
## matrix 系

ここで確率行列とは prob 型の２次元配列の事であり、  
足して 1 になる 0~1 の要素異からなる行列とは限らない。

    prob **iprob_new_matrix(int _n, int _m, prob _v);

_n x _m の確率行列を生成する。  
行列の各要素は _v で初期化される。

    void iprob_free_matrix(int _n, prob **_p);

_n x ? の確率行列を free する。  

    void iprob_init_matrix(int _n, int _m, prob **_p, prob _v);

_n x _m の確率行列の各要素を _v で初期化する。

    void iprob_init_matrix_by_ary(int _n, int _m, prob **_p, prob *_v);

_n x _m の確率行列の各行を長さ _m の確率ベクトル _p で初期化する。

    void iprob_rand_matrix(int _n, int _m, prob **_p);

_n x _m の確率行列の各行を一様な確率ベクトルで初期化する。

--------------------------------------------------------------------------------
## log sum exp 系

    prob iprob_log_sum(prob _x, prob _y, int _f);

_x = log(p), _y = log(q) としたとき、log(p+q) を返す。  
ただし、 _f == 1 のとき、log(q) を返す（初期化条件）。

    prob iprob_log_diff(prob _x, prob _y, int _f);

_x = log(p), _y = log(q) としたとき、log(p-q) を返す。  
ただし、 _f == 1 のとき、log(q) を返す（初期化条件）。

    prob iprob_log_sum_ary(int _n, prob *_lth);

長さ _n の log 確率ベクトル _lth の総和の log を返す。  
_lth[i] = log(th[i]) とすれば log( sum_i th[i] ) を返す。

    prob iprob_log_inner_product(int _n, prob *_lth, prob *_lph);

長さ _n の log 確率ベクトル _lth と _lph の内積の log を返す。


--------------------------------------------------------------------------------
## math 系
### gamma

以下では F(x) を Gamma 関数とする。

    prob iprob_gamma(prob x);

F(x) を返す。

    prob iprob_gammal(prob lx);

lx = log(x) のとき、F(x) を返す。

    prob iprob_lgamma(prob x);

log( F(x) ) を返す。

    prob iprob_lgammal(prob lx);

lx = log(x) のとき、log( F(x) ) を返す。


### *-gamma
    prob iprob_digamma(prob x);
    prob iprob_digammal(prob lx);
    prob iprob_trigamma(prob x);

### general
    prob iprob_log(prob x);
    prob iprob_exp(prob x);
    prob iprob_min(prob a, prob b);
    prob iprob_max(prob a, prob b);

--------------------------------------------------------------------------------
## rand 系

    void isrand(unsigned long _s);

rand 関数を seed _s を用いて初期化する。

    prob irand_uni_r(void);

[0,1] の一様乱数を生成する。

    int  irand_uni_i(int _max);

{0,1,...,_max-1} の離散一様乱数を生成する。


    int irand_cat(int _n, prob *_th);

長さ _n の確率ベクトル _th で定義される Categorical 分布からサンプリングを行う。

    int irand_catl(int _n, prob *_lth);

長さ _n の log 確率ベクトル _lth で定義される Categorical 分布からサンプリングを行う。

    void irand_dir(int _n, prob *_th, prob *_a);

長さ _n の確率ベクトル _a で定義される Dirichlet 分布から  
確率ベクトルをサンプリングし _th に格納する。

    prob irand_dir_kld(int _n, prob *_a, prob *_b);

長さ _n の確率ベクトル _a, _b で定義される２つの Dirichlet 分布の
KL-divergence を計算する。

    prob irand_dir_log_z(int _n, prob *_a);

長さ _n の確率ベクトル _a で定義される Dirichlet 分布の
正規化項 Z(_a) を計算する。

    void irand_dirl(int _n, prob *_lth, prob *_la);

長さ _n の log 確率ベクトル _la で定義される Dirichlet 分布から  
log 確率ベクトルをサンプリングし _lth に格納する。

    prob irand_dirl_kld(int _n, prob *_la, prob *_lb);

長さ _n の log 確率ベクトル _la で定義される Dirichlet 分布の
KL-divergence を計算する。

    prob irand_dirl_log_z(int _n, prob *_a);

長さ _n の log 確率ベクトル _la で定義される Dirichlet 分布の
正規化項の log を計算する。

    prob irand_gam(prob _a);

パラメータ _a で定義される Gamma 分布よりサンプリングを行う。
