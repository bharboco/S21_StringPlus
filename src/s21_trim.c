#include "s21_string.h"

int s21_flag_simbol(const char *trim_chars, char src) {
  int flag_null = 0;
  for (int i = 0; i < (int)s21_strlen(trim_chars); i++) {
    if (trim_chars[i] == src) flag_null = 1;
  }
  return flag_null ? 1 : 0;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int len_src = s21_strlen(src);
  int start_str = 0;
  int end_str = len_src - 1;
  while (src && s21_flag_simbol(trim_chars, src[start_str])) {
    start_str++;
  }
  while (s21_flag_simbol(trim_chars, src[end_str])) {
    end_str--;
  }
  char *result = (char *)malloc((end_str - start_str + 1) * sizeof(char));
  s21_strncpy(result, src + start_str, end_str - start_str + 1);
  result[end_str - start_str + 1] = '\0';

  return src == s21_NULL ? s21_NULL : (void *)result;
}
