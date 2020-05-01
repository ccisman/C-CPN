#define N 100
#define fun bor

extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern void __VERIFIER_assume(int);
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
extern short __VERIFIER_nondet_short(void);
extern int __VERIFIER_nondet_int();

short SIZE;

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

int main()
{
	int x[N];
	int temp;
	int ret;
	int ret2;
	int ret5;

	SIZE = __VERIFIER_nondet_short();
	if(SIZE > 1)
	{
		int i;
		short a[100];
		long long sum=2;
		
		for(int i = 0; i < SIZE; i++) 
		{
		  a[i] = __VERIFIER_nondet_short();
		}

		for(i = 0; i < SIZE; i++ )
		{
			sum = sum + a[i];
		}

		for(i = 0; i < SIZE; i++)
		{
			sum = sum - a[i];
		}
		__VERIFIER_assert(sum == 0);
	}
	
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
	return 1;
}
