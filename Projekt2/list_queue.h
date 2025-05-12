// list_queue.h
#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "common.h"

void list_init();
void list_insert(Element e);
Element list_pop();
Element list_peek();
int list_size();
void list_change_priority(int value, int new_priority);
void list_free();

#endif // LIST_QUEUE_H
