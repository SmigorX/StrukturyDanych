#include "heap_queue.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static Element heap[MAX_SIZE];
static int count = 0;

void heap_init() {
    count = 0;
}

int heap_size() {
    return count;
}

void swap(int i, int j) {
    Element temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void heapify_up(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].priority <= heap[i].priority)
            break;
        swap(parent, i);
        i = parent;
    }
}

void heapify_down(int i) {
    while (2 * i + 1 < count) {
        int child = 2 * i + 1;
        if (child + 1 < count && heap[child + 1].priority < heap[child].priority)
            child++;
        if (heap[i].priority <= heap[child].priority)
            break;
        swap(i, child);
        i = child;
    }
}

void heap_insert(Element e) {
    if (count >= MAX_SIZE) return;
    heap[count] = e;
    heapify_up(count++);
}

Element heap_peek() {
    return heap[0];
}

Element heap_pop() {
    Element top = heap[0];
    heap[0] = heap[--count];
    heapify_down(0);
    return top;
}

void heap_change_priority(int value, int new_priority) {
    for (int i = 0; i < count; i++) {
        if (heap[i].value == value) {
            int old_priority = heap[i].priority;
            heap[i].priority = new_priority;
            if (new_priority < old_priority) {
                heapify_up(i);
            } else {
                heapify_down(i);
            }
            return;
        }
    }
}

void heap_free() {
    count = 0;
}
