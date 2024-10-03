#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

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
