#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *p1 = str1;
  int flag = 0;
  s21_size_t count = 0;
  while (*p1 != '\0') {
    const char *p2 = str2;
    while (*p2 != '\0') {
      if (*p1 == *p2) {
        flag = 1;
        break;
      }
      p2++;
    }
    if (flag) break;
    p1++;
    count++;  // если не было совпадений возврат
  }
  return count;
}