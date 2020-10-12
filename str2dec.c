#include "str2dec.h"

static int str2dec_internal(const char *str, size_t *num, short *expo, int scientific) {
  int dot = 0;
  int sign = 1;
  int leading = 1;

  *num = 0;
  *expo = -32767; // MIN_SHORT

  while (*str != '\0') {
    switch (*str) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *num *= 10;
      *num += *str - '0';
      *expo += 1;
      break;
    case '.':
      if (!dot) {
        dot = 1;
        *expo = 0;
        break;
      }
      goto error;
    case '-':
      sign = -1;
    case '+':
      if (leading) { 
        leading = 0;
        break;
      }
      goto error;
    case 'e':
    case 'E':
      if (scientific != 0) goto error;
      
      size_t sciNum;
      short sciExp;
      str2dec_internal(str + 1, &sciNum, &sciExp, 1);
      if (sciExp != 0) goto error;
      *expo -= sciNum;
      while (*expo < 0) {
        *num *= 10;
        *expo += 1;
      }
      goto end;
    default:
error:
      return -1;    }
    str++;
  }

end:
  while (*expo > 0 && *num % 10 == 0) {
    *num /= 10;
    *expo -= 1;
  }
  if (*expo < 0) *expo = 0;
  *num *= sign;
  return 0;
}

int str2dec(const char *str, size_t *num, short *expo) {
  str2dec_internal(str, num, expo, 0);
}
