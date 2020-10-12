#include <stdio.h>
#include "str2dec.h"

int main(int argc, char *argv[]) {
  size_t num;
  short expo;
  
  for(int i = 1; i < argc; i++) {
    int res = str2dec(argv[i], &num, &expo);
    if (res != 0) { 
      printf("Error\n"); 
      return 1;
    }
    
    printf("num %ld\t expo %d\n", num, expo);
  }
  return 0;
}