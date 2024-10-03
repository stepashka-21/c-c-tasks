#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

int int_gt_comparator(const void *a, const void *b) {
  return *(int*)b - *(int*)a;  
}

int char_gt_comparator(const void *a, const void *b) {
  return (*(char *)b - *(char *)a);
}

int str_gt_comparator(const void *a, const void *b) {
  return strcmp(*(const char **)b, *(const char **)a);
}

int (*type_comparator(char *type))(const void *, const void *) {
  int (*comparator)(const void *, const void *) = NULL;

  if (strcmp(type, "int") == 0) {
    comparator = int_gt_comparator;
  } else if (strcmp(type, "char") == 0) {
    comparator = char_gt_comparator;
  } else if (strcmp(type, "str") == 0) {
    comparator = str_gt_comparator;
  }

  return comparator; 
}

int elem_size(char *type) {
  size_t element_size;

  if (strcmp(type, "int") == 0) {
    element_size = sizeof(int);
  } else if (strcmp(type, "char") == 0) {
    element_size = sizeof(char);
  } else {
    element_size = sizeof(char *);
  }

  return element_size;
}

void *array_to_work(size_t elements, size_t element_size, char *type, char *argvs[]) {
  void *array = malloc(elements * element_size);

  for (size_t i = 0; i < elements; ++i) {
    if (strcmp(type, "int") == 0) {
      ((int *)array)[i] = atoi(argvs[i + 2]);
    } else if (strcmp(type, "char") == 0) {
      ((char *)array)[i] = argvs[i + 2][0];
    } else {
      ((char **)array)[i] = argvs[i + 2];
    }
  }

  return array;
}

void print_array(void *array, size_t elements, char *type) {
  int *int_array = (int *)array;
  char *char_array = (char *)array;
  char **str_array = (char **)array;

  for (size_t i = 0; i < elements - 1; ++i) {
    if (strcmp(type, "int") == 0) {
      printf("%d ", *(int_array + i));
    } else if (strcmp(type, "char") == 0) {
      printf("%c ", *(char_array + i));
    } else if (strcmp(type, "str") == 0) {
      printf("%s ", *(str_array + i));
    }
  }
  
  if (strcmp(type, "int") == 0) {
    printf("%d", *(int_array + elements - 1));
  } else if (strcmp(type, "char") == 0) {
    printf("%c", *(char_array + elements - 1));
  } else if (strcmp(type, "str") == 0) {
    printf("%s", *(str_array + elements - 1));
  }
}

int main(int argc, char *argv[]) {

  int (*comparator)(const void *, const void *);
  comparator = type_comparator(argv[1]);

  size_t elements = argc - 2;

  if (elements == 0) {
    printf("\n");
    return 0;
  }

  size_t element_size;
  element_size = elem_size(argv[1]);

  void *array = array_to_work(elements, element_size, argv[1], argv);

  int result = mergesort(array, elements, element_size, comparator);
  
  if (result == -1) {
    printf("Error: memory allocation failed.\n");
    free(array);
    
    return 1;
  }

  print_array(array, elements, argv[1]);

  printf("\n");
  free(array);

  return 0;
}
