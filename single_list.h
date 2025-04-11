#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct StringNode{
    int elem;
    struct StringNode* next;
} StringNode;

const bool empty(StringNode* head);

const int front(StringNode* head);

void addFront(const int e, StringNode** head);

void removeFront(StringNode** head);

void printList(StringNode* head);


#endif
