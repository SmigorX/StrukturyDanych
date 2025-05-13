#include "array_queue.h"
#include "common.h"
#include "heap_queue.h"
#include "list_queue.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

/* How many times we run the test suite to get averages */
#define TRIALS 100
/* How many times we repeat the action to get measurable results */
#define BATCH 1000
/* How many elements we add/remove */
static const int ELEMENT_COUNTS[] = {100, 500, 1000, 5000, 10000};
static const int NUM_COUNTS =
    sizeof(ELEMENT_COUNTS) / sizeof(ELEMENT_COUNTS[0]);

void array_tests() {
    // Seed the random number generator
    srand(time(NULL));

    const char *scenarios[] = {"Optimistic", "Average", "Pessimistic"};

    // For each array size
    for (int i = 0; i < NUM_COUNTS; i++) {
        int count = ELEMENT_COUNTS[i];

        // Test each scenario
        for (int scenario = 0; scenario < 3; scenario++) {
            double insert_time = 0.0;
            double peek_time = 0.0;
            double pop_time = 0.0;
            double change_priority_time = 0.0;

            // Test BATCH times for averaging
            for (int batch = 0; batch < BATCH; batch++) {
                Array_queue queue = {0};
                clock_t start, end;

                // 1. INSERTION TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    Element e;
                    switch (scenario) {
                    case 0: // Optimistic (increasing priority)
                        e = (Element){k, k};
                        break;
                    case 1: // Average (random)
                        e = (Element){rand(), rand() % 1000};
                        break;
                    case 2: // Pessimistic (decreasing priority)
                        e = (Element){k, count - k};
                        break;
                    }
                    array_insert(&queue, e);
                }
                end = clock();
                insert_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 2. PEEK TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    Element e = array_peek(&queue);
                    (void)e; // Prevent unused warning
                }
                end = clock();
                peek_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 3. PRIORITY CHANGE TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    int new_priority;
                    switch (scenario) {
                    case 0:
                        new_priority = k / 2;
                        break; // Improve priority
                    case 1:
                        new_priority = rand() % 1000;
                        break;
                    case 2:
                        new_priority = count + k;
                        break; // Worsen priority
                    }
                    array_change_priority(&queue, k, new_priority);
                }
                end = clock();
                change_priority_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 4. POP TEST
                start = clock();
                while (queue.size > 0) {
                    Element e = array_pop(&queue);
                    (void)e; // Prevent unused warning
                }
                end = clock();
                pop_time += (double)(end - start) / CLOCKS_PER_SEC;
            }

            // Print results for this scenario
            printf("Array %s (%d elements):\n", scenarios[scenario], count);
            printf("  Insert:          %.6f sec\n", insert_time / BATCH);
            printf("  Peek:            %.6f sec\n", peek_time / BATCH);
            printf("  Change priority: %.6f sec\n",
                   change_priority_time / BATCH);
            printf("  Pop:             %.6f sec\n", pop_time / BATCH);
            printf("---------------------------------\n");
        }
    }
}

