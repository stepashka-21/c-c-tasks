#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

void init_list(struct intrusive_list *list) { 
  list->head = malloc(sizeof(struct intrusive_node)); 
  list->head->next = list->head->prev = list->head;
}

void add_node(struct intrusive_list *list, struct intrusive_node *node) {
  node->next = list->head->next;
  node->prev = list->head;
  list->head->next->prev = node;
  list->head->next = node;
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node) {
  if (list->head != node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
}

int get_length(struct intrusive_list *list) {
  int length = 0;
  struct intrusive_node *current = list->head->next;

  while (current != list->head) {
    length++;
    current = current->next;
  }

  return length;
}
