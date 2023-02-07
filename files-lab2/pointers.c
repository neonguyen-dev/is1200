
//Written by Neo Nguyen and co-developed by Peter Patranika
//This only applies for methods copycodes and work, and int variables and int pointers.

#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1values[20];
int list2values[20];

int* list1 = list1values;
int* list2 = list2values;

int count = 0;

void copycodes(char* text, int* list, int* countpointer){
  while((int)*text != 0)
  {
    *list = (int)*text;
    text++;
    list++;
    *countpointer += 1;
  }
}

void work(){ 
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
