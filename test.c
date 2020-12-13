#include <stdio.h>
#include <limits.h>

int main (){
  long long n = -60;
  printf("n: %lld\n", n);
  unsigned long long un = n;
  printf("un: %llu\n", un);
  printf("%d", INT_MIN);
}
