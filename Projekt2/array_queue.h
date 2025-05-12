// array_queue.h
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "common.h"

void array_init();
void array_insert(Element e);
Element array_pop();
Element array_peek();
int array_size();
void array_change_priority(int value, int new_priority);
void array_free();

#endif // ARRAY_QUEUE_H
