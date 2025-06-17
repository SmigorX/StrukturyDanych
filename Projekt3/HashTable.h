// HashTable.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashNode {
    char *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t capacity;
    size_t size;
    size_t (*hash_func)(char *);
    float load_factor;
} HashTable;

// Initialize hash table
HashTable *ht_create(size_t initial_capacity, size_t (*hash_func)(char *)) {
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
    table->hash_func = hash_func;
    table->load_factor = 0.75f; // Default load factor
    return table;
}

// Destroy hash table
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

// Helper function to create a new node
HashNode *create_node(char *key, void *value) {
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

// Check if resize is needed and perform it if necessary
void check_resize(HashTable *table) {
    if ((float)table->size / table->capacity >= table->load_factor) {
        ht_resize(table, table->capacity * 2);
    }
}

// Insert or update key-value pair
int ht_insert(HashTable *table, char *key, void *value) {
    if (!table || !key)
        return 0;

    check_resize(table);

    size_t index = table->hash_func(key) % table->capacity;
    HashNode *node = table->buckets[index];

    // Check if key already exists
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return 1;
        }
        node = node->next;
    }

    // Create new node
    HashNode *new_node = create_node(key, value);
    if (!new_node)
        return 0;

    // Insert at the beginning of the chain
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->size++;

    return 1;
}

// Remove key-value pair
int ht_remove(HashTable *table, char *key) {
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

// Lookup value by key
void *ht_get(HashTable *table, char *key) {
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

// Resize hash table
void ht_resize(HashTable *table, size_t new_capacity) {
    if (!table || new_capacity == 0)
        return;

    HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode *));
    if (!new_buckets)
        return;

    // Rehash all elements
    for (size_t i = 0; i < table->capacity; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *next = node->next;

            // Calculate new index
            size_t new_index = table->hash_func(node->key) % new_capacity;

            // Insert into new buckets
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;

            node = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
}

#endif
