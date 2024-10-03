#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

struct point {
  int x, y;
  struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y) {
  struct point *new_point = malloc(sizeof(struct point));
  new_point->x = x;
  new_point->y = y;
  add_node(list, &new_point->node);
}

void remove_point(struct intrusive_list *list, int x, int y) {
  struct intrusive_node *current = list->head->next;
  while (current != list->head) {
    struct intrusive_node *next_node = current->next;
    struct point *current_point = container_of(current, struct point, node);
    if (current_point->x == x && current_point->y == y) {
      remove_node(list, current);
      free(current_point);
    } 
    current = next_node;
  }
}

void show_all_points(struct intrusive_list *list) {
  struct intrusive_node *current = list->head->next;
  while (current != list->head) {
    struct point *current_point = container_of(current, struct point, node);
    printf("(%d %d)", current_point->x, current_point->y);
    current = current->next;
    if (current != list->head) {
      printf(" ");
    }
  }
  printf("\n");
}

void remove_all_points(struct intrusive_list *list) {
  struct intrusive_node *current = list->head->next;
  while (current != list->head) {
    struct intrusive_node *next_node = current->next;
    struct point *current_point = container_of(current, struct point, node);
    remove_node(list, current);
    free(current_point);
    current = next_node;
  }
}

void free_list(struct intrusive_list *list) {
  struct intrusive_node *current = list->head->next;
  while (current != list->head) {
    struct intrusive_node *next_node = current->next;
    struct point *current_point = container_of(current, struct point, node);
    free(current_point);
    current = next_node;
  }
  free(list->head);
}


int main() {
  struct intrusive_list l;
  init_list(&l);
  
  while(1) {
    char command[256];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    if (strncmp(command, "add", 3) == 0)  {
      int x, y;
      sscanf(command, "add %d %d", &x, &y);
      add_point(&l, x, y);
    } else if (strncmp(command, "rma", 3) == 0) {
      remove_all_points(&l);
    } else if (strncmp(command, "rm", 2) == 0) {
      int x, y;
      sscanf(command, "rm %d %d", &x, &y);
      remove_point(&l, x, y);
    } else if (strncmp(command, "print", 5) == 0) {
      show_all_points(&l);
    } else if (strncmp(command, "len", 3) == 0) {
      printf("%d\n", get_length(&l));
    } else if (strncmp(command, "exit", 4) == 0) {
      break;
    } else {
      printf("Unknown command\n");
    }
  }
  
  free_list(&l);
  
  return 0;
}
