#include "mulprec.h"
// xorshiftが何故か死んでいる．何故 -> 関数の初期化をしていなかった

// disp Multiple Number
void dispNumber(struct NUMBER *a)
{
  int i;
  if (getSign(a) == +1)
  {
    printf("+");
  }
  if (getSign(a) == -1)
  {
    printf("-");
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    printf("%2d", a->n[i]);
  }
}

// write Number to File
void fdispNumber(struct NUMBER *a, FILE *FP)
{
  int i;
  if (getSign(a) == +1)
  {
    fprintf(FP, "+");
  }
  if (getSign(a) == -1)
  {
    fprintf(FP, "-");
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    fprintf(FP, "%d", a->n[i]);
  }
}

// check Number is ZERO
int isZero(struct NUMBER *a)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    if (a->n[i] != 0)
    {
      return -1;
    }
  }
  return 0;
}

// clear Number by ZERO
void clearByZero(struct NUMBER *a)
{
  int i;

  for (i = 0; i < KETA; i++)
  {
    a->n[i] = 0;
  }
  setSign(a, +1);
}

// set NUMBER by randomNUMBER
void setRnd(struct NUMBER *a, int k)
{
  int i = 0;
  for (i = 0; i < k; i++)
  {
    a->n[i] = abs((int)pcg32()) % 10;
  }
  setSign(a, (pcg32() % 2 == 0) ? -1 : +1);
}

// copy NUMBER a to b
void copyNumber(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = a->n[i];
  }
  setSign(b, getSign(a));
}

// copy Number a to b and b become +
void getAbs(struct NUMBER *a, struct NUMBER *b)
{
  copyNumber(a, b);
  setSign(b, +1);
}

// set a's Signature from s
int setSign(struct NUMBER *a, int s)
{
  if (s == +1)
    a->sign = +1;
  else if (s == -1)
    a->sign = -1;
  else
    return -1;
  return 0;
}

// return a's Signature
int getSign(struct NUMBER *a)
{
  return a->sign == +1 ? +1 : -1;
}

// compare a and b
int numComp(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  if (getSign(a) != getSign(b))
  {
    return getSign(a) > getSign(b) ? 1 : -1;
  }
  if (getSign(a) == +1)
  {
    for (i = KETA - 1; i >= 0; i--)
    {
      if (a->n[i] > b->n[i])
      {
        return 1;
      }
      if (a->n[i] < b->n[i])
      {
        return -1;
      }
    }
    return 0;
  }
  if (getSign(a) == -1)
  {
    for (i = KETA - 1; i >= 0; i--)
    {
      if (a->n[i] < b->n[i])
      {
        return 1;
      }
      if (a->n[i] > b->n[i])
      {
        return -1;
      }
    }
    return 0;
  }
  return -10000;
}

// swap a with b
void swap(struct NUMBER *a, struct NUMBER *b)
{
  struct NUMBER c;
  clearByZero(&c);
  int i;
  for (i = 0; i < KETA; i++)
  {
    c.n[i] = a->n[i];
  }
  setSign(&c, a->sign);
  for (i = 0; i < KETA; i++)
  {
    a->n[i] = b->n[i];
  }
  setSign(a, b->sign);
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = c.n[i];
  }
  setSign(b, c.sign);
}

// left shift
int mulBy10(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA - 1; i++)
  {
    b->n[i + 1] = a->n[i];
  }
  setSign(b, getSign(a));
  b->n[0] = 0;
  if (a->n[0] != 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

// right shift
int divBy10(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA - 1; i++)
  {
    b->n[i] = a->n[i + 1];
  }
  setSign(b, getSign(a));
  b->n[KETA - 1] = 0;
  if (a->n[KETA - 1] != 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

// c = a + b
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
  int i, e = 0, d;
  struct NUMBER x, y;
  clearByZero(&x);
  clearByZero(&y);
  setSign(c, +1);
  if (getSign(a) == -1 && getSign(b) == -1)
  {
    getAbs(a, &x);
    getAbs(b, &y);
    setSign(c, -1);
  }
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &x);
    return sub(b, &x, c);
  }
  if (getSign(a) == +1 && getSign(b) == -1)
  {
    getAbs(b, &y);
    return sub(a, &y, c);
  }
  for (i = 0; i < KETA; i++)
  {
    d = a->n[i] + b->n[i] + e;
    c->n[i] = d % 10;
    e = d / 10;
  }
  return e != 0 ? -1 : 0;
}

