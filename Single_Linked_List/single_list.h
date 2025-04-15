#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Struktury listy */
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
} LinkedList;

/* Prototypy funkcji */
void initList(LinkedList *list);
Node* createNode(void *data, size_t dataSize);
bool empty(LinkedList *list);
void* front(LinkedList *list);
void pushFront(LinkedList *list, void *data, size_t dataSize);
void pushIndex(LinkedList *list, void *data, size_t dataSize, int index);
void pushBack(LinkedList *list, void *data, size_t dataSize);
void popFront(LinkedList *list);
void popIndex(LinkedList *list, int index);
void popBack(LinkedList *list);

typedef int (*CompareFunc)(const void*, const void*);
Node* find(LinkedList *list, void *key, CompareFunc cmp);
int compareInt(const void *a, const void *b);

void printInt(const void *data);
void printList(LinkedList *list, void (*printFunc)(const void*));

#endif

