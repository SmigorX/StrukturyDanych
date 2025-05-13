// array_queue.c
#include "array_queue.h"

Array_queue array_init() {
    Array_queue queue = {0};
    return queue;
}

int array_size(Array_queue *queue) { return queue->size; }

void array_insert(Array_queue *queue, Element e) {
    if (queue->size < ARRAY_MAX) {
        queue->array[queue->size++] = e;
    }
}

Element array_peek(Array_queue *queue) {
    if (queue->size == 0)
        return (Element){0, 0};
    int idx = 0;
    for (int i = 1; i < queue->size; i++) {
        if (queue->array[i].priority < queue->array[idx].priority)
            idx = i;
    }
    return queue->array[idx];
}

Element array_pop(Array_queue *queue) {
    if (queue->size == 0)
        return (Element){0, 0};
    int idx = 0;
    for (int i = 1; i < queue->size; i++) {
        if (queue->array[i].priority < queue->array[idx].priority)
            idx = i;
    }
    Element result = queue->array[idx];
    for (int i = idx; i < queue->size - 1; i++) {
        queue->array[i] = queue->array[i + 1];
    }
    queue->size--;
    return result;
}

void array_clear(Array_queue *queue) {
    while (queue->size > 0) {
        array_pop(queue);
    }
};

void array_change_priority(Array_queue *queue, int value, int new_priority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->array[i].value == value) {
            queue->array[i].priority = new_priority;
            return;
        }
    }
}
