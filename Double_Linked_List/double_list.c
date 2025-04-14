#include "double_list.h"

// returns 0 if successful, 1 if failed
int doubleInitList(DoubleLinkedListUnion *list, ListType type) {
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

int doubleCreateNode(void *data, size_t dataSize, DoubleNode *node) {
    DoubleNode *newDoubleNode = (DoubleNode *)malloc(sizeof(node));
    if (newDoubleNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    newDoubleNode->data = malloc(dataSize);
    if (newDoubleNode->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    };
    memcpy(newDoubleNode->data, data, dataSize);
    newDoubleNode->next = NULL;
    newDoubleNode->prev = NULL;
    node = newDoubleNode;
    return 0;
};

// Returns 1 if empty
const bool doubleEmpty(DoubleLinkedListUnion *list, ListType type) {
    if (type == DLL) {
        return list->dll.head == NULL;
    } else if (type == DLLWT) {
        return list->dllwt.head == NULL;
    };
};

void doublePushFront(DoubleLinkedListUnion *list, ListType type, void *data,
                     size_t dataSize) {

    DoubleNode *newDoubleNode = NULL;
    int result = doubleCreateNode(data, dataSize, newDoubleNode);

    if (newDoubleNode == NULL || result == 1) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    if (type == DLLWT) {
        DoubleNode *oldHead = list->dllwt.head;
        list->dllwt.head = newDoubleNode;
        oldHead->prev = list->dllwt.head;
        list->dllwt.head->next = oldHead;
    } else if (type == DLL) {
        DoubleNode *oldHead = list->dll.head;
        list->dll.head = newDoubleNode;
        oldHead->prev = list->dll.head;
        list->dll.head->next = oldHead;
    }
};

void doublePushBack(DoubleLinkedListUnion *list, ListType type, void *data,
                    size_t dataSize) {

    DoubleNode *newDoubleNode = NULL;
    int result = doubleCreateNode(data, dataSize, newDoubleNode);

    if (newDoubleNode == NULL || result == 1) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    if (type == DLLWT) {
        DoubleNode *oldTail = list->dllwt.tail;
        list->dllwt.tail = newDoubleNode;
        oldTail->next = newDoubleNode;
        list->dllwt.tail->prev = oldTail;
    } else if (type == DLL) {
        DoubleNode *currentElement = list->dll.head;
        while (currentElement->next != NULL) {
            currentElement = currentElement->next;
        }
        currentElement->next = newDoubleNode;
        newDoubleNode->prev = currentElement;
    };
};

int doublePushIndex(DoubleLinkedListUnion *list, ListType type, int index,
                    void *data, size_t dataSize) {
    int counter = 0;

    DoubleNode *newDoubleNode = NULL;
    int result = doubleCreateNode(data, dataSize, newDoubleNode);

    if (newDoubleNode == NULL || result == 1) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    DoubleNode *currentElement;

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
                list->dllwt.tail = newDoubleNode;
                currentElement->next = newDoubleNode;
                list->dllwt.tail->prev = currentElement;
                return 0;
            } else if (type == DLL) {
                currentElement->next = newDoubleNode;
                newDoubleNode->prev = currentElement;
                return 0;
            } else {
                return 1;
            }
        };
        currentElement = currentElement->next;

        counter += 1;
    };

    newDoubleNode->next = currentElement;
    newDoubleNode->prev = currentElement->prev;
    newDoubleNode->next->prev = newDoubleNode;
    newDoubleNode->prev->next = newDoubleNode;
    return 0;
};

// Writes data from popped inedx to void *data argument pointer,
// returns 0 if success, 1 if failure
int doublePopFront(DoubleLinkedListUnion *list, ListType type, void *content) {
    if (type == DLLWT) {
        content = list->dllwt.head->data;
        list->dllwt.head->next->prev = NULL;
        DoubleNode *oldHead = list->dllwt.head;
        list->dllwt.head = list->dllwt.head->next;
        free(oldHead);
    } else if (type == DLL) {
        content = list->dll.head->data;
        list->dll.head->next->prev = NULL;
        DoubleNode *oldHead = list->dll.head;
        list->dll.head = list->dll.head->next;
        free(oldHead);
    } else {
        return 1;
    }

    return 0;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
int doublePopBack(DoubleLinkedListUnion *list, ListType type, void *content) {
    if (type == DLLWT) {
        DoubleNode *oldTail = list->dllwt.tail;
        list->dllwt.tail = list->dllwt.tail->prev;
        list->dllwt.tail->next = NULL;
        content = oldTail->data;
        free(oldTail);
    } else if (type == DLL) {
        DoubleNode *lastDoubleNode = list->dll.head;
        while (lastDoubleNode->next != NULL) {
            lastDoubleNode = lastDoubleNode->next;
        };
        lastDoubleNode->prev->next = NULL;
        content = lastDoubleNode->data;
        free(lastDoubleNode);
    } else {
        fprintf(stderr, "Wrong list type\n");
        content = NULL;
        return 1;
    };
    return 0;
};

// Writes data from popped inedx to void *data argument pointer, returns 0
// if success, 1 if failure
int doublePopIndex(DoubleLinkedListUnion *list, ListType type, int index,
                   void *content) {
    int counter = 0;

    DoubleNode *currentElement = NULL;

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
            DoubleNode *oldTail = list->dllwt.tail;
            list->dllwt.tail = list->dllwt.tail->prev;
            list->dllwt.tail->next = NULL;
            content = oldTail->data;
            free(oldTail);
            return 0;
        } else if (type == DLL) {
            DoubleNode *lastDoubleNode = currentElement;
            lastDoubleNode->prev->next = NULL;
            content = lastDoubleNode->data;
            free(lastDoubleNode);
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
int doubleCompareInt(const void *a, const void *b) {
    return (*(int *)a == *(int *)b);
}

// Function to find an element in the list
// returns index if found, -1 if not found
int doubleFindElement(DoubleLinkedListUnion *list, ListType type,
                      CompareFunc compare, void *content) {
    DoubleNode *current;
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
