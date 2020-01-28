#include "mulprec.h"

int archimedes(void);
int stormer(void);
int salamin(void);
int wagon(void);
int neipia(void);

int main(void) {
  // printf("return = %d\n", archimedes());
  printf("return = %d\n", stormer());
  // printf("return = %d\n", wagon());
  // printf("return = %d\n", salamin());
  // printf("return = %d\n", neipia());
  /*NUMBER a,b,c;
  setClear();
  setInt(&a,1739292929);
  mulByN(&a, &b, 1);
  setInt(&c, -50000);
  clearByZero(&a);
  clearByZero(&b);
  clearByZero(&c);*/
  /*copyPartOfNumber(&b, &c, 1, 3);
  printf("c = ");
  dispNumber(&c);
  printf("\n");*/
  // printf("keta = %d\n",searchKeta(&b));
  /*NUMBER a, b, c, d;
  int count = 0, data1, data2,data3;
  FILE *FP, *FP2;
  srandom(time(NULL));
  clearByZero(&a);
  clearByZero(&b);
  clearByZero(&c);
  clearByZero(&d);
  printf("a = ");
  dispNumber(&a);
  printf("\n");
  setInt(&a, 1739212129);
  setInt(&b, 888888888);
  if((FP = fopen("check.txt", "w")) == NULL) {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  if((FP2 = fopen("check2.txt", "w")) == NULL) {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  while(count < 1000000) {
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    data1 = random() % 100000000;
    data2 = random() % 100 + 1;
    setInt(&a, data1);
    setInt(&b, data2);
    setSign(&a, random() % 2 == 1 ? +1 : -1);
    if(getSign(&a) == -1){
      data1 -= data1 * 2;
    }
    setSign(&b, random() % 2 == 1 ? +1 : -1);
    if(getSign(&b) == -1) {
      data2 -= data2 * 2;
    }
    // printf("data1 = %d data2 = %d\n", data1, data2);
    divide(&a, &b, &c,&d);
    data3 = data1 / data2;
    setInt(&d, data3);
    if(numComp(&c, &d) != 0 && isZero(&c) == 0) {
      printf("a = %d\n", data1);
      printf("b = %d\n", data2);
      printf("c = %d\n", data3);
      dispNumber(&c);
      printf("\n");
      break;
    }
    fdispNumber(&c, FP);
    fprintf(FP, "\n");
    fprintf(FP2, (data3) >= 0 ? "+" : "-");
    fprintf(FP2, "%080d\n", abs(data3));
    count++;
  }
  fclose(FP);
  fclose(FP2);
  // divide(&a, &b, &c, &d);
  // fastpower(&a, &b, &c);
  // squareroot(&a, &c);
  // sqrt_newton(&a,&c);
  // mulBy10000(&b,&a);
  // mulByN(&a, &b, 8);
  //add(&a, &b, &c);
   //sub(&a, &b, &c);
  // decrement(&a, &c);
  multiple(&a, &b, &c);
  // fastpower(&a, &b, &c);*/
  /*printf("a = ");
  dispNumber(&a);
  printf("\n");
  printf("b = ");
  dispNumber(&b);
  printf("\n");
  printf("c = ");
  dispNumber(&c);
  printf("\n");*/
}

