#define N 100
#define fun bAnd
extern void __VERIFIER_error() __attribute__ ((__noreturn__));
/* Example from "Towards an industrial use of FLUCTUAT on safety-critical 
   avionics software" by Delmas, Goubault, Putot, Souryis, Tekkal,
   and Védrine. Published in FMICS 09.

   Padé approximation of arctan.
*/


extern double __VERIFIER_nondet_double();
extern void __VERIFIER_assume(int expression);
void __VERIFIER_assert(int cond) { if (!(cond)) { ERROR: __VERIFIER_error(); } return; }

extern int __VERIFIER_nondet_int();

const double Pi=3.141592653589793238;

double PADE_2_2(double x) 
{
  double x_2;
  x_2=x*x;
  return 1. - x_2 / (3. + 9./5.*x_2);
}

double ARCTAN_0_1(double x)
{
  return x*PADE_2_2(x);
}

double ARCTAN_POS(double x)
{
  if (x > 1.) return Pi / 2. - ARCTAN_0_1(1. / x);
  else return ARCTAN_0_1(x);
}

double ARCTAN(double x)
{
  if (x < 0) return -ARCTAN_POS(-x);
  else return ARCTAN_POS(x);
}

int bAnd (int x[N])
{
  int i;
  long long res;
  res = x[0];
  for (i = 1; i < N; i++) {
    res = res & x[i];
  }
  return res;
}

int main()
{
  double a, r;
  int x[N];
  int temp;
  int ret;
  int ret2;
  int ret5;

  a = __VERIFIER_nondet_double();
  __VERIFIER_assume(a >= -1.79e308 && a <= 1.79e308);

  r = ARCTAN(a);
  
  __VERIFIER_assert(r >= -1.571 && r <= 1.571);
  
  for (int i = 0; i < N; i++) {
    x[i] = __VERIFIER_nondet_int();
  }

  ret = fun(x);

  temp=x[0];x[0] = x[1]; x[1] = temp;
  ret2 = fun(x);
  temp=x[0];
  for(int i =0 ; i<N-1; i++){
     x[i] = x[i+1];
  }
  x[N-1] = temp;
  ret5 = fun(x);

  if(ret != ret2 || ret !=ret5){ 
    __VERIFIER_error();
  }
  
  return 0;
}
