#include "Double_Linked_List/double_list.h"
#include "Dynamic_Array/dynamic_array.h"
#include "Single_Linked_List/single_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 100
#define GROUP_SIZE 1000
#define ELEMENT_COUNTS {100, 500, 1000, 5000, 10000}

/* Funkcja pomocnicza zwracająca czas w sekundach jako double */
double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

/* ----- Testy dla Dynamic Array ----- */
int dynamic_array_find(DynamicArray *arr, void *key,
                       int (*cmp)(const void *, const void *)) {
    for (int i = 0; i < arr->currSize; i++) {
        void *element = (char *)arr->A + i * arr->elementSize;
        if (cmp(element, key) == 0)
            return i;
    }
    return -1;
}

void test_dynamic_array(FILE *csv, int element_count) {
    DynamicArray da;
    initArray(&da, sizeof(int));
    for (int i = 0; i < element_count; i++) {
        insertAtEnd(&da, &i);
    }

    int x = -1;
    int mid_idx = element_count / 2;
    double time_accum;
    double start, end;

    /* Operacje są grupowane – wykonujemy GROUP_SIZE operacji, aby zmierzyć
     * łączny czas i podzielić przez GROUP_SIZE */
    // Insert Beginning
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtMiddle(&da, 0, &x);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            int error = deleteAtMiddle(&da, 0);
            if (error != 0) {
                fprintf(stderr, "[ERROR] (DynamicArray, insertAtBeginning) "
                                "Coulnd't delete at beginning");
            };
        }
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Insert,Beginning,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Insert Middle
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtMiddle(&da, mid_idx, &x);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            int error = deleteAtMiddle(&da, mid_idx);
            if (error != 0) {
                fprintf(stderr, "[ERROR] (DynamicArray, insertAtMiddle) "
                                "Coulnd't delete at middle");
            };
        }
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Insert,Middle,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Insert End
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtEnd(&da, &x);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            int error = deleteAtEnd(&da);
            if (error != 0) {
            }
        }
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Insert,End,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete Beginning
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        // Przygotowanie – wstawiamy element, który potem usuwamy
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtMiddle(&da, 0, &x);
        }
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            int error = deleteAtMiddle(&da, 0);
            if (error != 0) {
                fprintf(stderr, "[ERROR] (DynamicArray, deleteAtBeginning) "
                                "Coulnd't delete beginning\n");
            };
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtMiddle(&da, 0, &x);
        }
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Delete,Beginning,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete Middle
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtMiddle(&da, mid_idx, &x);
        }
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            int error = deleteAtMiddle(&da, mid_idx);
            if (error != 0) {
                printf("[Error] (DynamicArray, deleteAtMiddle) whilst deleting "
                       "in the middle of dynamic "
                       "array, element: %d\n",
                       i);
            }
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtMiddle(&da, mid_idx, &x);
        }
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Delete,Middle,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete End
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        insertAtEnd(&da, &x);
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            deleteAtEnd(&da);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            insertAtEnd(&da, &x);
        }
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Delete,End,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Search
    int key = element_count; // element, którego nie ma
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            dynamic_array_find(&da, &key, compareInt);
        }
        end = get_time_in_seconds();
        time_accum += (end - start);
    }
    fprintf(csv, "DynamicArray,Search,N/A,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    free(da.A);
}

/* ----- Testy dla Single Linked List ----- */
void test_single_list(FILE *csv, int element_count) {
    LinkedList list;
    initList(&list);
    for (int i = 0; i < element_count; i++) {
        pushBack(&list, &i, sizeof(int));
    }

    int x = -1;
    int mid_idx = element_count / 2;
    double time_accum = 0;
    double start, end;

    // Insert Beginning
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushFront(&list, &x, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            popFront(&list);
        }
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Insert,Beginning,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Insert Middle
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushIndex(&list, &x, sizeof(int), mid_idx);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            popIndex(&list, mid_idx);
        }
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Insert,Middle,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Insert End
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushBack(&list, &x, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            popBack(&list);
        }
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Insert,End,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete Beginning
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushFront(&list, &x, sizeof(int));
        }
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            popFront(&list);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushFront(&list, &x, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Delete,Beginning,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete Middle
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushIndex(&list, &x, sizeof(int), mid_idx);
        }
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            int result = popIndex(&list, mid_idx);
            if (result != 0) {
                fprintf(stderr, "[ERROR] (SingleList, DeleteMiddle)");
            }
        }
        end = get_time_in_seconds();
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Delete,Middle,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete End
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        pushBack(&list, &x, sizeof(int));
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            popBack(&list);
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            pushBack(&list, &x, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Delete,End,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Search
    int key = element_count;
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            find(&list, &key, compareInt);
        }
        end = get_time_in_seconds();
        time_accum += (end - start);
    }
    fprintf(csv, "SingleLinkedList,Search,N/A,%f us,%d\n",
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    while (!empty(&list)) {
        popFront(&list);
    }
}

