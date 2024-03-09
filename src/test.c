#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_memchr_test) {
  char test_1[] = "123456";
  char test_2 = '3';
  char test_3 = '7';
  char test_4[] = "Hello World";
  char test_5[] = "d";
  char test_6 = ' ';
  char test_7 = 'd';
  char test_8 = 'W';
  char test_9 = 'l';
  ck_assert_uint_eq((unsigned long)s21_memchr(test_1, test_2, 6),
                    (unsigned long)memchr(test_1, test_2, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_1, test_3, 6),
                    (unsigned long)memchr(test_1, test_3, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_6, 11),
                    (unsigned long)memchr(test_4, test_6, 11));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_5, test_6, 1),
                    (unsigned long)memchr(test_5, test_6, 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_7, 11),
                    (unsigned long)memchr(test_4, test_7, 11));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_8, 11),
                    (unsigned long)memchr(test_4, test_8, 11));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_9, 11),
                    (unsigned long)memchr(test_4, test_9, 11));
}
END_TEST

START_TEST(s21_memcmp_test) {
  char test_1[] = "Hello World";
  char test_2[] = "World Hello";
  char test_3[] = "bob";
  char test_4[] = "Hello";
  char test_5[] = "Hello";
  ck_assert_uint_eq(s21_memcmp(test_1, test_2, 11) < 0,
                    memcmp(test_1, test_2, 11) < 0);
  ck_assert_uint_eq(s21_memcmp(test_1, test_3, 3) > 0,
                    memcmp(test_1, test_3, 3) > 0);
  ck_assert_uint_eq(s21_memcmp(test_2, test_3, 3) > 0,
                    memcmp(test_2, test_3, 3) > 0);
  ck_assert_uint_eq(s21_memcmp(test_4, test_2, 5) > 0,
                    memcmp(test_4, test_2, 5) > 0);
  ck_assert_uint_eq(s21_memcmp(test_4, test_5, 5) == 0,
                    memcmp(test_4, test_5, 5) == 0);
}
END_TEST

START_TEST(s21_memcpy_test) {
  char test_1[] = "123456";
  char test_2[] = "  ";
  char test_3[] = "111   ";
  char test_4[] = "   111";
  char test_5[] = "qwerty";
  char test_6[] = "\0";
  ck_assert_str_eq(s21_memcpy(test_1, test_2, 2), memcpy(test_1, test_2, 2));
  ck_assert_str_eq(s21_memcpy(test_3, test_4, 6), memcpy(test_3, test_4, 6));
  ck_assert_str_eq(s21_memcpy(test_4, test_3, 3), memcpy(test_4, test_3, 3));
  ck_assert_str_eq(s21_memcpy(test_1, test_5, 6), memcpy(test_1, test_5, 6));
  ck_assert_str_eq(s21_memcpy(test_5, test_6, 1), memcpy(test_5, test_6, 1));
}
END_TEST

START_TEST(s21_memset_test) {
  unsigned char test_1[10] = "1234567890";
  unsigned char test_2[10] = "Hello";
  ck_assert_uint_eq((unsigned long)s21_memset(test_1, '6', 10),
                    (unsigned long)memset(test_1, '6', 10));
  ck_assert_uint_eq((unsigned long)s21_memset(test_1, '2', 10),
                    (unsigned long)memset(test_1, '2', 10));
  ck_assert_uint_eq((unsigned long)s21_memset(test_1, '0', 1),
                    (unsigned long)memset(test_1, '0', 1));
  ck_assert_uint_eq((unsigned long)s21_memset(test_1, '/', 6),
                    (unsigned long)memset(test_1, '/', 6));
  ck_assert_uint_eq((unsigned long)s21_memset(test_2, '4', 4),
                    (unsigned long)memset(test_2, '4', 4));
}
END_TEST

START_TEST(s21_strncat_test) {
  char test_2[4] = "<<<\0";
  char test_4[2] = "5\0";
  char test_44[2] = "5\0";
  char test_5[] = "\0";

  ck_assert_str_eq(s21_strncat(test_2, test_4, 1), "<<<5\0");
  ck_assert_str_eq(s21_strncat(test_44, test_5, 0), strncat(test_4, test_5, 0));
}
END_TEST

START_TEST(s21_strchr_test) {
  char str1[] = "Abcdefg";
  int symbol1 = 'd';
  char *ach1 = s21_strchr(str1, symbol1);
  ck_assert_str_eq(ach1, "defg");

  char str2[] = "Abcdefg";
  int symbol2 = 'd';
  char *ach2 = strchr(str2, symbol2);
  ck_assert_str_eq(ach1, ach2);
  ck_assert_str_eq(str1, str2);

  char str3[] = "Abcdefg";
  int symbol3 = '\0';
  char *ach3 = s21_strchr(str3, symbol3);

  char str4[] = "Abcdefg";
  int symbol4 = '\0';
  char *ach4 = strchr(str4, symbol4);
  ck_assert_str_eq(ach3, ach4);
  ck_assert_str_eq(str3, str4);
}
END_TEST

