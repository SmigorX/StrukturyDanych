#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Dynamic_Array/dynamic_array.h"
#include "Single_Linked_List/single_list.h"
#include "Double_Linked_List/double_list.h"

#define TRIALS 100
#define ELEMENT_COUNTS {100, 1000, 10000}

// Prosta funkcja porównująca inty (dla dynamic array i single list)
// DynamicArray search function
int dynamic_array_find(DynamicArray *arr, void *key, int (*cmp)(const void*, const void*)) {
    for (int i = 0; i < arr->currSize; i++) {
        void *element = (char*)arr->A + i * arr->elementSize;
        if (cmp(element, key) == 0) return i;
    }
    return -1;
}

void test_dynamic_array(FILE *csv, int element_count) {
    DynamicArray da;
    initArray(&da, sizeof(int));
    for (int i = 0; i < element_count; i++) insertAtEnd(&da, &i);

    int x = -1;
    int mid_idx = element_count / 2;
    clock_t start, end;
    double time;

    // Insert beginning
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        insertAtMiddle(&da, 0, &x);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        deleteAtMiddle(&da, 0);
    }
    fprintf(csv, "DynamicArray,Insert,Beginning,%f,%d\n", time/TRIALS, element_count);

    // Insert middle
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        insertAtMiddle(&da, mid_idx, &x);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        deleteAtMiddle(&da, mid_idx);
    }
    fprintf(csv, "DynamicArray,Insert,Middle,%f,%d\n", time/TRIALS, element_count);

    // Insert end
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        insertAtEnd(&da, &x);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        deleteAtEnd(&da);
    }
    fprintf(csv, "DynamicArray,Insert,End,%f,%d\n", time/TRIALS, element_count);

    // Delete beginning
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        deleteAtMiddle(&da, 0);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        insertAtMiddle(&da, 0, &x);
    }
    fprintf(csv, "DynamicArray,Delete,Beginning,%f,%d\n", time/TRIALS, element_count);

    // Delete middle
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        deleteAtMiddle(&da, mid_idx);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        insertAtMiddle(&da, mid_idx, &x);
    }
    fprintf(csv, "DynamicArray,Delete,Middle,%f,%d\n", time/TRIALS, element_count);

    // Delete end
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        deleteAtEnd(&da);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        insertAtEnd(&da, &x);
    }
    fprintf(csv, "DynamicArray,Delete,End,%f,%d\n", time/TRIALS, element_count);

    // Search
    int key = element_count;
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        dynamic_array_find(&da, &key, compareInt);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "DynamicArray,Search,N/A,%f,%d\n", time/TRIALS, element_count);

    free(da.A);
}

void test_single_list(FILE *csv, int element_count) {
    LinkedList list;
    initList(&list);
    for (int i = 0; i < element_count; i++) pushBack(&list, &i, sizeof(int));

    int x = -1;
    int mid_idx = element_count / 2;
    clock_t start, end;
    double time;

    // Insert beginning
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        pushFront(&list, &x, sizeof(int));
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        popFront(&list);
    }
    fprintf(csv, "SingleLinkedList,Insert,Beginning,%f,%d\n", time/TRIALS, element_count);

    // Insert middle
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        pushIndex(&list, &x, sizeof(int), mid_idx);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        popIndex(&list, mid_idx);
    }
    fprintf(csv, "SingleLinkedList,Insert,Middle,%f,%d\n", time/TRIALS, element_count);

    // Insert end
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        pushBack(&list, &x, sizeof(int));
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        popBack(&list);
    }
    fprintf(csv, "SingleLinkedList,Insert,End,%f,%d\n", time/TRIALS, element_count);

    // Delete beginning
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        pushFront(&list, &x, sizeof(int));
        start = clock();
        popFront(&list);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "SingleLinkedList,Delete,Beginning,%f,%d\n", time/TRIALS, element_count);

    // Delete middle
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        pushIndex(&list, &x, sizeof(int), mid_idx);
        start = clock();
        popIndex(&list, mid_idx);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "SingleLinkedList,Delete,Middle,%f,%d\n", time/TRIALS, element_count);

    // Delete end
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        pushBack(&list, &x, sizeof(int));
        start = clock();
        popBack(&list);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "SingleLinkedList,Delete,End,%f,%d\n", time/TRIALS, element_count);

    // Search
    int key = element_count;
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        find(&list, &key, compareInt);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "SingleLinkedList,Search,N/A,%f,%d\n", time/TRIALS, element_count);

    while (!empty(&list)) popFront(&list);
}

