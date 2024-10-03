#include <assert.h>
#include <stdio.h>
#include "stdlib.h"
#include "string.h"

static void merge( 
    void *array,
    size_t left, size_t right, size_t element_size,
    int (*comparator)(const void *, const void *)
) {
    
  size_t i, j, k;
  size_t n1 = left + (right + left) / 2;
  size_t n2 = right - (right + left) / 2;
    
  void *arrray = malloc((n1 + n2) * element_size);
  
  if (arrray == NULL) {
    return;
  }
    
  i = 0; j = 0; k = 0;

  while (i < n1 && j < n2) {
    char *left_element = (char *)array + (left + i) * element_size;
    char *right_element = (char *)array + ((right + left) / 2 + j) * element_size;

    if (comparator(left_element, right_element) > 0) {
      memcpy((char *)arrray + k * element_size, left_element, element_size);
      i++;
    } else {
      memcpy((char *)arrray + k * element_size, right_element, element_size);
      j++;
    }
      k++;
  }
    
  while (i < n1) {
    char *left_element = (char *)array + (left + i) * element_size;
    
    memcpy((char *)arrray + k * element_size, left_element, element_size);
    i++;
    k++;
  }

  while (j < n2) {
    char *right_element = (char *)array + ((right + left) / 2 + j) * element_size;
    
    memcpy((char *)arrray + k * element_size, right_element, element_size);
    j++;
    k++;
  }
  
  memcpy((char *)array, (char *)arrray, n1 * element_size);
  memcpy((char *)array + element_size * n1, (char *)arrray + n1 * element_size, n2 * element_size);
  free(arrray);
}

int mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *)
    ) {
    
  if (elements <= 1) {
    return 0;
  }
  
  int left_array = mergesort(array, elements / 2, element_size, comparator);
  int right_array = mergesort(array + elements / 2 * element_size, elements - elements / 2, element_size, comparator);
  
  if (left_array == -1 || right_array == -1) {
    return -1;
  }

  merge(array, 0, elements, element_size, comparator);
  
  return 0;
}
