// array_queue.h
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "common.h"

#define ARRAY_MAX 10000

typedef struct {
    int size;
    Element array[ARRAY_MAX];
} Array_queue;

Array_queue array_init();
int array_size(Array_queue *);
void array_insert(Array_queue *, Element);
Element array_peek(Array_queue *);
Element array_pop(Array_queue *);
void array_clear(Array_queue *);
void array_change_priority(Array_queue *, int, int);

#endif // ARRAY_QUEUE_H
