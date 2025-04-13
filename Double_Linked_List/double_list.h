#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DoubleLinkedList {
    Node *head;
} DoubleLinkedList;

typedef struct DoubleLinkedListWithTail {
    Node *head;
    Node *tail;
} DoubleLinkedListWithTail;

typedef union DoubleLinkedListUnion {
    DoubleLinkedList dll;
    DoubleLinkedListWithTail dllwt;
} DoubleLinkedListUnion;

typedef enum { DLL, DLLWT } ListType;

void initList(DoubleLinkedListUnion *list, ListType type);

Node *createNode(void *data, size_t dataSize);

const bool empty(DoubleLinkedListUnion *list);

void pushFront(DoubleLinkedListUnion *list, void *data, size_t dataSize);
void pushBack(DoubleLinkedListUnion *list, ListType type, void *data,
              size_t dataSize);
int pushIndex(DoubleLinkedListUnion *list, int index, void *data,
              size_t dataSize);

int *popFront(DoubleLinkedListUnion *list, void *data);
int *popBack(DoubleLinkedListUnion *list, ListType type, void *data);
int *popIndex(DoubleLinkedListUnion *list, ListType type, int index,
              void *data);

typedef int (*CompareFunc)(const void *, const void *);

int find(DoubleLinkedListUnion *list, void *data);

void printInt(const void *data);

void printList(DoubleLinkedListUnion *list, void (*printFunc)(const void *));

#endif
