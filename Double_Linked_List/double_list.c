#include "double_list.h"

// returns 0 if successful, 1 if failed
int initList(DoubleLinkedListUnion *list, ListType type) {
    list = malloc(sizeof(DoubleLinkedListUnion));

    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (type == DLLWT) {
        list->dllwt.tail = NULL;
        list->dllwt.head = NULL;
    } else if (type == DLL) {
        list->dll.head = NULL;
    }

    return 0;
};

int createNode(void *data, size_t dataSize, Node *node) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    };
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    newNode->prev = NULL;
    node = newNode;
    return 0;
};

// Returns 1 if empty
const bool empty(DoubleLinkedListUnion *list, ListType type) {
    if (type == DLL) {
        return list->dll.head == NULL;
    } else if (type == DLLWT) {
        return list->dllwt.head == NULL;
    };
};

void pushFront(DoubleLinkedListUnion *list, ListType type, void *data,
               size_t dataSize) {

    Node *newNode = NULL;
    int result = createNode(data, dataSize, newNode);

    if (newNode == NULL || result == 1) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    if (type == DLLWT) {
        Node *oldHead = list->dllwt.head;
        list->dllwt.head = newNode;
        oldHead->prev = list->dllwt.head;
        list->dllwt.head->next = oldHead;
    } else if (type == DLL) {
        Node *oldHead = list->dll.head;
        list->dll.head = newNode;
        oldHead->prev = list->dll.head;
        list->dll.head->next = oldHead;
    }
};

void pushBack(DoubleLinkedListUnion *list, ListType type, void *data,
              size_t dataSize) {

    Node *newNode = NULL;
    int result = createNode(data, dataSize, newNode);

    if (newNode == NULL || result == 1) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    if (type == DLLWT) {
        Node *oldTail = list->dllwt.tail;
        list->dllwt.tail = newNode;
        oldTail->next = newNode;
        list->dllwt.tail->prev = oldTail;
    } else if (type == DLL) {
        Node *currentElement = list->dll.head;
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

    Node *newNode = NULL;
    int result = createNode(data, dataSize, newNode);

    if (newNode == NULL || result == 1) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    Node *currentElement;

    if (type == DLLWT) {
        currentElement = list->dllwt.head;
    } else {
        currentElement = list->dll.head;
    }

    while (counter != index) {
        if (currentElement->next == NULL && index - counter > 1) {
            fprintf(stderr, "Index out of range\n");
            return 1;
        }

        // push back if last element
        if (currentElement->next == NULL && index - counter == 1) {
            if (type == DLLWT) {
                list->dllwt.tail = newNode;
                currentElement->next = newNode;
                list->dllwt.tail->prev = currentElement;
                return 0;
            } else if (type == DLL) {
                currentElement->next = newNode;
                newNode->prev = currentElement;
                return 0;
            } else {
                return 1;
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

// Writes data from popped inedx to void *data argument pointer,
// returns 0 if success, 1 if failure
int popFront(DoubleLinkedListUnion *list, ListType type, void *content) {
    if (type == DLLWT) {
        content = list->dllwt.head->data;
        list->dllwt.head->next->prev = NULL;
        Node *oldHead = list->dllwt.head;
        list->dllwt.head = list->dllwt.head->next;
        free(oldHead);
    } else if (type == DLL) {
        content = list->dll.head->data;
        list->dll.head->next->prev = NULL;
        Node *oldHead = list->dll.head;
        list->dll.head = list->dll.head->next;
        free(oldHead);
    } else {
        return 1;
    }

    return 0;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
int popBack(DoubleLinkedListUnion *list, ListType type, void *content) {
    if (type == DLLWT) {
        Node *oldTail = list->dllwt.tail;
        list->dllwt.tail = list->dllwt.tail->prev;
        list->dllwt.tail->next = NULL;
        content = oldTail->data;
        free(oldTail);
    } else if (type == DLL) {
        Node *lastNode = list->dll.head;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        };
        lastNode->prev->next = NULL;
        content = lastNode->data;
        free(lastNode);
    } else {
        fprintf(stderr, "Wrong list type\n");
        content = NULL;
        return 1;
    };
    return 0;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
int popIndex(DoubleLinkedListUnion *list, ListType type, int index,
             void *content) {
    int counter = 0;

    Node *currentElement = NULL;

    if (type == DLLWT) {
        currentElement = list->dllwt.head;
    } else if (type == DLL) {
        currentElement = list->dll.head;
    } else {
        return 1;
    }

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
            Node *oldTail = list->dllwt.tail;
            list->dllwt.tail = list->dllwt.tail->prev;
            list->dllwt.tail->next = NULL;
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
            content = NULL;
            return 1;
        };
    };

    content = currentElement->data;
    currentElement->next->prev = currentElement->prev;
    currentElement->prev->next = currentElement->next;
    free(currentElement);
};

// Comparison function type
int compareInt(const void *a, const void *b) {
    return (*(int *)a == *(int *)b);
}

// Function to find an element in the list
// returns index if found, -1 if not found
int findElement(DoubleLinkedListUnion *list, ListType type, CompareFunc compare,
                void *content) {
    Node *current;
    if (type == DLL) {
        current = list->dll.head;
    } else if (type == DLLWT) {
        current = list->dllwt.head;
    } else {
        fprintf(stderr, "Wrong list type\n");
        return -1; // Invalid list type
    }

    int index = 0;
    while (current != NULL) {
        if (compare(current->data, content)) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // Data not found
}
