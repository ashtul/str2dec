#include <stdio.h>
#include "str2dec.h"

int main(int argc, char *argv[]) {
  __int128_t num;
  short expo;
  
  for(int i = 1; i < argc; i++) {
    int res = str2dec(argv[i], strlen(argv[i]), &num, &expo);
    if (res != 0) { 
      printf("Error\n"); 
      return 1;
    }
    
    printf("num %ld\t expo %d\n", (size_t)num, expo);
  }

  char arr[40] = {0};
  dec2str(123456789, 4, arr, 40);
  printf("%s\n", arr);


  return 0;
}