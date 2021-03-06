#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define DIGIT 250
#define KETA DIGIT * 2
#define SHIFT 1
#define RADIX 10000

typedef struct {
  unsigned long n[KETA];
  int sign;
} NUMBER;

// 表示系
void dispNumber(NUMBER *);
void fdispNumber(NUMBER *, FILE *);
// 設定系
void clearByZero(NUMBER *);
int setSign(NUMBER *, int);
int getSign(NUMBER *);
void setClear();
void getAbs(NUMBER *, NUMBER *);
void copyNumber(NUMBER *, NUMBER *);
int numComp(NUMBER *, NUMBER *);
void swap(NUMBER *, NUMBER *);
int isZero(NUMBER *);
int searchKeta(NUMBER *);
// 計算系
int mulBy10000(NUMBER *, NUMBER *);
int divBy10000(NUMBER *, NUMBER *);
int mulByN(NUMBER *, NUMBER *, int);
int add(NUMBER *, NUMBER *, NUMBER *);
int sub(NUMBER *, NUMBER *, NUMBER *);
int increment(NUMBER *, NUMBER *);
int decrement(NUMBER *, NUMBER *);
int multiple(NUMBER *, NUMBER *, NUMBER *);
int divide(NUMBER *, NUMBER *, NUMBER *, NUMBER *);
int sqrt_newton(NUMBER *, NUMBER *);
// 変換系
int setInt(NUMBER *, long);