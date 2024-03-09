#include <string.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  Specifiers spec = {0};
  Errors err = {0};
  *str = 0;
  va_list args;  // для обработки других аргументов вместо "..."
  int result = 0;
  if (str == s21_NULL)
    result = -1;
  else {
    va_start(args, format);  // инициализируем va_list для работы с аргументами
    s21_reading_error(format, &spec, &err);
    if (err.exit) {
      s21_print_errors(&err);
      return 1;
    }
    s21_read_str(str, format, args, &spec);
    result = s21_strlen(str);  //
    va_end(args);  // завершаем работу с аргументами
  }
  return result;
}
void s21_read_str(char *str, const char *format, va_list args,
                  Specifiers *spec) {
  int flag = 0;  // флаг добавления ' ' при spec->space
  while (*format != '\0') {
    if (*format != '%') {
      s21_putchar_to_str(*format, str);
    } else if (*format == '%') {
      // format = [function] - это перемещение указателя, если прошли условия
      // функции
      format = s21_parser_flags(spec, format);
      if (spec->minus) {
        format = s21_alignment(format, spec);
      } else {
        format = s21_get_width(format, spec);
      }
      if (*format == '.') {
        format++;
        spec->point = 1;
        format = s21_get_point(format, spec);
      }
      format = s21_parser_length(spec, format);
      format = s21_parser_spec(spec, format);
      if (spec->d) s21_spec_d(args, spec, str, flag);
      if (spec->c) s21_spec_c(args, spec, str);
      if (spec->s) s21_spec_s(args, spec, str, flag);
      if (spec->u) s21_spec_u(args, spec, str, flag);
      if (spec->f) s21_spec_f(args, spec, str, flag);
    }
    format++;
  }
}
void s21_reading_error(const char *format, Specifiers *spec, Errors *err) {
  while (*format != '\0') {
    if (*format == '%') {
      s21_parser_flags_error(spec, format, err);
    }
    format++;
  }
}
void s21_print_errors(Errors *err) {
  if (err->plus_space) {
    char plus_space[BUF] =
        "error: ' ' flag ignored with '+' flag in gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->plus_c) {
    char plus_space[BUF] = "error: '+' flag used with '%c' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->plus_s) {
    char plus_space[BUF] = "error: '+' flag used with '%s' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->plus_u) {
    char plus_space[BUF] = "error: '+' flag used with '%u' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->space_c) {
    char plus_space[BUF] = "error: ' ' flag used with '%c' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->space_s) {
    char plus_space[BUF] = "error: ' ' flag used with '%s' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->space_u) {
    char plus_space[BUF] = "error: ' ' flag used with '%u' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  printf("FIX ANY ERROR(S) TO CONTINUE\r");
  s21_memset(err, 0, sizeof(Errors));
}
void s21_spec_d(va_list args, Specifiers *spec, char *str, int flag) {
  char temp[BUF] = {'\0'};
  int above_zero = 0;  // флаг, если число больше 0
  s21_init_d(args, spec, &above_zero, temp);
  if (spec->point) {
    if (spec->plus) spec->flag_for_plus = 1;
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp); i++) {
      spec->zero_acc++;  // счетчик добавленных нулей при точности
    }
  }
  if (spec->space && above_zero) s21_add_space(spec, str, &flag);
  s21_space_width(temp, str, spec, &flag);
  if (spec->point) {
    if (spec->plus &&
        !spec->BD_d) {  // добавление '+', если положительное число
      s21_putchar_to_str('+', str);
      spec->plus = 0;
    }
    if (spec->BD_d2) {
      s21_putchar_to_str('-', str);
    }
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp);
         i++) {  // добавление '0', если точность
      s21_putchar_to_str('0', str);
    }
    spec->accuracy = 0, spec->point = 0;
  }
  s21_strncat(str, temp, BUF);
  s21_space_minus(temp, str, spec, &flag);
  spec->zero_acc = 0, spec->flag_for_plus = 0, spec->plus = 0;
  spec->d = 0, spec->BD_d = 0, spec->space = 0, above_zero = 0, spec->BD_d2 = 0;
}
void s21_spec_c(va_list args, Specifiers *spec, char *str) {
  if (spec->shirina) {
    for (int i = 0; i < spec->shirina - 1; i++) {  // space_width
      s21_putchar_to_str(' ', str);
    }
    spec->shirina = 0;
  }
  if (spec->l) {
    spec->wc = va_arg(args, wchar_t);
    s21_putchar_to_str(spec->wc, str);
    spec->l = 0;
  } else {
    char c = va_arg(args, int);
    s21_putchar_to_str(c, str);
  }
  if (spec->minus) {                            // space_minus
    for (int i = 0; i < spec->alig - 1; i++) {  // -1: strlen(c)
      s21_putchar_to_str(' ', str);
    }
    spec->minus = 0, spec->alig = 0;
  }
  spec->c = 0;
}
void s21_spec_s(va_list args, Specifiers *spec, char *str, int flag) {
  char *s = va_arg(args, char *);
  if (spec->point) {
    for (int i = spec->accuracy; i < (int)s21_strlen(s) && s[i] != '\0'; i++) {
      s[i] = '\0';
    }
    spec->point = 0, spec->accuracy = 0;
  }
  s21_space_width(s, str, spec, &flag);
  s21_strncat(str, s, BUF);
  s21_space_minus(s, str, spec, &flag);
  spec->s = 0;
}
void s21_spec_u(va_list args, Specifiers *spec, char *str, int flag) {
  char temp[BUF] = {'\0'};
  if (spec->h) {
    spec->us_i = va_arg(args, int);
    s21_unsigned_int_to_string(spec->us_i, temp);
    spec->h = 0;
  } else if (spec->l) {
    spec->ul_i = va_arg(args, long);
    s21_unsigned_int_to_string(spec->ul_i, temp);
    spec->l = 0;
  } else {
    unsigned int d = va_arg(args, int);
    s21_unsigned_int_to_string(d, temp);
  }
  if (spec->point) {
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp); i++) {
      spec->zero_acc_u++;  // счетчик добавленных нулей при точности
    }
  }
  s21_space_width(temp, str, spec, &flag);
  if (spec->point) {  // можно сделать функцию
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp); i++) {
      s21_putchar_to_str('0', str);
    }
    spec->accuracy = 0, spec->point = 0;
  }
  s21_strncat(str, temp, BUF);
  s21_space_minus(temp, str, spec, &flag);
  spec->u = 0, spec->zero_acc_u = 0;
}
void s21_spec_f(va_list args, Specifiers *spec, char *str, int flag) {
  int sp = 0;
  double f = va_arg(args, double);
  if ((f < 0 && spec->plus)) spec->BD_d = 1, spec->BD_f = 1;
  if (f < 0 && spec->space) sp = 1;
  if (f < 0 && spec->minus) spec->sm = 1;
  if (spec->point) {
    for (int i = 0; i < spec->accuracy; i++) f = f * 10.0;
    f = round(f);
    for (int i = 0; i < spec->accuracy; i++) f = f / 10.0;
  }
  if (spec->plus && f >= 0) spec->BD_f_plus = 1;

  char *temp = s21_float_to_string(f, spec);
  if (spec->point) spec->point = 0, spec->accuracy = 0;
  if (f >= 0 && !spec->BD_f_plus && !spec->BD_f && !sp)
    s21_add_space(spec, str, &flag);

  s21_space_width(temp, str, spec, &flag);
  s21_strncat(str, temp, BUF);
  s21_space_minus(temp, str, spec, &flag);
  spec->f = 0, spec->BD_d = 0, spec->plus = 0, spec->BD_f = 0,
  spec->BD_f_plus = 0, spec->flag_for_plus_f = 0, spec->flag_for_plus_f2 = 0,
  spec->shirina = 0, sp = 0, spec->sm = 0;
}
const char *s21_parser_flags(Specifiers *spec,
                             const char *format) {  // + - space
  format++;
  char speci[100] = "1234567890\0";
  // считывание от '%' до любой цифры
  for (s21_size_t i = 0; i < s21_strcspn(format, speci) + 1; i++) {
    switch (*format) {
      case '+':
        spec->plus = 1;
        format++;
        break;
      case '-':
        spec->minus = 1;
        format++;
        break;
      case ' ':
        spec->space = 1;
        format++;
        break;
    }
  }
  return format;
}
const char *s21_parser_length(Specifiers *spec, const char *format) {
  char speci[100] = "cdsuf\0";
  // считывание флагов h и l до любого спецификатора
  for (s21_size_t i = 0; i < s21_strcspn(format, speci); i++) {
    switch (*format) {
      case 'h':
        spec->h = 1;
        format++;
        break;
      case 'l':
        spec->l = 1;
        format++;
        break;
    }
  }
  return format;
}
const char *s21_parser_spec(Specifiers *spec,
                            const char *format) {  // c d s u f
  for (int i = 0; i < 1; i++) {
    switch (*format) {
      case 'c':
        spec->c = 1;
        break;
      case 'd':
        spec->d = 1;
        break;
      case 's':
        spec->s = 1;
        break;
      case 'u':
        spec->u = 1;
        break;
      case 'f':
        spec->f = 1;
        break;
    }
  }
  return format;
}
const char *s21_parser_flags_error(Specifiers *spec, const char *format,
                                   Errors *err) {  // + - space
  format = s21_parser_flags(spec, format);
  if (spec->minus) {
    format = s21_alignment(format, spec);
  } else {
    format = s21_get_width(format, spec);
  }
  if (*format == '.') {
    format++;
    spec->point = 1;
    format = s21_get_point(format, spec);
  }
  format = s21_parser_length(spec, format);
  format = s21_parser_spec(spec, format);
  if (spec->space && spec->plus) err->plus_space = 1, err->exit = 1;
  if (spec->plus && spec->c) err->plus_c = 1, err->exit = 1;
  if (spec->plus && spec->s) err->plus_s = 1, err->exit = 1;
  if (spec->plus && spec->u) err->plus_u = 1, err->exit = 1;
  if (spec->space && spec->c) err->space_c = 1, err->exit = 1;
  if (spec->space && spec->s) err->space_s = 1, err->exit = 1;
  if (spec->space && spec->u) err->space_u = 1, err->exit = 1;

  s21_memset(spec, 0, sizeof(Specifiers));
  return format;
}
void s21_space_width(char *temp, char *str, Specifiers *spec, int *flag) {
  if (spec->shirina) {
    for (int i = 0;
         i < spec->shirina - (int)s21_strlen(temp) - *flag - spec->zero_acc -
                 spec->zero_acc_u - spec->flag_for_plus + spec->BD_d -
                 spec->BD_f - spec->BD_d2;
         i++) {
      s21_putchar_to_str(' ', str);
    }
    if (!spec->minus) *flag = 0;
    spec->shirina = 0;
  }
}
void s21_space_minus(char *temp, char *str, Specifiers *spec, int *flag) {
  if (spec->minus) {
    if (spec->s || spec->u) {
      for (int i = 0; i < spec->alig - (int)s21_strlen(temp) - spec->zero_acc_u;
           i++) {
        s21_putchar_to_str(' ', str);
      }
    } else {
      for (int i = 0;
           i < spec->alig - *flag - (int)s21_strlen(temp) - spec->zero_acc -
                   spec->BD_f - spec->BD_f_plus + spec->flag_for_plus_f2 -
                   spec->flag_for_plus - spec->BD_d2;
           i++) {
        s21_putchar_to_str(' ', str);
      }
    }
    spec->minus = 0, spec->alig = 0, *flag = 0;
  }
}
void s21_add_space(Specifiers *spec, char *str, int *flag) {
  if (spec->space) {
    s21_putchar_to_str(' ', str);
    *flag = 1;
  }
  spec->space = 0;
}
const char *s21_get_width(const char *format, Specifiers *spec) {
  char speci[100] = ".cdsufhl\0";
  // взятие числа при ширине
  int j = (int)s21_strcspn(format, speci);
  for (int i = 0; i < j; i++) {
    if (j == 1) {                    // для одной цифры
      spec->shirina = *format - 48;  // 1: 49 - 48 = 1; по ascii таблице
    } else {                         // для более одной
      spec->shirina = spec->shirina * 10 + (*format - 48);
      // 12: 1 * 10 = 10; 10 + 2 = 12
    }
    format++;
  }
  return format;
}
const char *s21_alignment(const char *format, Specifiers *spec) {
  char speci[100] = ".cdsufhl\0";
  // взятие числа при минусе
  int j = (int)s21_strcspn(format, speci);
  for (int i = 0; i < j; i++) {
    if (j == 1) {
      spec->alig = *format - 48;
    } else {
      spec->alig = spec->alig * 10 + (*format - 48);
    }
    format++;
  }
  return format;
}
const char *s21_get_point(const char *format, Specifiers *spec) {
  char speci[100] = "cdsufhl\0";
  // взятие точности
  int j = (int)s21_strcspn(format, speci);
  for (int i = 0; i < j; i++) {
    if (j == 1) {
      spec->accuracy = *format - 48;
    } else {
      spec->accuracy = spec->accuracy * 10 + (*format - 48);
    }
    format++;
  }
  return format;
}
int s21_putchar_to_str(const char c, char *str) {
  while (*str) {
    str++;
  }          // доходим до конца строки
  *str = c;  // приравниваем указатель к символу
  str++;
  *str = '\0';
  return 1;
}
void s21_reverse(char *s) {
  int i, j;
  char c;
  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
void s21_int_to_string(long int v, char *str, Specifiers *spec) {
  long int i = 0, is_negative = 0;
  if (v < 0) {
    is_negative = 1;  // флаг негативного числа
    v = -v;  // превращение числа в положительное
  }
  do {
    str[i++] = v % 10 + '0';
    v /= 10;
  } while (v > 0);
  if (!is_negative && spec->plus && !spec->point) {
    if (v >= 0) {
      str[i++] = '+';
      spec->plus = 0;
    }
  }
  if (spec->plus && spec->flag_for_plus_f && !spec->BD_d) {
    str[i++] = '+';
    spec->plus = 0, spec->flag_for_plus_f2 = 1;
  }
  if (!spec->BD_d2) {
    if ((is_negative || spec->BD || spec->BD_f)) {
      str[i++] = '-';
      is_negative = 0, spec->BD = 0, spec->BD_f = 0;
    }
  }
  str[i] = '\0';
  s21_reverse(str);
}
void s21_unsigned_int_to_string(unsigned long int value, char *str) {
  int i = 0;
  do {
    str[i++] = value % 10 + '0';
    value /= 10;
  } while (value > 0);
  str[i] = '\0';
  s21_reverse(str);
}
char *s21_float_to_string(double f, Specifiers *spec) {
  char *result = {'\0'};
  if (f < 0) {
    spec->BD = 1;
  }
  if (spec->point && !spec->accuracy) {
    int f2 = f - floor(f);
    // floor: округляют аргумент x до наибольшего целого числа, которое меньше
    // или равно аргументу
    if (f2 == 0) {
      spec->f_int = 1;
    }
  }
  int int_part = (int)f;             // число до точки
  double fract_part = f - int_part;  // дробная часть числа
  char temp_int[BUF] = {'\0'};
  if (spec->plus) {
    spec->flag_for_plus_f = 1;
  }
  s21_int_to_string(int_part, temp_int, spec);
  result = s21_strncat(temp_int, "\0", BUF);
  // преобразование инт в стринг до точки
  if (!spec->f_int)
    result = s21_strncat(temp_int, ".\0", BUF);  // добавление точки в строку
  if (spec->point) {
    fract_part = round(fract_part * pow(10, spec->accuracy));
  } else {
    fract_part = round(fract_part * 1000000);  // округление
  }
  char temp_fract[BUF] = {'\0'};
  if (fract_part != 0.0) {
    s21_int_for_float2_to_string(fract_part, temp_fract);
    // преобразование дробной части в строку
  }
  if (!spec->accuracy &&
      !spec->point) {  // если нет точности, то она по умолчанию равна 6
    spec->accuracy = 6;
  }
  long int fp2 = fract_part, z = 0;
  while (fp2 != 0) {
    fp2 = fp2 / 10;
    z++;  // длина дробной части
  }
  for (int i = 0; i < spec->accuracy - z; i++) {
    s21_putchar_to_str('0', result);
  }
  result = s21_strncat(result, temp_fract, BUF);
  spec->f_int = 0;
  // соединение двух строк в одну результирующую
  return result;
}
void s21_int_for_float2_to_string(long int n, char *str) {
  // для дробной части, чтобы не принтил '-'
  int i = 0;
  if (n < 0) n = -n;
  do {
    str[i++] = n % 10 + '0';
    n /= 10;
  } while (n > 0);
  str[i] = '\0';
  s21_reverse(str);
}
void s21_init_d(va_list args, Specifiers *spec, int *above_zero, char *temp) {
  if (spec->h) {
    spec->s_i = va_arg(args, int);
    if (spec->s_i < 0 && spec->plus) spec->BD_d = 1;
    if (spec->s_i > 0) *above_zero = 1;
    if (spec->s_i < 0 && spec->point) spec->BD_d2 = 1;
    s21_int_to_string(spec->s_i, temp, spec);
    spec->h = 0;
  } else if (spec->l) {
    spec->l_i = va_arg(args, long);
    if (spec->l_i < 0 && spec->plus) spec->BD_d = 1;
    if (spec->l_i > 0) *above_zero = 1;
    if (spec->l_i < 0 && spec->point) spec->BD_d2 = 1;
    s21_int_to_string(spec->l_i, temp, spec);
    spec->l = 0;
  } else {
    int d = va_arg(args, int);
    if (d < 0 && spec->plus) spec->BD_d = 1;
    if (d > 0) *above_zero = 1;
    if (d < 0 && spec->point) spec->BD_d2 = 1;
    s21_int_to_string(d, temp, spec);
  }
}