START_TEST(s21_strncmp_test) {
  char test1[] = "Hello World 1";
  char test2[] = "Hella Worda 2";
  ck_assert_int_eq(s21_strncmp(test1, test2, 13) < 0,
                   strncmp(test1, test2, 13) < 0);
  ck_assert_int_eq(s21_strncmp(test1, test2, 4) == 0,
                   strncmp(test1, test2, 4) == 0);
}
END_TEST

START_TEST(s21_strncpy_test) {
  char src[] = "\0";
  char res[] = "\0";
  char exp[] = "\0";
  s21_size_t n_byte = 0;

  s21_strncpy(res, src, n_byte);
  strncpy(exp, src, n_byte);

  ck_assert_str_eq(res, exp);

  char src1[] = "123\0";
  char res1[] = "123\0";
  char exp1[] = "123\0";
  s21_size_t n1_byte = 0;

  s21_strncpy(res1, src1, n1_byte);
  strncpy(exp1, src1, n1_byte);

  ck_assert_str_eq(res1, exp1);
}
END_TEST

START_TEST(s21_strcspn_test) {
  char test1[] = "12314241";
  char test2[] = "fffff";
  char test3[] = "//\0\n";
  char test4[] = "goga";
  char test5[] = "22222111111111";
  char test6[] = "22222111111111";
  ck_assert_uint_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_uint_eq(s21_strcspn(test2, test3), strcspn(test2, test3));
  ck_assert_uint_eq(s21_strcspn(test5, test4), strcspn(test5, test4));
  ck_assert_uint_eq(s21_strcspn(test5, test6), strcspn(test5, test6));
  ck_assert_uint_eq(s21_strcspn(test4, test3), strcspn(test4, test3));
}
END_TEST

START_TEST(s21_strerror_test) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(106), strerror(106));
  ck_assert_str_eq(s21_strerror(2147483647), strerror(2147483647));
  ck_assert_str_eq(s21_strerror(-214748364), strerror(-214748364));
}
END_TEST

START_TEST(s21_strlen_test) {
  char test1[] = "12312\0";
  char test2[] = "//\0\n\0";
  char test3[] = "dfdfd11\0";
  char test4[] = "    \0";
  char test5[] = "\0";
  char test6[] = "'f'f1213/v/f/////\0";
  ck_assert_int_eq(s21_strlen(test1), strlen(test1));
  ck_assert_int_eq(s21_strlen(test2), strlen(test2));
  ck_assert_int_eq(s21_strlen(test3), strlen(test3));
  ck_assert_int_eq(s21_strlen(test4), strlen(test4));
  ck_assert_int_eq(s21_strlen(test5), strlen(test5));
  ck_assert_int_eq(s21_strlen(test6), strlen(test6));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char test1[] = "01234ffffff";
  char test2[] = "7773";
  ck_assert_str_eq(s21_strpbrk(test1, test2), "34ffffff");
  ck_assert_str_eq(s21_strpbrk(test1, test2), strpbrk(test1, test2));

  char *str = "Hello, world";
  char *empty = "";
  ck_assert(s21_strpbrk(str, empty) == s21_NULL);
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty),
                    (unsigned long)strpbrk(str, empty));
}
END_TEST

START_TEST(s21_strrchr_test) {
  char test1[] = "0163456769";
  char test2[] = ";;;;;;H%%//#HH";
  char test3[] = "     /";
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, ' '),
                    (unsigned long)strrchr(test1, ' '));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '6'),
                    (unsigned long)strrchr(test1, '6'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, 'H'),
                    (unsigned long)strrchr(test2, 'H'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, '$'),
                    (unsigned long)strrchr(test2, '$'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, ';'),
                    (unsigned long)strrchr(test2, ';'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, ' '),
                    (unsigned long)strrchr(test3, ' '));
  ck_assert_str_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
}
END_TEST

