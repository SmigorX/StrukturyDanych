#include "double_list.h"

/* Inicjalizacja listy – ustawienie head (oraz tail, jeśli dotyczy) na NULL */
int doubleInitList(DoubleLinkedListUnion *list, ListType type) {
    if (type == DLLWT) {
        list->dllwt.head = NULL;
        list->dllwt.tail = NULL;
    } else {  // DLL
        list->dll.head = NULL;
    }
    return 0;
}

/* Tworzenie nowego węzła – przekazuje adres wskaźnika w node */
int doubleCreateNode(void *data, size_t dataSize, DoubleNode **node) {
    *node = malloc(sizeof(DoubleNode));
    if (*node == NULL) return 1;
    
    (*node)->data = malloc(dataSize);
    if ((*node)->data == NULL) {
        free(*node);
        return 1;
    }
    memcpy((*node)->data, data, dataSize);
    (*node)->next = NULL;
    (*node)->prev = NULL;
    return 0;
}

/* Zwraca true, gdy lista jest pusta */
bool doubleEmpty(DoubleLinkedListUnion *list, ListType type) {
    if (type == DLL) {
        return list->dll.head == NULL;
    } else if (type == DLLWT) {
        return list->dllwt.head == NULL;
    }
    return true;  // domyślnie pusta w razie nieznanego typu
}

/* Dodawanie elementu na początek listy */
void doublePushFront(DoubleLinkedListUnion *list, ListType type, void *data, size_t dataSize) {
    DoubleNode *new_node = NULL;
    if (doubleCreateNode(data, dataSize, &new_node) != 0) {
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
    } else {  // DLL
        new_node->next = list->dll.head;
        if (list->dll.head) {
            list->dll.head->prev = new_node;
        }
        list->dll.head = new_node;
    }
}

/* Dodawanie elementu na koniec listy */
void doublePushBack(DoubleLinkedListUnion *list, ListType type, void *data, size_t dataSize) {
    DoubleNode *new_node = NULL;
    int result = doubleCreateNode(data, dataSize, &new_node);
    if (new_node == NULL || result != 0) {
        fprintf(stderr, "Failed to create new node\n");
        exit(1);
    }

    if (type == DLLWT) {
        if (list->dllwt.tail == NULL) { // lista pusta
            list->dllwt.head = list->dllwt.tail = new_node;
        } else {
            DoubleNode *oldTail = list->dllwt.tail;
            oldTail->next = new_node;
            new_node->prev = oldTail;
            list->dllwt.tail = new_node;
        }
    } else {  // DLL
        if (list->dll.head == NULL) { // lista pusta
            list->dll.head = new_node;
        } else {
            DoubleNode *current = list->dll.head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
            new_node->prev = current;
        }
    }
}

/* Dodawanie elementu pod danym indeksem.
   Jeśli index == 0, to wstawiamy na początku. */
int doublePushIndex(DoubleLinkedListUnion *list, ListType type, int index, void *data, size_t dataSize) {
    if (index < 0) {
        fprintf(stderr, "Index cannot be negative\n");
        return 1;
    }
    if (index == 0) {
        doublePushFront(list, type, data, dataSize);
        return 0;
    }

    DoubleNode *new_node = NULL;
    if (doubleCreateNode(data, dataSize, &new_node) != 0) {
        fprintf(stderr, "Failed to create new node\n");
        return 1;
    }

    DoubleNode *current = (type == DLLWT) ? list->dllwt.head : list->dll.head;
    int counter = 0;
    /* Idziemy do elementu na pozycji index */
    while (current != NULL && counter < index) {
        current = current->next;
        counter++;
    }
    if (counter != index) {
        fprintf(stderr, "Index out of range\n");
        free(new_node->data);
        free(new_node);
        return 1;
    }

    /* Wstawiamy new_node przed current */
    new_node->next = current;
    new_node->prev = current ? current->prev : NULL;
    if (current) {
        if (current->prev) {
            current->prev->next = new_node;
        }
        current->prev = new_node;
    }
    /* Jeśli wstawiliśmy na początku, aktualizujemy head */
    if (new_node->prev == NULL) {
        if (type == DLLWT)
            list->dllwt.head = new_node;
        else
            list->dll.head = new_node;
    }
    return 0;
}

/* Usuwanie elementu z początku listy.
   Jeśli content != NULL, kopiujemy usuwane dane (dataSize bajtów) do content. */