// Dla double_list.h compareInt musi mieć typ int (*)(const void*, const void*)
// Dla doubleFindElement, compare powinno zwracać != 0 jeśli równe
int double_compareInt(const void *a, const void *b) {
    return (*(const int *)a == *(const int *)b);
}

void test_double_list(FILE *csv, int element_count, ListType type, const char *name) {
    DoubleLinkedListUnion list;
    doubleInitList(&list, type);
    for (int i = 0; i < element_count; i++) doublePushBack(&list, type, &i, sizeof(int));

    int x = -1, dummy;
    int mid_idx = element_count / 2;
    clock_t start, end;
    double time;

    // Insert beginning
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        doublePushFront(&list, type, &x, sizeof(int));
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        doublePopFront(&list, type, &dummy);
    }
    fprintf(csv, "%s,Insert,Beginning,%f,%d\n", name, time/TRIALS, element_count);

    // Insert middle
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        doublePushIndex(&list, type, mid_idx, &x, sizeof(int));
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        doublePopIndex(&list, type, mid_idx, &dummy);
    }
    fprintf(csv, "%s,Insert,Middle,%f,%d\n", name, time/TRIALS, element_count);

    // Insert end
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        doublePushBack(&list, type, &x, sizeof(int));
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
        doublePopBack(&list, type, &dummy);
    }
    fprintf(csv, "%s,Insert,End,%f,%d\n", name, time/TRIALS, element_count);

    // Delete beginning
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        doublePushFront(&list, type, &x, sizeof(int));
        start = clock();
        doublePopFront(&list, type, &dummy);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "%s,Delete,Beginning,%f,%d\n", name, time/TRIALS, element_count);

    // Delete middle
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        doublePushIndex(&list, type, mid_idx, &x, sizeof(int));
        start = clock();
        doublePopIndex(&list, type, mid_idx, &dummy);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "%s,Delete,Middle,%f,%d\n", name, time/TRIALS, element_count);

    // Delete end
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        doublePushBack(&list, type, &x, sizeof(int));
        start = clock();
        doublePopBack(&list, type, &dummy);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "%s,Delete,End,%f,%d\n", name, time/TRIALS, element_count);

    // Search
    int key = element_count;
    time = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = clock();
        doubleFindElement(&list, type, double_compareInt, &key);
        end = clock();
        time += (double)(end - start) / CLOCKS_PER_SEC;
    }
    fprintf(csv, "%s,Search,N/A,%f,%d\n", name, time/TRIALS, element_count);

    while (!doubleEmpty(&list, type)) doublePopFront(&list, type, &dummy);
}

int main() {
    FILE *csv = fopen("results.csv", "w");
    if (!csv) {
        fprintf(stderr, "Failed to open results.csv for writing.\n");
        return 1;
    }
    fprintf(csv, "Structure,Operation,Position,Time,ElementCount\n");
    int counts[] = ELEMENT_COUNTS;
    for (int i = 0; i < (int)(sizeof(counts)/sizeof(counts[0])); i++) {
        int ec = counts[i];
        test_dynamic_array(csv, ec);
        test_single_list(csv, ec);
        test_double_list(csv, ec, DLL, "DoubleLinkedList");
        test_double_list(csv, ec, DLLWT, "DoubleLinkedListWithTail");
    }
    fclose(csv);
    return 0;
}
