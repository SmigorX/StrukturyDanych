#ifndef HEAP_QUEUE_H
#define HEAP_QUEUE_H

#include "common.h"

#define HEAP_MAX 1000

typedef struct {
    int size;
    Element heap[HEAP_MAX];
} Heap_queue;

Heap_queue heap_init();
int heap_size(Heap_queue *queue);
void heap_insert(Heap_queue *queue, Element e);
Element heap_peek(Heap_queue *queue);
Element heap_pop(Heap_queue *queue);
void heap_clear(Heap_queue *queue);
void heap_change_priority(Heap_queue *queue, int value, int new_priority);

#endif
