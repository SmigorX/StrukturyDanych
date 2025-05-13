// list_queue.h
#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "common.h"

typedef struct Node {
    Element data;
    struct Node *next;
} Node;

typedef struct {
    int size;
    Node *head;
} List_queue;

List_queue list_init();
int list_size(List_queue *);
void list_insert(List_queue *, Element);
Element list_peek(List_queue *);
Element list_pop(List_queue *);
void list_change_priority(List_queue *, int, int);
void list_free(List_queue *);

#endif // LIST_QUEUE_H
