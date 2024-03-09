#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  const unsigned char* string = str;
  unsigned int q = c;
  int flag = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (string[i] == q) {
      flag = 1;
      string = string + i;
      break;
    }
  }
  return flag == 1 ? (void*)(string) : s21_NULL;
}
