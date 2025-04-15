#include "double_list.h"

// returns 0 if successful, 1 if failed
// Inicjalizacja listy
int doubleInitList(DoubleLinkedListUnion *list, ListType type) {
    if (type == DLLWT) {
        list->dllwt.head = NULL;
        list->dllwt.tail = NULL;
    } else {
        list->dll.head = NULL;
    }
    return 0;
}

// Tworzenie nowego węzła (poprawione zarządzanie pamięcią)
int doubleCreateNode(void *data, size_t dataSize, DoubleNode *node) {
    DoubleNode **real_node = (DoubleNode **)node;
    *real_node = malloc(sizeof(DoubleNode));
    if (!*real_node) return 1;
    
    (*real_node)->data = malloc(dataSize);
    if (!(*real_node)->data) {
        free(*real_node);
        return 1;
    }
    
    memcpy((*real_node)->data, data, dataSize);
    (*real_node)->next = NULL;
    (*real_node)->prev = NULL;
    return 0;
}
// Returns 1 if empty
const bool doubleEmpty(DoubleLinkedListUnion *list, ListType type) {
    if (type == DLL) {
        return list->dll.head == NULL;
    } else if (type == DLLWT) {
        return list->dllwt.head == NULL;
    }
    return NULL;
}

// Dodawanie na początek listy
void doublePushFront(DoubleLinkedListUnion *list, ListType type, void *data, 
                    size_t dataSize) {
    DoubleNode *new_node;
    if (doubleCreateNode(data, dataSize, (DoubleNode *)&new_node) != 0) {
        fprintf(stderr, "Failed to create node\n");
        return;
    }

    if (type == DLLWT) {
        new_node->next = list->dllwt.head;
        if (list->dllwt.head) {
            list->dllwt.head->prev = new_node;
        }
        list->dllwt.head = new_node;
        if (!list->dllwt.tail) {
            list->dllwt.tail = new_node;
        }
    } else {
        new_node->next = list->dll.head;
        if (list->dll.head) {
            list->dll.head->prev = new_node;
        }
        list->dll.head = new_node;
    }
}
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
    DoubleNode *to_remove = NULL;
    
    if (type == DLLWT) {
        if (!list->dllwt.head) return 1;
        to_remove = list->dllwt.head;
        list->dllwt.head = to_remove->next;
        if (list->dllwt.head) {
            list->dllwt.head->prev = NULL;
        } else {
            list->dllwt.tail = NULL;
        }
    } else {
        if (!list->dll.head) return 1;
        to_remove = list->dll.head;
        list->dll.head = to_remove->next;
        if (list->dll.head) {
            list->dll.head->prev = NULL;
        }
    }

    if (content) {
        memcpy(content, to_remove->data, sizeof(to_remove->data));
    }
    free(to_remove->data);
    free(to_remove);
    return 0;
}
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
    return 0;
}

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
