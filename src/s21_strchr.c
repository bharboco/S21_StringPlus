#include "s21_string.h"
char *s21_strchr(const char *str, int c) {
  int flag_null = 0;
  if (str == s21_NULL) flag_null = 1;
  do {
    if (*str == c) break;
  } while (*str++);
  return flag_null ? s21_NULL : (char *)str;
}