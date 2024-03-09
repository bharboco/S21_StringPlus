#ifndef STRING_H_
#define STRING_H_

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUF 10000
#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;

typedef struct spec {
  int c;
  int d;
  int f;
  int s;
  int u;
  int h;
  int l;
  int alig;  // значение цифр после минуса
  int plus;
  int minus;
  int space;
  int shirina;  // значение цифр после пробела
  int point;
  long int accuracy;  // значение цифр после точки
  int BD;             // Boulevard Depo - otricala
  // BD: f: if (f < 0)
  int BD_d;       // d: if (d < 0 && spec->plus)
  int BD_d2;      // d: if (d < 0 && spec->point)
  int BD_f;       // f: if (f < 0 && spec->plus)
  int BD_f_plus;  // f: if (spec->plus && f >= 0)
  int f_int;      // если double целое число
  int sm;         // f: if (f < 0 && spec->minus)
  int zero_acc;  // счетчик добавленных нулей при spec->point
  int zero_acc_u;  // счетчик добавленных нулей при spec->point для u
  short int s_i;            // d: short int
  long int l_i;             // d: long int
  wchar_t wc;               // c: width char
  unsigned short int us_i;  // u: Unsigned Short Int
  unsigned long int ul_i;   // u: Unsigned Long Int
  int flag_for_plus;        // d: if (spec->point && spec->plus)
  int flag_for_plus_f;      // f: if (spec->plus)
  int flag_for_plus_f2;     // f: флаг добавления '+'
} Specifiers;

typedef struct err {
  int exit;
  int plus_space;
  int plus_c;
  int plus_s;
  int plus_u;
  int space_c;
  int space_s;
  int space_u;
} Errors;

// 15 functions
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

// sprintf
int s21_sprintf(char *str, const char *format, ...);
void s21_reading_error(const char *format, Specifiers *spec, Errors *err);
void s21_print_errors(Errors *err);
void s21_read_str(char *str, const char *format, va_list args,
                  Specifiers *spec);
// спецификаторы
void s21_spec_d(va_list args, Specifiers *spec, char *str, int flag);
void s21_init_d(va_list args, Specifiers *spec, int *above_zero, char *temp);
void s21_spec_c(va_list args, Specifiers *spec, char *str);
void s21_spec_s(va_list args, Specifiers *spec, char *str, int flag);
void s21_spec_u(va_list args, Specifiers *spec, char *str, int flag);
void s21_spec_f(va_list args, Specifiers *spec, char *str, int flag);
// parsers
const char *s21_parser_flags_error(Specifiers *spec, const char *format,
                                   Errors *err);
const char *s21_parser_spec(
    Specifiers *spec,
    const char *format);  // для спецификаторов: d, c, s, u, f
const char *s21_parser_flags(
    Specifiers *spec,
    const char *format);  // для флагов: '+', ' ', '-', '.'
const char *s21_parser_length(Specifiers *spec,
                              const char *format);  // для длины: h, l
// преобразование
void s21_int_for_float2_to_string(
    long int n,
    char *str);  // преобразование дробной части float в string, без '-'
void s21_int_to_string(long int v, char *str,
                       Specifiers *spec);  // преобразование int в string
void s21_unsigned_int_to_string(
    unsigned long int value,
    char *str);  // преобразование unsigned int в string
char *s21_float_to_string(double f,
                          Specifiers *spec);  // преобразование float в string
void s21_reverse(char *temp_int);  // переворот строки
// ширина и выравнивание
const char *s21_alignment(const char *format,
                          Specifiers *spec);  // получение числа после '-'
const char *s21_get_width(const char *format,
                          Specifiers *spec);  // получение числа ширины
const char *s21_get_point(const char *format,
                          Specifiers *spec);  // получение числа после '.'
// добавление символов
int s21_putchar_to_str(const char c, char *str);  // добавление символа в строку
void s21_space_width(char *temp, char *str, Specifiers *spec,
                     int *flag);  // добавление ' ' в строку при spec->shirina
void s21_space_minus(char *temp, char *str, Specifiers *spec,
                     int *flag);  // добавление ' ' в строку при spec->minus
void s21_add_space(Specifiers *spec, char *str,
                   int *flag);  // добавление ' ' в строку при spec->space

// Допки
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int s21_flag_simbol(const char *trim_chars, char src);

#endif  // STRING_H_