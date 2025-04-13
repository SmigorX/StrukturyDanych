#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    void* data;
    struct Node *next;
} Node;

typedef struct LinkedList{
    Node* head;
} LinkedList;

void initList(LinkedList *list);

Node* createNode(void *data, size_t dataSize);

const bool empty(LinkedList *list);

const void* front(LinkedList *list);

void pushFront(LinkedList *list, void *data, size_t dataSize);

void removeFront(LinkedList *list);

void printInt(const void *data);

void printList(LinkedList *list, void (*printFunc)(const void*));


#endif