int doublePopFront(DoubleLinkedListUnion *list, ListType type, void *content, size_t dataSize) {
    DoubleNode *to_remove = NULL;
    
    if (type == DLLWT) {
        if (!list->dllwt.head) return 1;
        to_remove = list->dllwt.head;
        list->dllwt.head = to_remove->next;
        if (list->dllwt.head)
            list->dllwt.head->prev = NULL;
        else
            list->dllwt.tail = NULL;
    } else {
        if (!list->dll.head) return 1;
        to_remove = list->dll.head;
        list->dll.head = to_remove->next;
        if (list->dll.head)
            list->dll.head->prev = NULL;
    }

    if (content) {
        memcpy(content, to_remove->data, dataSize);
    }
    free(to_remove->data);
    free(to_remove);
    return 0;
}

/* Usuwanie elementu z końca listy.
   Nowa wersja przyjmuje także dataSize, aby skopiować dane usuwanego elementu. */
int doublePopBack(DoubleLinkedListUnion *list, ListType type, void *content, size_t dataSize) {
    if (type == DLLWT) {
        if (!list->dllwt.tail) return 1;
        DoubleNode *oldTail = list->dllwt.tail;
        list->dllwt.tail = oldTail->prev;
        if (list->dllwt.tail)
            list->dllwt.tail->next = NULL;
        else
            list->dllwt.head = NULL;
        if (content)
            memcpy(content, oldTail->data, dataSize);
        free(oldTail->data);
        free(oldTail);
    } else if (type == DLL) {
        if (!list->dll.head) return 1;
        DoubleNode *current = list->dll.head;
        while (current->next != NULL) {
            current = current->next;
        }
        if (current->prev)
            current->prev->next = NULL;
        else
            list->dll.head = NULL;
        if (content)
            memcpy(content, current->data, dataSize);
        free(current->data);
        free(current);
    } else {
        fprintf(stderr, "Wrong list type\n");
        return 1;
    }
    return 0;
}

/* Usuwanie elementu znajdującego się pod danym indeksem.
   Kopiujemy dane usuwanego elementu (dataSize bajtów) do content, jeśli content != NULL. */
int doublePopIndex(DoubleLinkedListUnion *list, ListType type, int index, void *content, size_t dataSize) {
    if (index < 0) {
        fprintf(stderr, "Index cannot be negative\n");
        return 1;
    }
    DoubleNode *current = (type == DLLWT) ? list->dllwt.head : list->dll.head;
    int counter = 0;
    while (current != NULL && counter < index) {
        current = current->next;
        counter++;
    }
    if (current == NULL) {
        fprintf(stderr, "Index out of range\n");
        return 1;
    }
    /* Usuwamy current z listy */
    if (current->prev)
        current->prev->next = current->next;
    else {  // usuwany jest pierwszy element
        if (type == DLLWT)
            list->dllwt.head = current->next;
        else
            list->dll.head = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    } else {  // usuwany jest ostatni element (dla DLLWT aktualizujemy tail)
        if (type == DLLWT)
            list->dllwt.tail = current->prev;
    }
    if (content) {
        memcpy(content, current->data, dataSize);
    }
    free(current->data);
    free(current);
    return 0;
}

/* Funkcja porównująca liczby całkowite – zwraca 1, jeśli są równe, 0 w przeciwnym przypadku */
int doubleCompareInt(const void *a, const void *b) {
    return (*(int *)a == *(int *)b) ? 1 : 0;
}

/* Wyszukuje element przy użyciu funkcji compare.
   Zwraca indeks pierwszego napotkanego elementu lub -1, jeśli nie znaleziono. */
int doubleFindElement(DoubleLinkedListUnion *list, ListType type, CompareFunc compare, void *content) {
    DoubleNode *current;
    if (type == DLL) {
        current = list->dll.head;
    } else if (type == DLLWT) {
        current = list->dllwt.head;
    } else {
        fprintf(stderr, "Wrong list type\n");
        return -1;
    }
    int index = 0;
    while (current != NULL) {
        if (compare(current->data, content))
            return index;
        current = current->next;
        index++;
    }
    return -1;
}

/* Funkcja wypisująca pojedynczy element – przykładowo dla int */
//void printInt(const void *content) {
//    printf("%d ", *(int *)content);
//}

/* Funkcja wypisująca zawartość listy.
   Parametr type wskazuje, z którego wariantu listy korzystamy. */
void doublePrintList(DoubleLinkedListUnion *list, ListType type, void (*printFunc)(const void *)) {
    DoubleNode *current = (type == DLLWT) ? list->dllwt.head : list->dll.head;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
    printf("\n");
}

