// array_queue.c
#include "array_queue.h"

#define ARRAY_MAX 1000

static Element arr[ARRAY_MAX];
static int arr_count = 0;

void array_init() {
    arr_count = 0;
}

int array_size() {
    return arr_count;
}

void array_insert(Element e) {
    if (arr_count < ARRAY_MAX) {
        arr[arr_count++] = e;
    }
}

Element array_peek() {
    if (arr_count == 0) return (Element){0,0};
    int idx = 0;
    for (int i = 1; i < arr_count; i++) {
        if (arr[i].priority < arr[idx].priority)
            idx = i;
    }
    return arr[idx];
}

Element array_pop() {
    if (arr_count == 0) return (Element){0,0};
    int idx = 0;
    for (int i = 1; i < arr_count; i++) {
        if (arr[i].priority < arr[idx].priority)
            idx = i;
    }
    Element result = arr[idx];
    for (int i = idx; i < arr_count - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr_count--;
    return result;
}

void array_change_priority(int value, int new_priority) {
    for (int i = 0; i < arr_count; i++) {
        if (arr[i].value == value) {
            arr[i].priority = new_priority;
            return;
        }
    }
}

void array_free() {
    arr_count = 0;
}
