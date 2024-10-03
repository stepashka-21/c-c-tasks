#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

void init_list(struct intrusive_list *list) { 
  list->head = malloc(sizeof(struct intrusive_node)); 
  list->head->prev = list->head->next = list->head;
}

void add_node(struct intrusive_list *list, struct intrusive_node *node) {
  node->next = list->head;
  node->prev = list->head->prev;
  list->head->prev->next = node;
  list->head->prev = node;
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node) {
  if (list->head != node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
}

void apply(struct intrusive_list *list, void (*op)(struct intrusive_node *node, void *data), void *data) {
  struct intrusive_node *current = list->head->next;

  while (current != list->head) {
    struct intrusive_node *next_node = current->next;
    op(current, data);
    current = next_node;
  }
}
