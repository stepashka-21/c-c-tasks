#include <stdio.h>
#include "str.h"
#include <string.h>
#include <assert.h>

void test_strcpy() {
  {
    char s1[] = "";
    char s2[20] = "qwe";
    char s3[] = "";
    char s4[20] = "qwe";
    assert(strcmp(my_strcpy(s1, s2), strcpy(s3, s4)) == 0);
  }

  {
    char s1[20] = "asdfg";
    char s2[20] = "qwe";
    char s3[20] = "asdfg";
    char s4[20] = "qwe";
    assert(strcmp(my_strcpy(s1, s2), strcpy(s3, s4)) == 0);
  }
}

void test_strcat() {
  {
    char s1[20] = "bhfwub";
    char s2[20] = "eivb";
    char s3[20] = "bhfwub";
    char s4[20] = "eivb";
    assert(strcmp(my_strcat(s1, s2), strcat(s3, s4)) == 0);
  }

  {
    char s1[20] = "asdfg";
    char s2[20] = "";
    char s3[20] = "asdfg";
    char s4[20] = "";
    assert(strcmp(my_strcat(s1, s2), strcat(s3, s4)) == 0);
  }
}

void test_strcmp() {
  {
    char s1[20] = "bhfwub";
    char s2[20] = "eivb";
    assert((my_strcmp(s1, s2) < 0) == (strcmp(s1, s2) < 0));
  }

  {
    char s1[20] = "asdfg";
    char s2[20] = "asdfg";
    assert(my_strcmp(s1, s2) == strcmp(s1, s2));
  }
}

void test_strlen() {
  {
    char s[20] = "bhfwub";
    assert(my_strlen(s) == strlen(s));
  }

  {
    char s[20] = "";
    assert(my_strlen(s) == strlen(s));
  }
}
