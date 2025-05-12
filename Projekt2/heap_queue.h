#ifndef HEAP_QUEUE_H
#define HEAP_QUEUE_H

#include "common.h"

void heap_init();
void heap_insert(Element e);
Element heap_pop();
Element heap_peek();
int heap_size();
void heap_change_priority(int value, int new_priority);
void heap_free();

#endif
