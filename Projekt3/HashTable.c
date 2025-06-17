// HashTable.c
#include "HashTable.h"
#include <stdio.h>

HashTable *ht_create(size_t initial_capacity,
                     size_t (*hash_func)(const char *)) {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    table->buckets = calloc(initial_capacity, sizeof(HashNode *));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    table->capacity = initial_capacity;
    table->size = 0;
    table->collisions = 0;
    table->hash_func = hash_func;
    table->load_factor = 0.75f;
    return table;
}

void ht_destroy(HashTable *table) {
    if (!table)
        return;

    for (size_t i = 0; i < table->capacity; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }

    free(table->buckets);
    free(table);
}

static HashNode *create_node(const char *key, void *value) {
    HashNode *node = malloc(sizeof(HashNode));
    if (!node)
        return NULL;

    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }

    node->value = value;
    node->next = NULL;
    return node;
}

void ht_resize(HashTable *table, size_t new_capacity) {
    if (!table || new_capacity == 0)
        return;

    HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode *));
    if (!new_buckets)
        return;

    for (size_t i = 0; i < table->capacity; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *next = node->next;
            size_t new_index = table->hash_func(node->key) % new_capacity;

            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;

            node = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
    table->collisions = 0; // Reset collisions after resize
}

int ht_insert(HashTable *table, const char *key, void *value) {
    if (!table || !key)
        return 0;

    size_t index = table->hash_func(key) % table->capacity;

    // Add new node
    HashNode *new_node = create_node(key, value);
    if (!new_node)
        return 0;

    // Count collision if bucket not empty
    if (table->buckets[index] != NULL) {
        table->collisions++;
    }

    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->size++;

    // Resize if needed
    if ((float)table->size / table->capacity >= table->load_factor) {
        ht_resize(table, table->capacity * 2);
    }

    return 1;
}

int ht_remove(HashTable *table, const char *key) {
    if (!table || !key)
        return 0;

    size_t index = table->hash_func(key) % table->capacity;
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                table->buckets[index] = node->next;
            }

            free(node->key);
            free(node);
            table->size--;
            return 1;
        }

        prev = node;
        node = node->next;
    }

    return 0;
}

void *ht_get(HashTable *table, const char *key) {
    if (!table || !key)
        return NULL;

    size_t index = table->hash_func(key) % table->capacity;
    HashNode *node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}