int archimedes(void) {
  struct timeval tv;
  double tstart, tend;
  gettimeofday(&tv, NULL);
  tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  NUMBER a0, b0, an, bn, anext, bnext, two, three, temp, temp2, temp3, modulo;
  unsigned int i = 0;
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
  setClear();
  setInt(&two, 2);
  setInt(&three, 3); // 3を多倍長変数に代入
  mulByN(&three, &temp, DIGIT * 2);
  sqrt_newton(&temp, &temp3);    // squareroot(3)を求める
  setInt(&temp2, 2);             // 2を多倍長変数に代入
  multiple(&temp3, &temp2, &a0); // squareroot(3)*2 を a0に代入
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  /*x = sqrt(3) * 2 * pow(10,8);
  printf("x = %lf\n", x);
  y = (int)x;
  printf("y = %d\n",y);
  setInt(&a0, y);*/
  copyNumber(&a0, &an); // a0をanにコピー
  setInt(&temp, 3);
  mulByN(&temp, &b0, DIGIT); // b0に3を代入
  copyNumber(&b0, &bn);      // b0をbnにコピー
  printf("a0 = ");
  dispNumber(&an);
  printf("\n");
  printf("b0 = ");
  dispNumber(&bn);
  printf("\n");
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("ready time = %lf\n", tend - tstart);
  while(i < DIGIT * 10) {         // 何かしらのwhile文
    multiple(&an, &two, &temp);   // 2 * anを計算
    multiple(&temp, &bn, &temp2); // (2 * an) * bnを計算
    add(&an, &bn, &temp3);        // an + bnを計算
    divide(&temp2, &temp3, &anext,
           &modulo); // (2 * an *  bn) / (an + bn)を計算してanextに代入
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    if(numComp(&anext, &an) == 0) { // anが収束したときwhile内から抜ける
      break;
    }
    multiple(&anext, &bn, &temp); // anext * bnを計算
    sqrt_newton(&temp, &bnext); // squareroot(anext * bn)を計算してbnextに代入
    copyNumber(&anext, &an); // anextをanにコピー
    copyNumber(&bnext, &bn); // bnextをbnにコピー
    clearByZero(&anext);
    clearByZero(&bnext);
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    i++; // インクリメント
  }
  printf("n = %d : \n", i);
  printf("pi = ");
  dispNumber(&an); // 表示
  printf("\n");
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("total time = %lf\n", tend - tstart);
  return 0;
}
/*
int wagon(void) {
  struct timeval tv;
  double tstart, tend, loopstart, loopend, nstart, nend;
  gettimeofday(&tv, NULL);
  tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  NUMBER a0, a1, a2, a3, an, bn, temp, temp2, temp3, temp4, temp5, temp6, temp7,
      temp8, notuse, one, two, three, four, six, tw, tef, ff, otft, pi, pi2, n;
  setClear();
  setInt(&one, 1);
  setInt(&two, 2);
  setInt(&three, 3);
  setInt(&four, 4);
  setInt(&six, 6);
  setInt(&tw, -12);
  setInt(&tef, 384);
  setInt(&ff, 45);
  setInt(&otft, -1215);
  mulByN(&one, &an, DIGIT);
  clearByZero(&pi);
  clearByZero(&pi2);
  int i;
  for(i = 1; i < 1000000; i++) {
    gettimeofday(&tv, NULL);
    loopstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    setInt(&n, i);
    clearByZero(&temp);
    fastpower(&n, &three, &temp);

    clearByZero(&temp2);
    clearByZero(&temp3);
    clearByZero(&temp4);
    multiple(&an, &tw, &temp2);
    increment(&n, &temp3);
    multiple(&temp, &temp3, &temp4);
    divide(&temp2, &temp4, &a0, &notuse);

    clearByZero(&temp2);
    clearByZero(&temp3);
    clearByZero(&temp4);
    multiple(&an, &tef, &temp2);
    add(&n, &two, &temp3);
    multiple(&temp, &temp3, &temp4);
    divide(&temp2, &temp4, &a1, &notuse);

    clearByZero(&temp2);
    clearByZero(&temp3);
    clearByZero(&temp4);
    clearByZero(&temp5);
    multiple(&an, &ff, &temp2);           // 10^n * 45
    multiple(&n, &four, &temp5);          // 4n
    add(&temp5, &two, &temp3);            // 4n + 2
    multiple(&temp, &temp3, &temp4);      // n^3 * (4n + 2)
    divide(&temp2, &temp4, &a2, &notuse); //(10^n * 45) / (n^3 * (4n + 2))

    clearByZero(&temp2);
    clearByZero(&temp3);
    clearByZero(&temp4);
    clearByZero(&temp5);
    multiple(&an, &otft, &temp2);         // 10^n * -1215
    multiple(&n, &four, &temp5);          // 4n
    add(&temp5, &six, &temp3);            // 4n + 6
    multiple(&temp, &temp3, &temp4);      // n^3 * (4n + 6)
    divide(&temp2, &temp4, &a3, &notuse); //(10^n * -1215) / (n^3 * (4n + 6))

    clearByZero(&temp2);
    clearByZero(&temp6);
    clearByZero(&temp7);
    clearByZero(&temp8);
    add(&a0, &a1, &temp6);
    add(&a2, &a3, &temp7);
    add(&temp6, &temp7, &temp8);
    // divide(&temp8, &temp, &temp2,&notuse);
    clearByZero(&temp);
    add(&temp8, &pi2, &temp);
    copyNumber(&temp, &pi2);
    gettimeofday(&tv, NULL);
    loopend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("loop time = %lf\n", loopend - loopstart);
  }
  sqrt_newton(&pi2, &pi);
  printf("pi = ");
  dispNumber(&pi);
  printf("\n");
  return 0;
}

int salamin(void) {
  NUMBER a0, b0, t0, p0, an, anext, bn, bnext, tn, tnext, pn, pnext, temp,
      temp2, temp3, temp4, notuse, one, two, four, ten, pi;
  int i;
  setClear();
  setInt(&one, 1);
  setInt(&two, 2);
  setInt(&four, 4);
  setInt(&ten, 10);
  clearByZero(&temp);
  clearByZero(&pn);
  clearByZero(&pnext);
  mulByN(&one, &an, DIGIT);
  mulByN(&two, &b0, DIGIT * 2);
  sqrt_newton(&b0, &temp);
  divide(&temp, &two, &bn, &notuse);
  mulByN(&one, &t0, DIGIT);
  divide(&t0, &four, &tn, &notuse);
  // mulByN(&one, &p0, DIGIT);
  copyNumber(&one, &pn);
  printf("a0 = ");
  dispNumber(&an);
  printf("\n");
  printf("b0 = ");
  dispNumber(&bn);
  printf("\n");
  printf("t0 = ");
  dispNumber(&tn);
  printf("\n");
  printf("p0 = ");
  dispNumber(&pn);
  printf("\n");
  while(1) {
    printf("an = ");
    dispNumber(&an);
    printf("\n");
    printf("bn = ");
    dispNumber(&bn);
    printf("\n");
    printf("tn = ");
    dispNumber(&tn);
    printf("\n");
    printf("pn = ");
    dispNumber(&pn);
    printf("\n");
    clearByZero(&temp);
    add(&an, &bn, &temp);
    divide(&temp, &two, &anext, &notuse);
    clearByZero(&temp);
    multiple(&an, &bn, &temp);
    sqrt_newton(&temp, &bnext);
    clearByZero(&temp);
    sub(&an, &anext, &temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    // setInt(&two, 2);
    fastpower(&temp, &two, &temp2);
    while(searchKeta(&temp) != searchKeta(&temp2)) {
      clearByZero(&temp3);
      divBy10000(&temp2, &temp3);
      copyNumber(&temp3, &temp2);
    }
    printf("temp2 = ");
    dispNumber(&temp2);
    printf("\n");
    divide(&temp2, &ten, &temp3, &notuse);
    copyNumber(&temp3, &temp2);
    clearByZero(&temp3);
    printf("temp2 = ");
    dispNumber(&temp2);
    printf("\n");
    multiple(&temp2, &pn, &temp3);
    printf("tn = ");
    dispNumber(&tn);
    printf("\n");
    printf("temp3 = ");
    dispNumber(&temp3);
    printf("\n");
    sub(&tn, &temp3, &tnext);
    // setInt(&two, 2);
    multiple(&pn, &two, &pnext);
    if(numComp(&an, &anext) == 0) {
      break;
    }
    copyNumber(&anext, &an);
    copyNumber(&bnext, &bn);
    copyNumber(&tnext, &tn);
    copyNumber(&pnext, &pn);
  }
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  clearByZero(&temp4);
  add(&an, &bn, &temp);
  fastpower(&temp, &two, &temp2);
  printf("temp2 = ");
  dispNumber(&temp2);
  printf("\n");
  // mulByN(&temp2, &temp4, DIGIT * 5);
  multiple(&tn, &four, &temp3);
  printf("temp3 = ");
  dispNumber(&temp3);
  printf("\n");
  clearByZero(&pi);
  divide(&temp2, &temp3, &pi, &notuse);
  printf("pi = ");
  dispNumber(&pi);
  printf("\n");
  return 0;
}*/

