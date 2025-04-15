#include "single_list.h"

bool empty(LinkedList *list) { return (list->head == NULL); }

void *front(LinkedList *list) {
    if (empty(list))
        return NULL;
    return list->head->data;
}

void initList(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

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
    if (newNode == NULL) {
        printf("Błąd alokacji pamięci\n");
        return;
    }
    newNode->next = list->head;
    list->head = newNode;
    // Jeśli lista była pusta, ustaw również tail
    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void pushBack(LinkedList *list, void *data, size_t dataSize) {
    Node *newNode = createNode(data, dataSize);
    if (newNode == NULL) {
        printf("Błąd alokacji pamięci\n");
        return;
    }
    if (empty(list)) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void pushIndex(LinkedList *list, void *data, size_t dataSize, int index) {
    if (index < 0) {
        printf("Wrong index!\n");
        return;
    }
    if (index == 0) {
        pushFront(list, data, dataSize);
        return;
    }
    Node *current = list->head;
    int i;
    for (i = 0; current != NULL && i < index - 1; i++) {
        current = current->next;
    }
    if (current == NULL) {
        fprintf(stderr, "[ERROR] (pushIndex) Index out of list size\n");
        return;
    }
    Node *newNode = createNode(data, dataSize);
    if (newNode == NULL) {
        printf("Błąd alokacji pamięci\n");
        return;
    }
    newNode->next = current->next;
    current->next = newNode;
    // Jeśli wstawiono na końcu, aktualizujemy tail:
    if (newNode->next == NULL) {
        list->tail = newNode;
    }
}

void popFront(LinkedList *list) {
    if (empty(list)) {
        fprintf(stderr, "[ERROR] (popFront) List is empty\n");
        return;
    }
    Node *old = list->head;
    list->head = old->next;
    if (list->head == NULL) { // Lista stała się pusta
        list->tail = NULL;
    }
    free(old->data);
    free(old);
}

int popIndex(LinkedList *list, int index) {
    if (empty(list)) {
        fprintf(stderr, "[ERROR] (popIndex) List is empty\n");
        return 1;
    }
    if (index < 0) {
        fprintf(stderr, "[ERROR] (popIndex) Wrong index!\n");
        return 1;
    }
    if (index == 0) {
        popFront(list);
        return 1;
    }
    Node *current = list->head;
    int i = 0;
    for (; current->next != NULL && i < index - 1; i++) {
        current = current->next;
    }
    if (current->next == NULL && i != index) {
        fprintf(
            stderr,
            "[ERROR] (popIndex) Index out of list size, index: %d, current: "
            "%d\n",
            index, i);
        return 1;
    }
    Node *old = current->next;
    current->next = old->next;
    if (current->next == NULL) { // usunięto ostatni element – aktualizacja tail
        list->tail = current;
    }
    free(old->data);
    free(old);
    return 0;
}

void popBack(LinkedList *list) {
    if (empty(list)) {
        fprintf(stderr, "[ERROR] (popBack) List is empty\n");
        return;
    }
    if (list->head->next == NULL) { // Tylko jeden element
        free(list->head->data);
        free(list->head);
        list->head = list->tail = NULL;
        return;
    }
    Node *current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }
    free(list->tail->data);
    free(list->tail);
    list->tail = current;
    current->next = NULL;
}

int compareInt(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    if (int_a == int_b)
        return 0;
    else
        return (int_a < int_b) ? -1 : 1;
}

Node *find(LinkedList *list, void *key, CompareFunc cmp) {
    Node *current = list->head;
    while (current != NULL) {
        if (cmp(current->data, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void printInt(const void *data) { printf("%d -> ", *(int *)data); }

void printList(LinkedList *list, void (*printFunc)(const void *)) {
    Node *current = list->head;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
    printf("NULL\n");
}
