#include "HashTable.h"
#include "hashing_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_CASES 5
#define INITIAL_CAPACITY 16
#define OPTIMISTIC_SIZE 1000
#define AVERAGE_SIZE 1000
#define PESSIMISTIC_SIZE 1000

// Funkcje pomocnicze
double get_time() { return (double)clock() / CLOCKS_PER_SEC; }

void generate_random_string(char *buffer, size_t length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buffer[length] = '\0';
}

// Testy wydajnościowe
void test_performance(HashTable *table, const char *test_name, char **keys,
                      size_t size) {
    printf("\nTest: %s (rozmiar: %zu)\n", test_name, size);

    // Test dodawania
    double start = get_time();
    for (size_t i = 0; i < size; i++) {
        ht_insert(table, keys[i], (void *)(long)i);
    }
    double end = get_time();
    printf("Dodawanie: %.6f sekund\n", end - start);
    printf("Rozmiar: %zu, Pojemność: %zu, Współczynnik obciążenia: %.2f\n",
           table->size, table->capacity, (float)table->size / table->capacity);

    // Test usuwania
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

    // Lista funkcji haszujących do testów
    struct {
        const char *name;
        size_t (*func)(char *);
    } hash_functions[] = {{"SDBM", sdbm},
                          {"FNV1a", fnv1a},
                          {"Jenkins", jenkins},
                          {"CRC32", crc32},
                          {"Adler32", adler32}};

    // Przygotowanie danych testowych
    printf("Przygotowywanie danych testowych...\n");

    // 1. Przypadek optymistyczny - unikalne losowe klucze
    char **optimistic_keys = malloc(OPTIMISTIC_SIZE * sizeof(char *));
    for (size_t i = 0; i < OPTIMISTIC_SIZE; i++) {
        optimistic_keys[i] = malloc(21);
        generate_random_string(optimistic_keys[i], 20);
    }

    // 2. Przypadek średni - mieszanka unikalnych i częściowo powtarzających się
    // kluczy
    char **average_keys = malloc(AVERAGE_SIZE * sizeof(char *));
    for (size_t i = 0; i < AVERAGE_SIZE; i++) {
        average_keys[i] = malloc(21);
        if (i % 10 == 0 && i > 0) {
            // Co 10-ty klucz powtarza się
            strcpy(average_keys[i], average_keys[i - 1]);
        } else {
            generate_random_string(average_keys[i], 20);
        }
    }

    // 3. Przypadek pesymistyczny - wszystkie klucze mają ten sam hash
    char **pessimistic_keys = malloc(PESSIMISTIC_SIZE * sizeof(char *));
    for (size_t i = 0; i < PESSIMISTIC_SIZE; i++) {
        pessimistic_keys[i] = malloc(21);
        sprintf(pessimistic_keys[i], "key%zu",
                i); // Wszystkie będą miały ten sam hash
    }

    // Przeprowadzenie testów dla każdej funkcji haszującej
    for (size_t i = 0; i < sizeof(hash_functions) / sizeof(hash_functions[0]);
         i++) {
        printf("\n=== Testowanie funkcji haszującej: %s ===\n",
               hash_functions[i].name);

        // Test optymistyczny
        HashTable *opt_table =
            ht_create(INITIAL_CAPACITY, hash_functions[i].func);
        test_performance(opt_table, "Przypadek optymistyczny", optimistic_keys,
                         OPTIMISTIC_SIZE);
        ht_destroy(opt_table);

        // Test średni
        HashTable *avg_table =
            ht_create(INITIAL_CAPACITY, hash_functions[i].func);
        test_performance(avg_table, "Przypadek średni", average_keys,
                         AVERAGE_SIZE);
        ht_destroy(avg_table);

        // Test pesymistyczny
        HashTable *pes_table =
            ht_create(INITIAL_CAPACITY, hash_functions[i].func);
        test_performance(pes_table, "Przypadek pesymistyczny", pessimistic_keys,
                         PESSIMISTIC_SIZE);
        ht_destroy(pes_table);
    }

    // Zwolnienie pamięci
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
