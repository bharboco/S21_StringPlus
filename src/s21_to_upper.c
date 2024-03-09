#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *our_str1 = s21_NULL;
  if (str) {
    our_str1 = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
  }
  if (our_str1) {
    s21_strncpy(our_str1, str, s21_strlen(str) + 1);
    for (char *i = our_str1; *i; i++) {
      if (*i >= 'a' && *i <= 'z') {
        *i -= 32;
      }
    }
  }
  return (void *)our_str1;
}