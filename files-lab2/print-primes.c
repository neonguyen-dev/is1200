/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

// Written by Peter Patranika and co-developed by Neo Nguyen
// This only includes methods is_prime from last assignment, print_number and print_primes 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 6
int is_prime(int n){
  for(int i = 2; i < n; i ++){
    if ((n % i) == 0){
      return 0;
    }
  }
  return 1;
}

void print_number(int n)
{
  printf("%10d ", n);
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  clock_t start_time;
  clock_t end_time;
  double currentTime;

  start_time = clock();

  int currentColumn = 0;
  for (int i = 2; i < n; i++)
  {
    if(is_prime(i))
    {
      print_number(i);
      currentColumn++;
    }
    if(currentColumn == COLUMNS)
    {
      printf("\n");
      currentColumn = 0;
    }
  }
  end_time = clock();
  currentTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  
  printf("\n%f", currentTime);

  /*
  printf("%10d ", 2);
  printf("%10d ", 3);
  printf("%10d ", 5);
  printf("%10d ", 7);
  printf("%10d ", 11);
  printf("%10d ", 13);
  printf("\n");
  printf("%10d ", 17);
  printf("%10d ", 19);

  printf("\n");
  */
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
