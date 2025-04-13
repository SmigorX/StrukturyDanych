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

int initList(DoubleLinkedListUnion *list, ListType type);

int createNode(void *data, size_t dataSize, Node *node);

const bool empty(DoubleLinkedListUnion *list, ListType type);

void pushFront(DoubleLinkedListUnion *list, ListType type, void *content,
               size_t dataSize);
void pushBack(DoubleLinkedListUnion *list, ListType type, void *content,
              size_t dataSize);
int pushIndex(DoubleLinkedListUnion *list, ListType type, int index,
              void *content, size_t dataSize);

int popFront(DoubleLinkedListUnion *list, ListType type, void *content);
int popBack(DoubleLinkedListUnion *list, ListType type, void *content);
int popIndex(DoubleLinkedListUnion *list, ListType type, int index,
             void *content);

typedef int (*CompareFunc)(const void *, const void *);

int findElement(DoubleLinkedListUnion *list, ListType type, CompareFunc compare,
                void *content);

void printInt(const void *content);

void printList(DoubleLinkedListUnion *list, void (*printFunc)(const void *));

#endif
