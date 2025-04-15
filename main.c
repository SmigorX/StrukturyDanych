#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Single_Linked_List/single_list.h"
#include "Double_Linked_List/double_list.h"
#include "Dynamic_Array/dynamic_array.h"

// Pomocnicze funkcje do obsługi danych
int* create_int(int value) {
    int* data = malloc(sizeof(int));
    *data = value;
    return data;
}

// Test dla listy jednokierunkowej
void test_single_linked_list(int n) {
    LinkedList list;
    initList(&list);
    clock_t start, end;

    // Wstawianie na początek
    start = clock();
    for (int i = 0; i < n; i++) {
        pushFront(&list, &i, sizeof(int));
    }
    end = clock();
    printf("[Singly] Wstawienie %d (front): %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Dostęp sekwencyjny
    start = clock();
    Node* current = list.head;
    while (current != NULL) {
        int val = *(int*)current->data;
        current = current->next;
    }
    end = clock();
    printf("[Singly] Przejście %d elementów: %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Usuwanie z początku
    start = clock();
    for (int i = 0; i < n; i++) {
        popFront(&list);
    }
    end = clock();
    printf("[Singly] Usunięcie %d (front): %.6f s\n\n", n, (double)(end - start)/CLOCKS_PER_SEC);
}

// Test dla listy dwukierunkowej
void test_double_linked_list(int n) {
    DoubleLinkedListUnion list;
    doubleInitList(&list, DLL);
    clock_t start, end;

    // Wstawianie na początek
    start = clock();
    for (int i = 0; i < n; i++) {
        doublePushFront(&list, DLL, &i, sizeof(int));
    }
    end = clock();
    printf("[Doubly] Wstawienie %d (front): %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Dostęp sekwencyjny
    start = clock();
    DoubleNode* current = list.dll.head;
    while (current != NULL) {
        int val = *(int*)current->data;
        current = current->next;
    }
    end = clock();
    printf("[Doubly] Przejście %d elementów: %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Usuwanie z początku
    start = clock();
    for (int i = 0; i < n; i++) {
        doublePopFront(&list, DLL, NULL);
    }
    end = clock();
    printf("[Doubly] Usunięcie %d (front): %.6f s\n\n", n, (double)(end - start)/CLOCKS_PER_SEC);
}

// Test dla tablicy dynamicznej
void test_dynamic_array(int n) {
    DynamicArray arr;
    initArray(&arr, sizeof(int));
    clock_t start, end;

    // Wstawianie na koniec
    start = clock();
    for (int i = 0; i < n; i++) {
        insertAtEnd(&arr, &i);
    }
    end = clock();
    printf("[Dynamic] Wstawienie %d (back): %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Dostęp bezpośredni
    start = clock();
    for (int i = 0; i < n; i++) {
        int val = ((int*)arr.A)[i];
    }
    end = clock();
    printf("[Dynamic] Dostęp do %d elementów: %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Wstawianie na początek
    start = clock();
    for (int i = 0; i < n; i++) {
        insertAtMiddle(&arr, 0, &i);
    }
    end = clock();
    printf("[Dynamic] Wstawienie %d (front): %.6f s\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    // Usuwanie z końca
    start = clock();
    for (int i = 0; i < n; i++) {
        deleteAtEnd(&arr);
    }
    end = clock();
    printf("[Dynamic] Usunięcie %d (back): %.6f s\n\n", n, (double)(end - start)/CLOCKS_PER_SEC);

    free(arr.A);
}

int main() {
    int test_sizes[] = {1000, 10000, 50000};
    const int num_sizes = sizeof(test_sizes)/sizeof(test_sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int n = test_sizes[i];
        printf("\n===== Test dla n = %d =====\n", n);
        
        printf("\n-- Lista jednokierunkowa --\n");
        test_single_linked_list(n);
        
        printf("\n-- Lista dwukierunkowa --\n");
        test_double_linked_list(n);
        
        printf("\n-- Tablica dynamiczna --\n");
        test_dynamic_array(n);
    }

    return 0;
}
