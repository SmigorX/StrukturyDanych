#include "double_list.h"

DoubleLinkedListUnion *initList(ListType type) {
    DoubleLinkedListUnion *list = malloc(sizeof(DoubleLinkedListUnion));

    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    list->head = NULL;
    if (type == DLLWT) {
        list->tail = NULL;
    }
    return list;
};

Node *createNode(void *data, size_t dataSize) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    };
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
};

const bool empty(LinkedListUnion *list) { return list->head == NULL; };

void pushFront(DoubleLinkedListUnion *list, void *data, size_t dataSize) {

    Node *newNode = createNode(data, dataSize);

    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    Node *oldHead = list->head;
    list->head = newNode;
    oldHead->prev = list->head;
    list->head->next = oldHead;
};

void pushBack(DoubleLinkedListUnion *list, ListType type, void *data,
              size_t dataSize) {

    Node *newNode = createNode(data, dataSize);

    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    };

    if (type == DLLWT) {
        Node *oldTail = list->tail;
        list->tail = newNode;
        oldTail->next = newNode;
        list->tail->prev = oldtail;
    } else if (type == DDL) {
        Node *currentElement = list->head;
        while (currentElement->next != NULL) {
            currentElement = currentElement->next;
        }
        currentElement->next = newNode;
        newNode->prev = currentElement;
    };
};

int pushIndex(DoubleLinkedListUnion *list, ListType type, int index, void *data,
              size_t dataSize) {
    int counter = 0;
    Node *newNode = createNode(data, dataSize);

    Node *currentElement = list->head;

    while (counter != index) {
        if (currentElement->next == NULL && index - counter > 1) {
            fprintf(stderr, "Index out of range\n");
            return 1;
        }

        // push back if last element
        if (currentElement->next == NULL && index - counter == 1) {
            if (type == DLLWT) {
                list->tail = newNode;
                currentElement->next = newNode;
                list->tail->prev = currentElement;
                return 0;
            } else if (type == DLL) {
                currentElement->next = newNode;
                newNode->prev = currentElement;
                return 0;
            }
        };
        currentElement = currentElement->next;

        counter += 1;
    };

    newNode->next = currentElement;
    newNode->prev = currentElement->prev;
    newNode->next->prev = newNode;
    newNode->prev->next = newNode;
    return 0;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
void *popFront(DoubleLinkedListUnion *list, void *data) {
    void *content = list->head->data;

    list->head->next->prev = NULL;

    Node *oldHead = list->head;
    list->head = list->head->next;
    free(oldHead);

    data = content;
    return;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
int *popBack(DoubleLinkedListUnion *list, ListType type, void *data) {
    void *content;
    if (type == DLLWT) {
        Node *oldTail = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        content = oldTail->data;
        free(oldTail);
    } else if (type == DLL) {
        Node *lastNode = list->head;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        };
        lastNode->prev->next = NULL;
        content = lastNode->data;
        free(lastNode);
    } else {
        fprintf(stderr, "Wrong list type\n");
        data = NULL;
        return 1;
    };
    data = content;
    return 0;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
int *popIndex(DoubleLinkedListUnion *list, ListType type, int index,
              void *data) {
    void *content;
    int counter = 0;

    Node *curretElement = list->head;

    while (counter != index) {
        if (currentElement->next == NULL) {
            fprintf(stderr, "Index out of range\n");
            return 1;
        }
        counter += 1;
        currentElement = currentElement->next;
    };

    if (currentElement->next == NULL) {
        if (type == DLLWT) {
            Node *oldTail = list->tail;
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            content = oldTail->data;
            free(oldTail);
            return 0;
        } else if (type == DLL) {
            Node *lastNode = currentElement;
            lastNode->prev->next = NULL;
            content = lastNode->data;
            free(lastNode);
            return 0;
        } else {
            fprintf(stderr, "Wrong list type\n");
            data = NULL;
            return 1;
        };
    };

    content = currentElement->data;
    currentElement->next->prev = currentElement->prev;
    currentElement->prev->next = currentElement->next;
    free(currentElement);
};

int find(DoubleLinkedListUnion *list, void *data) { int index = 0; };

// Comparison function type
int compareInt(const void *a, const void *b) {
    return (*(int *)a == *(int *)b);
}

// Function to find an element in the list
// returns index if found, -1 if not found
int find(DoubleLinkedListUnion *list, void *data, ListType type,
         CompareFunc compare) {
    Node *current;
    if (type == DLL) {
        current = list->dll->head;
    } else if (type == DLLWT) {
        current = list->dllwt->head;
    } else {
        return -1; // Invalid list type
    }

    int index = 0;
    while (current != NULL) {
        if (compare(current->data, data)) {
            return index; // Data found, return the index
        }
        current = current->next;
        index++;
    }

    return -1; // Data not found
}
