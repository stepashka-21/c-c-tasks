#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

void count_point(struct intrusive_node *node, void *data) {
  (void)node;
  *(int*) data += 1;
}

void print_point(struct intrusive_node *node, void *data) {
  char *format = (char *)data;
  struct point *current = container_of(node, struct point, node);

  printf(format, current->x, current->y);
}

void read_point(struct intrusive_node *node, void *data) {
  FILE *input_file = (FILE *)data;

  int x, y;
  fscanf(input_file, "%d %d", &x, &y);

  add_point((struct intrusive_list *)node, x, y);
}

void load_text(const char *file_path, struct intrusive_list *list) {
  FILE *file = fopen(file_path, "r");

  int x, y;

  while (fscanf(file, "%d %d\n", &x, &y) == 2) {
    add_point(list, x, y);
  }

  fclose(file);
}

void load_bin(const char *file_path, struct intrusive_list *list) {
  FILE *file = fopen(file_path, "rb");

  int n = 0;
  int nums[2] = {0, 0};

  while (fread(&nums[n], 3, 1, file)) {
    if (nums[n] > 0x7FFFFF) {
      nums[n] -= 0x1000000;
    }

    n = ~n & 1;

    if (!n) {
      add_point(list, nums[0], nums[1]);
      nums[0] = 0, nums[1] = 0;
    }
  }
}

void save_text(const char *file_path, struct intrusive_list *list) {
  FILE *file = fopen(file_path, "w");

  struct intrusive_node *node = list->head->next;

  while (node != list->head) {
    struct point *current_point = container_of(node, struct point, node);
    
    int x = current_point->x;
    int y = current_point->y;

    fprintf(file, "%d %d\n", x, y);

    node = node->next;
  }

  fclose(file);
}

void save_bin(const char *file_path, struct intrusive_list *list) {
  FILE *file = fopen(file_path, "wb");

  struct intrusive_node *start_node = list->head->next;

  while (start_node != list->head) {
    struct point *current_point = container_of(start_node, struct point, node);

    fwrite(&current_point->x, 3, 1, file);
    fwrite(&current_point->y, 3, 1, file);

    start_node = start_node->next;
  }
}

int main(int argc, char *argv[]) {
  struct intrusive_list list;
  init_list(&list);

  if (argc > 100000) { // оно вроде не нужно, пусть хотя бы так.. 
    return 1;
  } 

  const char *load = argv[1];
  const char *infile = argv[2];
  const char *action = argv[3];

  if (strcmp(load, "loadtext") == 0) {
    load_text(infile, &list);
  } else {
    load_bin(infile, &list);
  }

  if (strcmp(action, "print") == 0) {
    apply(&list, print_point, (void *)argv[4]);
    printf("\n");
  } else if (strcmp(action, "count") == 0) {
    int count = 0;
    apply(&list, count_point, (void *)&count);
    printf("%d\n", count);
  } else {
    if (strcmp(argv[3], "savetext") == 0) {
      save_text(argv[4], &list);
    } else {
      save_bin(argv[4], &list);
    }
  }

  free_list(&list);

  return 0;
}
