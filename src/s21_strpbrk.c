#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *p1 = (const char *)str1;
  int flag = 0;
  while (*p1 != '\0') {
    const char *p2 = (const char *)str2;
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        flag = 1;
        break;
      }
      p2++;
    }
    if (flag) break;
    p1++;
  }
  return flag ? (char *)p1 : s21_NULL;
}