// c = a - b
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
  int i, h = 0, flag = 0;
  struct NUMBER x, y;
  clearByZero(&x);
  clearByZero(&y);
  // (getSign(a) == +1 || getSign(a) == -1) && getSign(b) == -1
  if (getSign(b) == -1)
  {
    getAbs(b, &y);
    return add(a, &y, c);
  }
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &x);
    setSign(c, -1);
    return add(&x, b, c);
  }
  if (numComp(a, b) < 0)
  {
    swap(a, b);
    setSign(c, -1);
    flag = 1;
  }
  else
  {
    setSign(c, +1);
  }
  for (i = 0; i < KETA; i++)
  {
    a->n[i] -= h;
    if (a->n[i] >= b->n[i])
    {
      c->n[i] = a->n[i] - b->n[i];
      h = 0;
    }
    else
    {
      c->n[i] = 10 + a->n[i] - b->n[i];
      h = 1;
    }
  }
  if (flag == 1)
  {
    swap(a, b);
  }
  return h != 0 ? -1 : 0;
}

int increment(struct NUMBER *a, struct NUMBER *b)
{
  struct NUMBER one;
  int r;

  setInt(&one, +1);

  r = add(a, &one, b);

  return r;
}

int decrement(struct NUMBER *a, struct NUMBER *b)
{
  struct NUMBER one;
  int r;
  setInt(&one, 1);
  r = sub(a, &one, b);
  return r;
}

int simpleMultiple(int a, int b, int *c)
{
  int i = 0, j;
  /*for (i = 0; i < b; i++)
  {
    *c += a;
    if (a > INT32_MAX - *c)
    {
      return -500;
    }
  }*/
  if (b < 0)
    j = abs(b);
  else
    j = b;
  while (1)
  {
    if (i >= j)
    {
      break;
    }
    if (a >= 0)
    {
      if (a > INT32_MAX - *c)
      {
        return -400;
      }
    }
    else
    {
      if (a < INT32_MIN - *c)
      {
        return -500;
      }
    }
    *c += a;
    //printf("i = %d j = %d", i, j);
    //printf("test3 = %d\n", *c);
    i++;
  }
  if (b < 0)
    *c -= *c * 2;
  return 0;
}

// TODO:自信ない
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
  int i = 0, j = 0, aj, bi, h, e, r;
  struct NUMBER d, f, x, y;
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &x);
    r = multiple(&x, b, c);
    setSign(c, -1);
    return r;
  }
  if (getSign(a) == +1 && getSign(b) == -1)
  {
    getAbs(b, &y);
    r = multiple(a, &y, c);
    setSign(c, -1);
    return r;
  }
  if (getSign(a) == -1 && getSign(b) == -1)
  {
    getAbs(a, &x);
    getAbs(b, &y);
    r = multiple(&x, &y, c);
    return r;
  }
  for (i = 0; i < KETA; i++)
  {
    bi = b->n[i];
    h = 0;
    clearByZero(&d);
    for (j = 0; j < KETA; j++)
    {
      aj = a->n[j];
      e = aj * bi + h;
      if (j + i >= KETA)
      {
        //printf("j = %d i = %d aj = %d bi = %d e = %d\n", j, i, aj, bi, e);
        if (e != 0)
        {
          return -1;
        }
        break;
      }
      d.n[j + i] = e % 10;
      h = e / 10;
    }
    if (h != 0)
      return -1;
    clearByZero(&f);
    if (add(c, &d, &f) == -1)
      return -1;
    copyNumber(&f, c);
  }
  return 0;
}

int factorial(struct NUMBER *a, struct NUMBER *b)
{
  struct NUMBER c, d, e, f;
  clearByZero(&c);
  clearByZero(&d);
  clearByZero(&e);
  clearByZero(&f);
  if (numComp(b, &f) == 0)
  {
    copyNumber(a, b);
  }
  copyNumber(a, &c);
  decrement(&c, &d);
  if (numComp(&d, &f) == 0)
  {
    return 0;
  }
  printf("a = ");
  dispNumber(a);
  printf("\n");
  printf("d = ");
  dispNumber(&d);
  printf("\n");
  multiple(b, &d, &e);
  copyNumber(&e, b);
  printf("b = ");
  dispNumber(b);
  printf("\n");
  factorial(&d, b);
}

