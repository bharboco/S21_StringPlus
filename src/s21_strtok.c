#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last;
  int ch = 0, flag = 0;
  if (str == 0) str = last;
  do {
    if ((ch = *str++) == '\0') {
      flag = 1;
      break;
    }
  } while (s21_strchr(delim, ch));
  --str;
  last = str + s21_strcspn(str, delim);
  if (*last != 0) *last++ = 0;
  return flag ? 0 : str;
}