int stormer(void) {
  struct timeval tv;
  double tstart, tend;
  gettimeofday(&tv, NULL);
  tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  NUMBER a0, an, bn, c, two,  tf, notuse, j, temp, temp2, tanA, tanB, tanC,
      eight, sf, fs, fsfs, four, tsn, tsntsn, left, center, right, ans;
  int i = 0;
  setClear();
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&tanA);
  clearByZero(&tanB);
  clearByZero(&left);
  clearByZero(&center);
  clearByZero(&right);
  clearByZero(&ans);
  clearByZero(&c);
  clearByZero(&an);
  setInt(&two, 2);
  setInt(&a0, 1);
  setInt(&eight, 8);
  setInt(&sf, 64);
  setInt(&fs, 57);
  setInt(&fsfs, 57 * 57);
  setInt(&tf, 24);
  setInt(&tsn, 239);
  setInt(&tsntsn, 239 * 239);
  setInt(&j, 3);
  setInt(&four, 4);
  mulByN(&a0, &c, DIGIT);
  divide(&c, &eight, &an, &notuse);
  copyNumber(&an, &bn);
  while(1) {
    divide(&an, &sf, &temp, &notuse);
    if(isZero(&temp) == 1) {
      break;
    }
    copyNumber(&temp, &an);
    divide(&an, &j, &temp2, &notuse);
    clearByZero(&temp);
    if(i == 0) {
      sub(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 1;
    } else if(i == 1) {
      add(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 0;
    } else {
      return -1;
    }
    clearByZero(&temp);
    clearByZero(&temp2);
    add(&j, &two, &temp);
    copyNumber(&temp, &j);
    clearByZero(&temp);
  }
  copyNumber(&bn, &tanA);
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&c);
  clearByZero(&an);
  i = 0;
  setInt(&a0, 1);
  setInt(&j, 3);
  mulByN(&a0, &c, DIGIT);
  divide(&c, &fs, &an, &notuse);
  copyNumber(&an, &bn);
  while(1) {
    divide(&an, &fsfs, &temp, &notuse);
    if(isZero(&temp) == 1) {
      break;
    }
    copyNumber(&temp, &an);
    divide(&an, &j, &temp2, &notuse);
    if(i == 0) {
      sub(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 1;
    } else if(i == 1) {
      add(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 0;
    } else {
      return -1;
    }
    clearByZero(&temp);
    clearByZero(&temp2);
    add(&j, &two, &temp);
    copyNumber(&temp, &j);
    clearByZero(&temp);
  }
  copyNumber(&bn, &tanB);

  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&c);
  clearByZero(&an);
  i = 0;
  setInt(&a0, 1);
  setInt(&j, 3);
  mulByN(&a0, &c, DIGIT);
  divide(&c, &tsn, &an, &notuse);
  copyNumber(&an, &bn);
  while(1) {
    divide(&an, &tsntsn, &temp, &notuse);
    if(isZero(&temp) == 1) {
      break;
    }
    copyNumber(&temp, &an);
    divide(&an, &j, &temp2, &notuse);
    if(i == 0) {
      sub(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 1;
    } else if(i == 1) {
      add(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 0;
    } else {
      return -1;
    }
    clearByZero(&temp);
    clearByZero(&temp2);
    add(&j, &two, &temp);
    copyNumber(&temp, &j);
    clearByZero(&temp);
  }
  copyNumber(&bn, &tanC);
  multiple(&tanA, &tf, &left);
  multiple(&tanB, &eight, &center);
  multiple(&tanC, &four, &right);
  add(&left, &center, &temp);
  add(&temp, &right, &ans);
  printf("pi = ");
  dispNumber(&ans);
  printf("\n");
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("total time = %lf\n", tend - tstart);
  return 0;
}

int neipia(void) {
  struct timeval tv;
  double tstart, tend;
  gettimeofday(&tv, NULL);
  tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  setClear();
  NUMBER a, b, c, d, e, notuse, temp, temp2, temp3;
  setInt(&a, 1);
  mulByN(&a, &c, DIGIT);
  setInt(&b, 1);
  mulByN(&a, &e, DIGIT);
  while(1) {
    clearByZero(&d);
    factorial(&b, &d);
    divide(&c, &d, &temp2, &notuse);
    if(isZero(&temp2) == 1) {
      break;
    }
    add(&e, &temp2, &temp3);
    copyNumber(&temp3, &e);
    clearByZero(&temp2);
    clearByZero(&temp3);
    increment(&b, &temp);
    copyNumber(&temp, &b);
    clearByZero(&temp);
  }
  printf("e = ");
  dispNumber(&e);
  printf("\n");
  clearByZero(&d);
  sqrt_newton(&e, &d);
  printf("sqrt(e) = ");
  dispNumber(&d);
  printf("\n");
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("total time = %lf\n", tend - tstart);
  return 0;
}