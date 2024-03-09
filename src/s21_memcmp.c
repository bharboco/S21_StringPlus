#include "s21_string.h"
int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *p1 = s1, *p2 = s2;
  int flag = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (*(p1 + i) != *(p2 + i)) {
      flag = ((*(p1 + i) < *(p2 + i))) ? -1 : 1;
      break;
    }
  }
  return flag;
}