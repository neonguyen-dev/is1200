/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 6

void print_number(int n)
{
  printf("%10d", n);
}

void print_sieves(int n){
  clock_t start_time;
  clock_t end_time;
  double currentTime;

  start_time = clock();

  int values[n];
  int currentColumn = 0;

  for(int i = 2; i < n; i++){
    values[i] = 1;
  }


  for(int i = 2; i*i < n; i++){
    if(values[i] != 0){
      for(int j = i*i; j < n; j += i){
        values[j] = 0;
      }
    }
  }
  
//print the numbers
  for(int i = 2; i < n; i++){
    if(values[i] != 0){
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
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}