int simpleDivide(int x, int y, int *z, int *w)
{
  int k;
  int flag = 0;

  if (y == 0)
    return -1;
  if (y < 0)
  {
    flag = 1;
    y = abs(y);
  }
  if (x < 0)
  {
    if (!flag)
      flag = 2;
    else
      flag = 3;
    x = abs(x);
  }
  k = 0;
  while (1)
  {
    if (x < y)
      break;
    x -= y;
    k++;
  }
  switch (flag)
  {
  case 0:
    *z = k;
    *w = x;
    break;
  case 1:
    *z = -k;
    *w = x;
    break;
  case 2:
    *z = -k;
    *w = -x;
    break;
  case 3:
    *z = k;
    *w = -x;
    break;
  default:
    break;
  }
  return 0;
}

int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d)
{
  struct NUMBER m, n, p, q;
  int r;
  if (getSign(a) == +1 && getSign(b) == -1)
  {
    getAbs(b, &p);
    r = divide(a, &p, c, d);
    setSign(c, -1);
    return r;
  }
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &p);
    r = divide(&p, b, c, d);
    setSign(c, -1);
    setSign(d, -1);
    return r;
  }
  if (getSign(a) == -1 && getSign(b) == -1)
  {
    getAbs(a, &p);
    getAbs(b, &q);
    r = divide(&p, &q, c, d);
    setSign(d, -1);
    return r;
  }
  clearByZero(c);
  clearByZero(d);

  if (!isZero(b))
  {
    return -1;
  }

  copyNumber(a, &n);
  while (1)
  {
    //printf("numcomp = %d\n", numComp(&n, b));
    if (numComp(&n, b) < 0)
    {
      copyNumber(&n, d);
      printf("d = ");
      dispNumber(d);
      printf("\n");
      break;
    }
    increment(c, &m);
    copyNumber(&m, c);
    clearByZero(&m);
    sub(&n, b, &m);
    copyNumber(&m, &n);
    clearByZero(&m);
  }
  return 0;
}

// TODO:add辺りでセグフォ(もしくはStack OverFlow)ってる 範囲がおかしいかも 配列外を参照している説ある
/*
int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d)
{
  int i = KETA - 1, k = 0;
  struct NUMBER h, l, m, n, t, x, y, z, temp1, temp2;
  clearByZero(&h);
  clearByZero(&l);
  clearByZero(&m);
  clearByZero(&n);
  clearByZero(&t);
  clearByZero(&x);
  clearByZero(&y);
  clearByZero(&z);
  clearByZero(&temp1);
  clearByZero(&temp2);
  setInt(&m, 10);
  while (i >= KETA - 1)
  {
    //multiple(&m, &h, &l);  // 10h
    mulBy10(&h, &l);
    setInt(&n, a->n[i]);   // a[i]
    add(&l, &n, &t);       // t = 10h + a[i]
    divide(&t, b, &y, &h); // h = t mod b
    clearByZero(&y);
    sub(&t, &h, &y); // t - h
    divide(&y, b, &temp1, &temp2);
    getInt(&temp1, &k);
    c->n[i] = k;
    i--;
  }
  copyNumber(&h, d);
  return 0;
}
*/

// a^b
int fastpower(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
  int x = 0;
  struct NUMBER n;
  struct NUMBER m;
  struct NUMBER o;
  struct NUMBER p;
  getInt(b, &x);
  if (x == 0)
  {
    setInt(c, +1);
  }
  if (x == 1)
  {
    copyNumber(a, c);
    return x;
  }
  if (x % 2 == 0)
  {
    copyNumber(a, &n);
    multiple(a, &n, &m);
    setInt(&o, x / 2);
    fastpower(&m, &o, &p);
    copyNumber(&p, c);
  }
  decrement(b, &n);
  fastpower(a, &n, &p);
  multiple(a, &p, &o);
  copyNumber(&o, c);
}

int gcd(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
  struct NUMBER d, e, f, g, zero;
  clearByZero(&d);
  clearByZero(&e);
  clearByZero(&f);
  clearByZero(&g);
  clearByZero(&zero);
  //setSign(c, -1);
  setInt(c, 1);
  while (1)
  {
    clearByZero(c);
    divide(a, b, &d, c);
    printf("c = ");
    dispNumber(c);
    printf("\n");
    if (numComp(c, &zero) == 0){
      copyNumber(b, c);
      break;
    }
    copyNumber(b, a);
    copyNumber(c, b);
  }
}

