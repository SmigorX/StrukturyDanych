#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoubleNode {
    void *data;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;

typedef struct DoubleLinkedList {
    DoubleNode *head;
} DoubleLinkedList;

typedef struct DoubleLinkedListWithTail {
    DoubleNode *head;
    DoubleNode *tail;
} DoubleLinkedListWithTail;

typedef union DoubleLinkedListUnion {
    DoubleLinkedList dll;
    DoubleLinkedListWithTail dllwt;
} DoubleLinkedListUnion;

typedef enum { DLL, DLLWT } ListType;

int doubleInitList(DoubleLinkedListUnion *list, ListType type);

int doubleCreateNode(void *data, size_t dataSize, DoubleNode *node);

const bool doubleEmpty(DoubleLinkedListUnion *list, ListType type);

void doublePushFront(DoubleLinkedListUnion *list, ListType type, void *content,
                     size_t dataSize);
void doublePushBack(DoubleLinkedListUnion *list, ListType type, void *content,
                    size_t dataSize);
int doublePushIndex(DoubleLinkedListUnion *list, ListType type, int index,
                    void *content, size_t dataSize);

int doublePopFront(DoubleLinkedListUnion *list, ListType type, void *content);
int doublePopBack(DoubleLinkedListUnion *list, ListType type, void *content);
int doublePopIndex(DoubleLinkedListUnion *list, ListType type, int index,
                   void *content);

typedef int (*CompareFunc)(const void *, const void *);

int doubleFindElement(DoubleLinkedListUnion *list, ListType type,
                      CompareFunc compare, void *content);

void printInt(const void *content);

void doublePrintList(DoubleLinkedListUnion *list,
                     void (*printFunc)(const void *));

#endif
