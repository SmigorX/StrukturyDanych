
#include "HashTable.h"
#include "HashingFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_CASES 5
#define INITIAL_CAPACITY 16
#define OPTIMISTIC_SIZE 10000
#define AVERAGE_SIZE 10000
#define PESSIMISTIC_SIZE 10000

double get_time() { return (double)clock() / CLOCKS_PER_SEC; }

void generate_random_string(char *buffer, size_t length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buffer[length] = '\0';
}

void test_performance(HashTable *table, const char *test_name, char **keys,
                      size_t size) {
    printf("\nTest: %s (rozmiar: %zu)\n", test_name, size);

    // Reset collision counter
    table->collisions = 0;

    // Insert test
    double start = get_time();
    for (size_t i = 0; i < size; i++) {
        ht_insert(table, keys[i], (void *)(long)i);
    }
    double end = get_time();
    printf("Dodawanie: %.6f sekund\n", end - start);
    printf("Rozmiar: %zu, Pojemność: %zu, Wsp. obciążenia: %.2f\n", table->size,
           table->capacity, (float)table->size / table->capacity);
    printf("Kolizje: %zu (%.2f%%)\n", table->collisions,
           (float)table->collisions / size * 100);

    // Find max bucket length
    size_t max_len = 0;
    for (size_t i = 0; i < table->capacity; i++) {
        size_t len = 0;
        HashNode *node = table->buckets[i];
        while (node) {
            len++;
            node = node->next;
        }
        if (len > max_len)
            max_len = len;
    }
    printf("Maks. długość bucketu: %zu\n", max_len);

    // Remove test
    start = get_time();
    for (size_t i = 0; i < size; i++) {
        ht_remove(table, keys[i]);
    }
    end = get_time();
    printf("Usuwanie: %.6f sekund\n", end - start);
    printf("Rozmiar po usunięciu: %zu\n", table->size);
}

int main() {
    srand(time(NULL));

    struct {
        const char *name;
        size_t (*func)(const char *);
    } hash_functions[] = {
        {"SDBM", sdbm},
        {"FNV1a", fnv1a},
        {"Jenkins", jenkins},
        {"CRC32", crc32},
        {"Adler32", adler32},
        {"CONSTANT", constant_hash} // For pessimistic testing
    };

    // Prepare test data
    printf("Przygotowywanie danych testowych...\n");

    // 1. Optimistic case - unique random keys
    char **optimistic_keys = malloc(OPTIMISTIC_SIZE * sizeof(char *));
    for (size_t i = 0; i < OPTIMISTIC_SIZE; i++) {
        optimistic_keys[i] = malloc(21);
        generate_random_string(optimistic_keys[i], 20);
    }

    // 2. Average case - mix of unique and duplicate keys
    char **average_keys = malloc(AVERAGE_SIZE * sizeof(char *));
    for (size_t i = 0; i < AVERAGE_SIZE; i++) {
        average_keys[i] = malloc(21);
        if (i > 0 && i % 100 == 0) {
            strcpy(average_keys[i],
                   average_keys[i - 1]); // Duplicate every 100th key
        } else {
            generate_random_string(average_keys[i], 20);
        }
    }

    // 3. Pessimistic case - all keys identical
    char **pessimistic_keys = malloc(PESSIMISTIC_SIZE * sizeof(char *));
    for (size_t i = 0; i < PESSIMISTIC_SIZE; i++) {
        pessimistic_keys[i] = strdup("identical_key"); // All keys same
    }

    // Run tests
    for (size_t i = 0; i < sizeof(hash_functions) / sizeof(hash_functions[0]);
         i++) {
        printf("\n=== Testowanie funkcji haszującej: %s ===\n",
               hash_functions[i].name);

        // Optimistic test
        HashTable *opt = ht_create(INITIAL_CAPACITY, hash_functions[i].func);
        test_performance(opt, "Przypadek optymistyczny", optimistic_keys,
                         OPTIMISTIC_SIZE);
        ht_destroy(opt);

        // Average test
        HashTable *avg = ht_create(INITIAL_CAPACITY, hash_functions[i].func);
        test_performance(avg, "Przypadek średni", average_keys, AVERAGE_SIZE);
        ht_destroy(avg);

        // Pessimistic test
        HashTable *pes = ht_create(INITIAL_CAPACITY, hash_functions[i].func);
        test_performance(pes, "Przypadek pesymistyczny", pessimistic_keys,
                         PESSIMISTIC_SIZE);
        ht_destroy(pes);
    }

    // Cleanup
    for (size_t i = 0; i < OPTIMISTIC_SIZE; i++)
        free(optimistic_keys[i]);
    for (size_t i = 0; i < AVERAGE_SIZE; i++)
        free(average_keys[i]);
    for (size_t i = 0; i < PESSIMISTIC_SIZE; i++)
        free(pessimistic_keys[i]);
    free(optimistic_keys);
    free(average_keys);
    free(pessimistic_keys);

    return 0;
}
