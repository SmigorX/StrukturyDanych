#include "single_list.h"

const bool empty(LinkedList *list) { return list->head == NULL; }
const void *front(LinkedList *list) { return list->head->data; }

void initList(LinkedList *list) { list->head = NULL; }

Node *createNode(void *data, size_t dataSize) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL) {
        free(newNode);
        return NULL;
    }
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    return newNode;
}

void pushFront(LinkedList *list, void *data, size_t dataSize) {
    Node *newNode = createNode(data, dataSize);
    newNode->next = list->head;
    list->head = newNode;
}

void removeFront(LinkedList *list) {
    Node *old = list->head;
    list->head = old->next;
    free(old->data);
    free(old);
}

void printInt(const void *data) { printf("%d -> ", *(int *)data); }

void printList(LinkedList *list, void (*printFunc)(const void *)) {
    Node *temp = list->head;
    while (temp != NULL) {
        printFunc(temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
