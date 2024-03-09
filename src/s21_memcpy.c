#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src,
                 s21_size_t n) {  // копирует из src в dest на n символов
  /*  check comment
      unsigned char dest; // указатель на массив в который будут скопированы
     данные unsigned char src; // указатель на массив источник копируемых данных
      n – количество байт для копирования */
  char *cdest = (char *)dest;
  const char *csrc = (char *)src;
  for (s21_size_t i = 0; i < n; ++i) *cdest++ = *csrc++;

  return dest;
}