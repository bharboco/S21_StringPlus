#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int flag_null = 0;
  char *result = {'\0'};
  if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src) ||
      0 >= start_index) {
    flag_null = 1;
  }
  if (!flag_null) {
    int src_len = s21_strlen(src);
    int str_len = s21_strlen(str);
    int index = start_index;
    int end_src_len = src_len - index;
    result = (char *)malloc((src_len + str_len + 1) * sizeof(char));

    int i;
    for (i = 0; i < index && src[i] != '\0'; i++) {
      result[i] = src[i];
    }
    result[i] = '\0';
    s21_strncat(result, str, str_len);
    s21_strncat(result, src + index, end_src_len);
  }
  return flag_null ? s21_NULL : result;
}