/* ----- Testy dla Double Linked List ----- */

/* Funkcja porównawcza dla int (zwraca 1, gdy równe) */
int double_compareInt(const void *a, const void *b) {
    return (*(const int *)a == *(const int *)b) ? 1 : 0;
}

void test_double_list(FILE *csv, int element_count, ListType type,
                      const char *name) {
    DoubleLinkedListUnion list;
    doubleInitList(&list, type);
    for (int i = 0; i < element_count; i++) {
        doublePushBack(&list, type, &i, sizeof(int));
    }

    int x = -1, dummy;
    int mid_idx = element_count / 2;
    double time_accum = 0;
    double start, end;

    // Insert Beginning
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePushFront(&list, type, &x, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePopFront(&list, type, &dummy, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Insert,Beginning,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Insert Middle
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePushIndex(&list, type, mid_idx, &x, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePopIndex(&list, type, mid_idx, &dummy, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Insert,Middle,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Insert End
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePushBack(&list, type, &x, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePopBack(&list, type, &dummy, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Insert,End,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete Beginning
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        doublePushFront(&list, type, &x, sizeof(int));
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePopFront(&list, type, &dummy, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePushFront(&list, type, &x, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Delete,Beginning,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete Middle
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        for (int i = 0; i < GROUP_SIZE; i++) {
            int error = doublePushIndex(&list, type, mid_idx, &x, sizeof(int));
            if (error != 0) {
                fprintf(
                    stderr,
                    "[ERROR] (DoubleLinkedList, DeleteMiddle) Couldn't delete "
                    "at middle");
            };
        };
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePopIndex(&list, type, mid_idx, &dummy, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePushIndex(&list, type, mid_idx, &x, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Delete,Middle,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Delete End
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        doublePushBack(&list, type, &x, sizeof(int));
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePopBack(&list, type, &dummy, sizeof(int));
        }
        end = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doublePushBack(&list, type, &x, sizeof(int));
        }
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Delete,End,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    // Search
    int key = element_count;
    time_accum = 0;
    for (int t = 0; t < TRIALS; t++) {
        start = get_time_in_seconds();
        for (int i = 0; i < GROUP_SIZE; i++) {
            doubleFindElement(&list, type, double_compareInt, &key);
        }
        end = get_time_in_seconds();
        time_accum += (end - start);
    }
    fprintf(csv, "%s,Search,N/A,%f us,%d\n", name,
            (time_accum / (TRIALS * GROUP_SIZE)) * 1e6, element_count);

    while (!doubleEmpty(&list, type)) {
        doublePopFront(&list, type, &dummy, sizeof(int));
    }
}

/* ----- Funkcja main ----- */
int main() {
    FILE *csv = fopen("results.csv", "w");
    if (!csv) {
        fprintf(stderr, "Failed to open results.csv for writing.\n");
        return 1;
    }
    fprintf(csv, "Structure,Operation,Position,Time(us),ElementCount\n");
    int counts[] = ELEMENT_COUNTS;
    int count_len = sizeof(counts) / sizeof(counts[0]);

    for (int i = 0; i < count_len; i++) {
        int ec = counts[i];
        test_dynamic_array(csv, ec);
        test_single_list(csv, ec);
        test_double_list(csv, ec, DLL, "DoubleLinkedList");
        test_double_list(csv, ec, DLLWT, "DoubleLinkedListWithTail");
    }

    fclose(csv);
    return 0;
}