START_TEST(s21_strstr_test) {
  char test_1[] = "<<<5>>>";
  char test_2[] = "5";
  char test_3[] = "QwertyQwertyQwerty";
  char test_4[] = "Qwerty";
  char test_5[] = "abcd";
  char test_6[] = "";
  char test_7[] = "aaaaa123aaa1234aaa";
  char test_8[] = "1234";

  ck_assert_ptr_eq(s21_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(s21_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(s21_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(s21_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(s21_strstr(test_7, test_8), strstr(test_7, test_8));
}
END_TEST

START_TEST(s21_strtok_test) {
  char str_strtok1[] = "one/two/three(four)five";
  char delim1[] = "/()";
  char str_strtok2[] = "one/two/three(four)five";
  char delim2[] = "/()";
  char *my_strtok = s21_strtok(str_strtok1, delim1);
  char *origin_strtok = strtok(str_strtok2, delim2);
  while (my_strtok != s21_NULL) {
    ck_assert_str_eq(my_strtok, origin_strtok);
    my_strtok = s21_strtok(s21_NULL, delim1);
    origin_strtok = strtok(s21_NULL, delim2);
  }
}
END_TEST

START_TEST(s21_to_lower_test) {
  char test1[] = "hElLo WoRLd";
  char test2[] = "DoG";
  char *new_str = s21_to_lower(test1);
  if (new_str) {
    ck_assert_str_eq(new_str, "hello world");
    free(new_str);
  }
  new_str = s21_to_lower(test2);
  if (new_str) {
    ck_assert_str_eq(new_str, "dog");
    free(new_str);
  }
}
END_TEST

START_TEST(s21_to_upper_test) {
  char test1[] = "hElLo WoRLd";
  char test2[] = "DoG";
  char *new_str = s21_to_upper(test1);
  if (new_str) {
    ck_assert_str_eq(new_str, "HELLO WORLD");
    free(new_str);
  }
  new_str = s21_to_upper(test2);
  if (new_str) {
    ck_assert_str_eq(new_str, "DOG");
    free(new_str);
  }
}
END_TEST

START_TEST(s21_insert_test) {
  char *src = "Hello!!";
  char *str = " World!";
  char *new_str = s21_insert(src, str, 5);
  if (new_str) {
    ck_assert_str_eq(new_str, "Hello World!!!");
    free(new_str);
  }
  new_str = s21_insert(src, "", 40);
  ck_assert(new_str == s21_NULL);
  new_str = s21_insert(src, str, -1);
  ck_assert(new_str == s21_NULL);
}
END_TEST

START_TEST(s21_trim_test) {
  char str_trim[] = "\n  ! Hello World ! ,, \n\0";
  char test1[] = "\n !\0";
  char test2[] = "\n !,Hd\0";
  char *str = s21_trim(str_trim, test1);
  if (str) {
    ck_assert_str_eq(str, "Hello World ! ,,\0");
    free(str);
  }
  str = s21_trim(str_trim, test2);
  if (str) {
    ck_assert_str_eq(str, "ello Worl\0");
    free(str);
  }
}
END_TEST

START_TEST(s21_sprintf_f_test) {
  char str[80] = {'\0'};
  char str_orig[80] = {'\0'};

  double b_1 = -1.0234;
  int res_1 = s21_sprintf(str, "% 5.1f", b_1);
  int res_1_orig = sprintf(str_orig, "% 5.1f", b_1);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  double b_2 = 0.02345;
  int res_2 = s21_sprintf(str, "%+-5.3f", b_2);
  int res_2_orig = sprintf(str_orig, "%+-5.3f", b_2);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  double b_3 = 13.04;
  int res_3 = s21_sprintf(str, "%15.5f", b_3);
  int res_3_orig = sprintf(str_orig, "%15.5f", b_3);
  ;
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  double b_4 = 5.6;
  int res_4 = s21_sprintf(str, "%+3.5f", b_4);
  int res_4_orig = sprintf(str_orig, "%+3.5f", b_4);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  double b_5 = 9.6;
  int res_5 = s21_sprintf(str, "%-3.5f", b_5);
  int res_5_orig = sprintf(str_orig, "%-3.5f", b_5);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_d_test) {
  char str[80] = {'\0'};
  char str_orig[80] = {'\0'};
  int d = 228;

  int res_1 = s21_sprintf(str, "%10.5d", d);
  int res_1_orig = sprintf(str_orig, "%10.5d", d);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5d", d);
  int res_2_orig = sprintf(str_orig, "% 10.5d", d);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5d", d);
  int res_3_orig = sprintf(str_orig, "%3.5d", d);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%d", d);
  int res_4_orig = sprintf(str_orig, "%d", d);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%0d", d);
  int res_5_orig = sprintf(str_orig, "%0d", d);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-d", d);
  int res_6_orig = sprintf(str_orig, "%-d", d);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+d", d);
  int res_7_orig = sprintf(str_orig, "%+d", d);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% d", d);
  int res_8_orig = sprintf(str_orig, "% d", d);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5d", d);
  int res_9_orig = sprintf(str_orig, "%5d", d);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%-5d", d);
  int res_10_orig = sprintf(str_orig, "%-5d", d);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%+5d", d);
  int res_11_orig = sprintf(str_orig, "%+5d", d);
  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "% 5d", d);
  int res_12_orig = sprintf(str_orig, "% 5d", d);
  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%.5d", d);
  int res_13_orig = sprintf(str_orig, "%.5d", d);
  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_c_test) {
  char str[80] = {'\0'};
  char str_orig[80] = {'\0'};
  char A = 'A';

  int res_1 = s21_sprintf(str, "%c", A);
  int res_1_orig = sprintf(str_orig, "%c", A);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%-c", A);
  int res_2_orig = sprintf(str_orig, "%-c", A);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%10c", A);
  int res_4_orig = sprintf(str_orig, "%10c", A);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%-2c", A);
  int res_5_orig = sprintf(str_orig, "%-2c", A);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_s_test) {
  char str[80] = {'\0'};
  char str_orig[80] = {'\0'};
  char *A = "Ochko";

  int res_1 = s21_sprintf(str, "%s", A);
  int res_1_orig = sprintf(str_orig, "%s", A);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%-s", A);
  int res_2_orig = sprintf(str_orig, "%-s", A);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%10s", A);
  int res_4_orig = sprintf(str_orig, "%10s", A);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_5 = s21_sprintf(str, "%.5s", A);
  int res_5_orig = sprintf(str_orig, "%.5s", A);
  ck_assert_int_eq(res_5, res_5_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-10s", A);
  int res_6_orig = sprintf(str_orig, "%-10s", A);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_ld_test) {
  char str[80] = {'\0'};
  char str_orig[80] = {'\0'};
  long int d = 1504389565748;

  int res_1 = s21_sprintf(str, "%10.5ld", d);
  int res_1_orig = sprintf(str_orig, "%10.5ld", d);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "% 10.5ld", d);
  int res_2_orig = sprintf(str_orig, "% 10.5ld", d);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5ld", d);
  int res_3_orig = sprintf(str_orig, "%3.5ld", d);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%ld", d);
  int res_4_orig = sprintf(str_orig, "%ld", d);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%-ld", d);
  int res_6_orig = sprintf(str_orig, "%-ld", d);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_7 = s21_sprintf(str, "%+ld", d);
  int res_7_orig = sprintf(str_orig, "%+ld", d);
  ck_assert_int_eq(res_7, res_7_orig);
  ck_assert_str_eq(str, str_orig);

  int res_8 = s21_sprintf(str, "% ld", d);
  int res_8_orig = sprintf(str_orig, "% ld", d);
  ck_assert_int_eq(res_8, res_8_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5ld", d);
  int res_9_orig = sprintf(str_orig, "%5ld", d);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%-5ld", d);
  int res_10_orig = sprintf(str_orig, "%-5ld", d);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_11 = s21_sprintf(str, "%+5ld", d);
  int res_11_orig = sprintf(str_orig, "%+5ld", d);
  ck_assert_int_eq(res_11, res_11_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "% 5ld", d);
  int res_12_orig = sprintf(str_orig, "% 5ld", d);
  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%.5ld", d);
  int res_13_orig = sprintf(str_orig, "%.5ld", d);
  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_u_test) {
  char str[80] = {'\0'};
  char str_orig[80] = {'\0'};
  unsigned int u = 228;

  int res_1 = s21_sprintf(str, "%10.5u", u);
  int res_1_orig = sprintf(str_orig, "%10.5u", u);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);

  int res_2 = s21_sprintf(str, "%-10.5u", u);
  int res_2_orig = sprintf(str_orig, "%-10.5u", u);
  ck_assert_int_eq(res_2, res_2_orig);
  ck_assert_str_eq(str, str_orig);

  int res_3 = s21_sprintf(str, "%3.5u", u);
  int res_3_orig = sprintf(str_orig, "%3.5u", u);
  ck_assert_int_eq(res_3, res_3_orig);
  ck_assert_str_eq(str, str_orig);

  int res_4 = s21_sprintf(str, "%u", u);
  int res_4_orig = sprintf(str_orig, "%u", u);
  ck_assert_int_eq(res_4, res_4_orig);
  ck_assert_str_eq(str, str_orig);

  int res_6 = s21_sprintf(str, "%u", u);
  int res_6_orig = sprintf(str_orig, "%u", u);
  ck_assert_int_eq(res_6, res_6_orig);
  ck_assert_str_eq(str, str_orig);

  int res_9 = s21_sprintf(str, "%5u", u);
  int res_9_orig = sprintf(str_orig, "%5u", u);
  ck_assert_int_eq(res_9, res_9_orig);
  ck_assert_str_eq(str, str_orig);

  int res_10 = s21_sprintf(str, "%-5u", u);
  int res_10_orig = sprintf(str_orig, "%-5u", u);
  ck_assert_int_eq(res_10, res_10_orig);
  ck_assert_str_eq(str, str_orig);

  int res_12 = s21_sprintf(str, "%10.5u", u);
  int res_12_orig = sprintf(str_orig, "%10.5u", u);
  ck_assert_int_eq(res_12, res_12_orig);
  ck_assert_str_eq(str, str_orig);

  int res_13 = s21_sprintf(str, "%.5u", u);
  int res_13_orig = sprintf(str_orig, "%.5u", u);
  ck_assert_int_eq(res_13, res_13_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

START_TEST(s21_sprintf_ULTIMA_test) {
  char str[200] = {'\0'};
  char str_orig[200] = {'\0'};
  char s[] = "chfbjkds\0";
  char s2[] = "qwerty\0";
  short int d = 19555;
  long int d2 = 1504389565748;
  int d3 = -190;
  unsigned short int us = 10443;
  unsigned long int ul = 5665465454;
  char c = 'A';
  float f = 1.0004;
  float f2 = -228;
  float f3 = 1.0;
  const char format[BUF] =
      "1234 x %+-5.3hd x %+-20.15ld x % 10.6d x %-5s x %-10.3s x %-5.7hu x "
      "%-10.2lu x %-5lc x %c x % -5.2f x %10.5f x %.f x %10f";
  int res_1 =
      s21_sprintf(str, format, d, d2, d3, s, s2, us, ul, c, c, f, f2, f3, f3);
  int res_1_orig =
      sprintf(str_orig, format, d, d2, d3, s, s2, us, ul, c, c, f, f2, f3, f3);
  ck_assert_int_eq(res_1, res_1_orig);
  ck_assert_str_eq(str, str_orig);
}
END_TEST

int main() {
  Suite *s1 = suite_create(
      "s21_string");  // создаем набор тестов s1 с названием  s21_string
  TCase *tc1_1 = tcase_create(
      "s21_string");  // создаем тестовый случай tc1_1 c названием s21_string
  SRunner *sr = srunner_create(
      s1);  // создаем отчет о запуске, связывая его с набором тестров
  int nf;
  suite_add_tcase(s1, tc1_1);  // добавляем тестовый случай к набору тестов

  tcase_add_test(tc1_1, s21_memchr_test);  // добавляем функцию в набор тестов
  tcase_add_test(tc1_1, s21_memcmp_test);
  tcase_add_test(tc1_1, s21_memcpy_test);
  tcase_add_test(tc1_1, s21_memset_test);
  tcase_add_test(tc1_1, s21_strncat_test);
  tcase_add_test(tc1_1, s21_strchr_test);
  tcase_add_test(tc1_1, s21_strncmp_test);
  tcase_add_test(tc1_1, s21_strncpy_test);
  tcase_add_test(tc1_1, s21_strcspn_test);
  tcase_add_test(tc1_1, s21_strerror_test);
  tcase_add_test(tc1_1, s21_strlen_test);
  tcase_add_test(tc1_1, s21_strpbrk_test);
  tcase_add_test(tc1_1, s21_strrchr_test);
  tcase_add_test(tc1_1, s21_strstr_test);
  tcase_add_test(tc1_1, s21_strtok_test);

  tcase_add_test(tc1_1, s21_to_lower_test);
  tcase_add_test(tc1_1, s21_to_upper_test);
  tcase_add_test(tc1_1, s21_insert_test);
  tcase_add_test(tc1_1, s21_trim_test);

  tcase_add_test(tc1_1, s21_sprintf_f_test);
  tcase_add_test(tc1_1, s21_sprintf_d_test);
  tcase_add_test(tc1_1, s21_sprintf_c_test);
  tcase_add_test(tc1_1, s21_sprintf_s_test);
  tcase_add_test(tc1_1, s21_sprintf_ld_test);
  tcase_add_test(tc1_1, s21_sprintf_u_test);
  tcase_add_test(tc1_1, s21_sprintf_ULTIMA_test);

  srunner_run_all(sr, CK_ENV);  //  запускает все тесты в наборе тестов с
                                //  использованием окружения CHECH.h
  nf = srunner_ntests_failed(
      sr);  // сохраянем колличество тестов, которые завершились
  srunner_free(sr);  // освобождаем память выделенную под структуру тестов

  return nf == 0 ? 0 : 1;
}