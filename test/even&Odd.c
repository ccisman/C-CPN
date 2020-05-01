extern void __VERIFIER_error() __attribute__ ((__noreturn__));
extern int __VERIFIER_nondet_int();
extern short __VERIFIER_nondet_short();
void __VERIFIER_assert(int cond) {
  if (!(cond)) {
    ERROR: __VERIFIER_error();
  }
  return;
}
int main(void) {
  unsigned int x = 0;
  unsigned int y = 1;
  while (__VERIFIER_nondet_int()) {
    x += 2;
  }
  __VERIFIER_assert(!(x % 2));
  while (__VERIFIER_nondet_short()) {
    y += 2;
  }
  __VERIFIER_assert(y % 2);
  return 0;
}