int lcm(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
  struct NUMBER temp,temp2,temp3;
  clearByZero(&temp);
  clearByZero(&temp2);
  multiple(a,b,&temp);
  gcd(a, b, &temp2);
  printf("temp2 = ");
  dispNumber(&temp2);
  printf("\n");
  divide(&temp, &temp2, c, &temp3);
  dispNumber(c);
}

int squareroot(struct NUMBER *a, struct NUMBER *b)
{
  struct NUMBER c,temp,two;
  clearByZero(&c);
  clearByZero(&temp);
  clearByZero(&two);
  if(numComp(a,&temp) == -1){
    return -1;
  }
  setInt(&c,1);
  setInt(&two, 2);
  while(numComp(a,&c) != -1){
    sub(a, &c, &temp);
    copyNumber(&temp,a);
    clearByZero(&temp);
    add(&c, &two, &temp);
    copyNumber(&temp,&c);
    clearByZero(&temp);
    increment(b,&temp);
    copyNumber(&temp, b);
    clearByZero(&temp);
  }
}

int isPrime(struct NUMBER *a){
  struct NUMBER b,temp,temp2,temp3;
  clearByZero(&b);
  clearByZero(&temp2);
  clearByZero(&temp3);
  setInt(&b, 2);
  while(numComp(a,&b) != 0){
    clearByZero(&temp2);
    divide(a, &b, &temp, &temp2);
    dispNumber(&temp2);
    printf("\n");
    if(isZero(&temp2) == 0){
      return 1;
    }
    increment(&b,&temp3);
    copyNumber(&temp3, &b);
    clearByZero(&temp3);
  }
  return 0;
}

// set integer to NUMBER
int setInt(struct NUMBER *a, int x)
{
  int i = 0;
  if (x < 0)
  {
    setSign(a, -1);
    x -= x * 2;
  }
  else
  {
    setSign(a, +1);
  }
  for (i = 0; i < KETA; i++)
  {
    a->n[i] = x % 10;
    x -= x % 10;
    x /= 10;
  }
  if (x == 0)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

// stringからi文字ずつint型の配列に入れる
int setIntFromString(struct NUMBER *a, char *x)
{
  unsigned int i;
  for (i = 0; i < strlen(x); i++)
  {
    if (i >= KETA && x[strlen(x) - i - 1] != '-')
    {
      printf("over flow\n");
      return -1;
    }
    if (x[strlen(x) - i - 1] == '-')
    {
      setSign(a, -1);
      return 0;
    }
    a->n[i] = ctoi(x[strlen(x) - i - 1]);
    if (a->n[i] < 0 && a->n[i] > 9)
      return -1;
  }
  setSign(a, +1);
  return 0;
}

int ctoi(char x)
{
  return x - '0';
}

int getInt(struct NUMBER *a, int *x)
{
  int i;
  long temp = 1;
  *x = 0;
  for (i = 0; i < 9; i++)
  {
    if (*x > INT32_MAX - (a->n[i] * temp))
    {
      return -1;
    }
    else
    {
      *x += a->n[i] * temp;
      //printf("a->n[%d] = %d\n", i, a->n[i]);
      temp *= 10;
      //printf("*x = %d\n", *x);
    }
  }
  if (getSign(a) != 1)
  {
    *x -= *x * 2;
  }
  return 0;
}
// TODO: Int型をChar型にして配列に入れるだけ
int getIntAsString(struct NUMBER *a, char *x) /* *xはx[KETA + 1]と扱う(しかない) */
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    x[KETA - i] = (char)(a->n[i] + '0');
  }
  if (getSign(a) != 1)
  {
    x[0] = *("-");
  }
  return 0;
}

