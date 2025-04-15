
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struktura pojedynczego węzła */
typedef struct DoubleNode {
    void *data;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;

/* Warianty listy: tylko głowa lub głowa i ogon */
typedef struct DoubleLinkedList {
    DoubleNode *head;
} DoubleLinkedList;

typedef struct DoubleLinkedListWithTail {
    DoubleNode *head;
    DoubleNode *tail;
} DoubleLinkedListWithTail;

/* Unia umożliwiająca wykorzystanie obu wariantów */
typedef union DoubleLinkedListUnion {
    DoubleLinkedList dll;
    DoubleLinkedListWithTail dllwt;
} DoubleLinkedListUnion;

/* Typ listy – bez ogona lub z ogonem */
typedef enum { DLL, DLLWT } ListType;

/* Prototypy funkcji */
int doubleInitList(DoubleLinkedListUnion *list, ListType type);

/* Tworzy nowy węzeł – przekazuje adres wskaźnika w node */
int doubleCreateNode(void *data, size_t dataSize, DoubleNode **node);

bool doubleEmpty(DoubleLinkedListUnion *list, ListType type);

void doublePushFront(DoubleLinkedListUnion *list, ListType type, void *content, size_t dataSize);
void doublePushBack(DoubleLinkedListUnion *list, ListType type, void *content, size_t dataSize);
/* Funkcja wstawia element pod indeks – zwraca 0 przy sukcesie, 1 przy błędzie */
int doublePushIndex(DoubleLinkedListUnion *list, ListType type, int index, void *content, size_t dataSize);

/* Funkcje usuwające element – dodatkowo kopiują usuwane dane do bufora content.
   Dodajemy argument dataSize, aby wiedzieć, ile bajtów kopiować. */
int doublePopFront(DoubleLinkedListUnion *list, ListType type, void *content, size_t dataSize);
int doublePopBack(DoubleLinkedListUnion *list, ListType type, void *content, size_t dataSize);
int doublePopIndex(DoubleLinkedListUnion *list, ListType type, int index, void *content, size_t dataSize);

/* Funkcja porównująca – zwraca 1, jeśli elementy są równe, 0 w przeciwnym wypadku */
typedef int (*CompareFunc)(const void *, const void *);

int doubleFindElement(DoubleLinkedListUnion *list, ListType type, CompareFunc compare, void *content);

/* Funkcje pomocnicze do wypisywania listy */
//void printInt(const void *content);
/* Dodajemy parametr ListType, żeby wiedzieć, z którego wariantu listy korzystamy */
void doublePrintList(DoubleLinkedListUnion *list, ListType type, void (*printFunc)(const void *));

#endif