void heap_tests() {
    // Seed the random number generator
    srand(time(NULL));

    const char *scenarios[] = {"Optimistic", "Average", "Pessimistic"};

    // For each heap size
    for (int i = 0; i < NUM_COUNTS; i++) {
        int count = ELEMENT_COUNTS[i];

        // Test each scenario
        for (int scenario = 0; scenario < 3; scenario++) {
            double insert_time = 0.0;
            double peek_time = 0.0;
            double pop_time = 0.0;
            double change_priority_time = 0.0;

            // Test BATCH times for averaging
            for (int batch = 0; batch < BATCH; batch++) {
                Heap_queue queue = {0};
                clock_t start, end;

                // 1. INSERTION TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    Element e;
                    switch (scenario) {
                    case 0: // Optimistic (increasing priority)
                        e = (Element){k, k};
                        break;
                    case 1: // Average (random)
                        e = (Element){rand(), rand() % 1000};
                        break;
                    case 2: // Pessimistic (decreasing priority)
                        e = (Element){k, count - k};
                        break;
                    }
                    heap_insert(&queue, e);
                }
                end = clock();
                insert_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 2. PEEK TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    Element e = heap_peek(&queue);
                    (void)e; // Prevent unused warning
                }
                end = clock();
                peek_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 3. PRIORITY CHANGE TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    int new_priority;
                    switch (scenario) {
                    case 0:
                        new_priority = k / 2;
                        break; // Improve priority
                    case 1:
                        new_priority = rand() % 1000;
                        break;
                    case 2:
                        new_priority = count + k;
                        break; // Worsen priority
                    }
                    heap_change_priority(&queue, k, new_priority);
                }
                end = clock();
                change_priority_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 4. POP TEST
                start = clock();
                while (queue.size > 0) {
                    Element e = heap_pop(&queue);
                    (void)e; // Prevent unused warning
                }
                end = clock();
                pop_time += (double)(end - start) / CLOCKS_PER_SEC;
            }

            // Print results for this scenario
            printf("Heap %s (%d elements):\n", scenarios[scenario], count);
            printf("  Insert:          %.6f sec\n", insert_time / BATCH);
            printf("  Peek:            %.6f sec\n", peek_time / BATCH);
            printf("  Change priority: %.6f sec\n",
                   change_priority_time / BATCH);
            printf("  Pop:             %.6f sec\n", pop_time / BATCH);
            printf("---------------------------------\n");
        }
    }
}

void list_test() {
    // Seed the random number generator
    srand(time(NULL));

    const char *scenarios[] = {"Optimistic", "Average", "Pessimistic"};

    // For each list size
    for (int i = 0; i < NUM_COUNTS; i++) {
        int count = ELEMENT_COUNTS[i];

        // Test each scenario
        for (int scenario = 0; scenario < 3; scenario++) {
            double insert_time = 0.0;
            double peek_time = 0.0;
            double pop_time = 0.0;
            double change_priority_time = 0.0;

            // Test BATCH times for averaging
            for (int batch = 0; batch < BATCH; batch++) {
                List_queue queue = {0};
                clock_t start, end;

                // 1. INSERTION TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    Element e;
                    switch (scenario) {
                    case 0: // Optimistic (increasing priority)
                        e = (Element){k, k};
                        break;
                    case 1: // Average (random)
                        e = (Element){rand(), rand() % 1000};
                        break;
                    case 2: // Pessimistic (decreasing priority)
                        e = (Element){k, count - k};
                        break;
                    }
                    list_insert(&queue, e);
                }
                end = clock();
                insert_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 2. PEEK TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    Element e = list_peek(&queue);
                    (void)e; // Prevent unused warning
                }
                end = clock();
                peek_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 3. PRIORITY CHANGE TEST
                start = clock();
                for (int k = 0; k < count; k++) {
                    int new_priority;
                    switch (scenario) {
                    case 0:
                        new_priority = k / 2;
                        break; // Improve priority
                    case 1:
                        new_priority = rand() % 1000;
                        break;
                    case 2:
                        new_priority = count + k;
                        break; // Worsen priority
                    }
                    list_change_priority(&queue, k, new_priority);
                }
                end = clock();
                change_priority_time += (double)(end - start) / CLOCKS_PER_SEC;

                // 4. POP TEST
                start = clock();
                while (queue.size > 0) {
                    Element e = list_pop(&queue);
                    (void)e; // Prevent unused warning
                }
                end = clock();
                pop_time += (double)(end - start) / CLOCKS_PER_SEC;
            }

            // Print results for this scenario
            printf("List %s (%d elements):\n", scenarios[scenario], count);
            printf("  Insert:          %.6f sec\n", insert_time / BATCH);
            printf("  Peek:            %.6f sec\n", peek_time / BATCH);
            printf("  Change priority: %.6f sec\n",
                   change_priority_time / BATCH);
            printf("  Pop:             %.6f sec\n", pop_time / BATCH);
            printf("---------------------------------\n");
        }
    }
}

int main() {
    array_tests();
    heap_tests();
    list_test();
}