/*xorshift_function*/
void xorshiftInit(uint64_t seed)
{
  seed = seed + 0x9E3779B97f4A7C15;
  seed = (seed ^ (seed) >> 30) * 0xBF58476D1CE4E5B9;
  seed = (seed ^ (seed >> 27)) * 0x94D049BB133111EB;
  seed = seed ^ (seed >> 31);
  xorshift_x = seed;
  xorshift_y = seed >> 6;
  seed = seed + 0x9FFFFFFFFFFFFFFF;
  seed = (seed ^ (seed) >> 30) * 0xBF58476D1CE4E5B9;
  seed = (seed ^ (seed >> 28)) * 0x94D049BB133111EB;
  seed = seed ^ (seed >> 31);
  xorshift_z = seed;
  xorshift_w = seed >> 6;
  //printf("x y z w : %lld %lld %lld %lld\n", xorshift_x, xorshift_y, xorshift_z, xorshift_w);
  xorshift();
  xorshift();
  xorshift();
  xorshift();
}

uint32_t rol64(uint32_t x, int k)
{
  return (x << k) | (x >> (64 - k));
}

uint32_t xorshift()
{
  uint32_t result = rol64((uint32_t)xorshift_y * 5, 7) * 9;
  uint64_t t;
  t = xorshift_x ^ (xorshift_x << 17);
  xorshift_z ^= xorshift_x;
  xorshift_w ^= xorshift_y;
  xorshift_y ^= xorshift_z;
  xorshift_x ^= xorshift_w;
  xorshift_z ^= t;
  //w ^= t ^ (t >> 8) ^ (w >> 19);
  xorshift_w = rol64((uint32_t)xorshift_w, 45);
  //printf("result = %lld\n", result);
  return result;
}

/*Permuted congruential generator*/

uint32_t rotr32(uint32_t x, unsigned r)
{
  return x >> r | x << (-r & 31);
}

uint32_t pcg32(void)
{
  uint64_t x = pcg_state;
  unsigned count = (unsigned)(x >> 59); // 59 = 64 - 5

  pcg_state = x * pcg_multiplier + pcg_increment;
  x ^= x >> 18;                              // 18 = (64 - 27)/2
  return rotr32((uint32_t)(x >> 27), count); // 27 = 32 - 5
}

void pcg32_init(uint64_t seed)
{
  pcg_state = seed + pcg_increment;
  (void)pcg32();
}

uint64_t simpleArchimedes(void)
{
  double a0 = 2 * sqrt(3);
  double b0 = 3;
  double anext, bnext;
  double an = a0;
  double bn = b0;
  int i = 0;
  while (i < 100000000)
  {
    anext = (2 * an * bn) / (an + bn);
    bnext = sqrt(anext * bn);
    an = anext;
    bn = bnext;
    printf("an = %.80lf\n", an);
    i++;
  }
  printf("%lld", an);
  return an;
}

int archimedes(void)
{
  struct NUMBER a0, b0, an, bn,anext,bnext,two,three,temp,temp2,temp3,modulo;
  int i = 0;
  clearByZero(&a0);
  clearByZero(&b0);
  clearByZero(&an);
  clearByZero(&bn);
  clearByZero(&anext);
  clearByZero(&bnext);
  clearByZero(&two);
  clearByZero(&three);
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);

  setInt(&three, 3);   // 3を多倍長変数に代入
  squareroot(&three, &temp); // squareroot(3)を求める
  setInt(&two, 2); // 2を多倍長変数に代入
  add(&temp, &two, &a0); // squareroot(3) + 2 を a0に代入
  clearByZero(&temp);
  setInt(&b0, 3);        // b0に3を代入
  copyNumber(&a0, &an);  // a0をanにコピー
  copyNumber(&b0, &bn);  // b0をbnにコピー
  while(i < 10){  // 何かしらのwhile文
    multiple(&two, &an, &temp); // 2 * anを計算
    multiple(&temp, &bn, &temp2); // (2 * an) * bnを計算
    add(&an, &bn, &temp3);            // an + bnを計算
    divide(&temp2,&temp3,&anext,&modulo);// (2 * an * bn) / (an * bn)を計算してanextに代入
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    multiple(&anext, &bn, &temp); // anext * bnを計算
    squareroot(&temp, &bnext);    // squareroot(anext * bn)を計算してbnextに代入
    copyNumber(&anext, &an);      // anextをanにコピー
    copyNumber(&bnext, &bn);      // bnextをbnにコピー
    clearByZero(&anext);
    clearByZero(&bnext);
    clearByZero(&temp);
    printf("an = ");
    dispNumber(&an); // 表示
    printf("\n");
    i++; // インクリメント
  }
}