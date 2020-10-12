#include "str2dec.h"

#include <assert.h>
#include <string.h>

static int str2dec_internal(const char *str, size_t len, __int128_t *num, short *expo, int scientific) {
  int dot = 0;
  int sign = 1;
  int leading = 1;
  size_t strRunner = 0;

  *num = 0;
  *expo = -32767; // MIN_SHORT

  while (len - strRunner > 0 && *(str + strRunner) != '\0') {
    switch (*(str + strRunner)) {
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
      *num += *(str + strRunner) - '0';
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
      
      __int128_t sciNum;
      short sciExp;
      str2dec_internal(str + strRunner + 1, len - strRunner, &sciNum, &sciExp, 1);
      if (sciExp != 0) goto error; // exponent value cannot be float

      *expo -= sciNum;
      while (*expo < 0) {
        *num *= 10;
        *expo += 1;
      }
      goto end;
    default:
      return -1;
    }
    strRunner++;      // exponent value cannot be float
  }

end:
  while (*expo > 0 && *num % 10 == 0) {
    *num /= 10;
    *expo -= 1;
  }
  if (*expo < 0) *expo = 0;
  *num *= sign;
  return 0;

error:
  return -1;
}

int str2dec(const char *str, size_t len, __int128_t *num, short *expo) {
  return str2dec_internal(str, len ,num, expo, 0);
}

int dec2str(__int128_t num, short expo, char *str, int size) {
  // char str[40] = {0}; // log10(1 << 128) + '\0'
  int pos = size; //sizeof(str) - 1;
  // char *s = str + sizeof(str) - 1; // start at the end
  while (num != 0) {
    assert (pos > 0) ; // never happens

    str[--pos] = "0123456789"[num % 10]; // save last digit
    num /= 10;                     // drop it
  }

  int len = size - pos;
  if (expo > 0) {
    memmove(str, &str[pos], len - expo);
    str += expo;
  
  }
  memmove(&str[expo], &str[pos], size - pos);
}