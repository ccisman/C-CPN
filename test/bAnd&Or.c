#define N 100
#define fun bAnd
#define fun1 bor

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern int __VERIFIER_nondet_int();
extern short __VERIFIER_nondet_short();

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

int bor (int x[N])
{
  int i;
  long long res;
  res = x[0];
  for (i = 1; i < N; i++) {
    res = res | x[i];
  }
  return res;
}

int main ()
{
  int x[N];
  int temp;
  int ret;
  int ret2;
  int ret5;
  int y[N];
  int temp_y;
  int ret_y;
  int ret2_y;
  int ret5_y;

  for (int i = 0; i < N; i++) {
    x[i] = __VERIFIER_nondet_int();
  }
  for (int i = 0; i < N; i++) {
    y[i] = __VERIFIER_nondet_short();
  }

  ret = fun(x);
  ret_y = fun1(y);

  temp=x[0];x[0] = x[1]; x[1] = temp;
  temp_y=y[0];y[0] = y[1]; y[1] = temp_y;
  ret2 = fun(x);
  ret2_y = fun1(y);
  temp=x[0];
  temp_y=y[0];
  for(int i =0 ; i<N-1; i++){
     x[i] = x[i+1];
  }
  for(int i =0 ; i<N-1; i++){
     y[i] = y[i+1];
  }
  x[N-1] = temp;
  y[N-1] = temp_y;
  ret5 = fun(x);
  ret5_y = fun1(y);

  if(ret != ret2 || ret !=ret5){ 
    __VERIFIER_error();
  }

  return 1;
}
