#include "heap_queue.h"
#include <assert.h>

// Initialize a new heap queue
Heap_queue heap_init() {
    Heap_queue queue = {0};
    return queue;
}

// Get the current size of the heap
int heap_size(Heap_queue *queue) { return queue->size; }

// Peek at the top element without removing it
Element heap_peek(Heap_queue *queue) {
    assert(queue->size > 0); // Ensure heap isn't empty
    return queue->heap[0];   // Return the root element
}

// Restore heap property by moving element up
void heapify_up(Heap_queue *queue, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (queue->heap[parent].priority <= queue->heap[i].priority)
            break;
        heap_change_priority(queue, parent, i);
        i = parent;
    }
}

// Restore heap property by moving element down
void heapify_down(Heap_queue *queue, int i) {
    while (2 * i + 1 < queue->size) {
        int child = 2 * i + 1;
        if (child + 1 < queue->size &&
            queue->heap[child + 1].priority < queue->heap[child].priority)
            child++;
        if (queue->heap[i].priority <= queue->heap[child].priority)
            break;
        // Pass the actual 'value' field, not the index
        heap_change_priority(queue, queue->heap[i].value,
                             queue->heap[child].priority);
        i = child;
    }
}

// Change priority of an element and maintain heap property
void heap_change_priority(Heap_queue *queue, int value, int new_priority) {
    // Find the element with matching value
    for (int i = 0; i < queue->size; i++) {
        if (queue->heap[i].value == value) {
            int old_priority = queue->heap[i].priority;
            queue->heap[i].priority = new_priority;

            // Maintain heap property
            if (new_priority < old_priority) {
                // Priority increased - move up
                heapify_up(queue, i);
            } else {
                // Priority decreased - move down
                heapify_down(queue, i);
            }
            return;
        }
    }
}

// Insert a new element into the heap
void heap_insert(Heap_queue *queue, Element e) {
    if (queue->size >= HEAP_MAX)
        return;
    queue->heap[queue->size] = e;
    heapify_up(queue, queue->size++);
}

// Remove and return the top element
Element heap_pop(Heap_queue *queue) {
    assert(queue->size > 0); // Ensure heap isn't empty
    Element top = queue->heap[0];
    queue->heap[0] = queue->heap[--queue->size];
    heapify_down(queue, 0);
    return top;
}

// Clear the heap
void heap_clear(Heap_queue *queue) {
    queue->size = 0; // Reset size to effectively clear the heap
}
