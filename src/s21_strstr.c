#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = *needle == '\0' ? (char *)haystack : s21_NULL;
  while (*haystack != '\0') {
    const char *p1 = (const char *)haystack;
    const char *p2 = (const char *)needle;
    while (*p2 != '\0' && *p1 == *p2) {
      p1++;
      p2++;
    }
    if (*p2 == '\0') {
      result = (char *)haystack;
      break;
    }
    haystack++;
  }
  return result;
}