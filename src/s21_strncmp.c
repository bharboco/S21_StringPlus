#include "s21_string.h"

int s21_strncmp(const char *s1, const char *s2, s21_size_t n) {
  const char *p1 = s1, *p2 = s2;
  int flag = 0;

  for (s21_size_t i = 0; i < n; i++) {
    if (*(p1 + i) != *(p2 + i)) {
      flag = ((*(p1 + i) < *(p2 + i))) ? -1 : 1;
      break;
    }
  }
  return flag;
}