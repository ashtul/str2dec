#pragma once

#include <stddef.h>
#include <string.h>

int str2dec(const char *str, size_t len, __int128_t *num, short *expo);
int dec2str(__int128_t num, short expo, char *str, int size);