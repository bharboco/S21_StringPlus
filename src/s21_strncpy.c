#include "s21_string.h"
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int flag_null = 0;
  if (dest == s21_NULL || n == 0) {
    flag_null = 1;
  }
  char *ptr = dest;  // создаем указатель на первый элемент массива char(ов)
  if (!flag_null) {
    while (*src && n--) {  // пока не конец строки
      *dest++ = *src++;  // добавляем пока число не ноль
    }
    *dest = '\0';  // добавляем в конец строки '\0'
  }
  return flag_null ? s21_NULL : ptr;
}