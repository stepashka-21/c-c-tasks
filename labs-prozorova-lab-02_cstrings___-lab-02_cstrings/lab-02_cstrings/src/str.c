#include <stdio.h>
#include "str.h"

char *my_strcpy(char *restrict s1, const char *restrict s2) {
  char *start = s1;
  
  while (*s2) {
    *s1 = *s2;
    s1++;
    s2++;
  }
  *s1 = '\0';
  
  return start;
}

char *my_strcat(char *restrict s1, const char *restrict s2) {
  char *start = s1;
  
  s1 += my_strlen(s1);
  
  my_strcpy(s1, s2);
  
  return start;
}

int my_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }
    s1++;
    s2++;
  }
  
  if (!*s1 && !*s2) {
    return 0;
  } else if (!*s1) {
    return -1;
  }
  return 1;
}

size_t my_strlen(const char *s) {
  size_t length = 0;

  while (*s) {
    length++;
    s++;
  }

  return length;
}
