/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

// Written by Peter Patranika and co-developed by Neo Nguyen
// Only applies for is_prime function
#include <stdio.h>

int is_prime(int n){
  for(int i = 2; i < n; i ++){
    if ((n % i) == 0){
      return 0;
    }
  }
  return 1;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
