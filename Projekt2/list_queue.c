// list_queue.c
#include "list_queue.h"
#include <stdlib.h>

typedef struct Node {
    Element data;
    struct Node* next;
} Node;

static Node* head = NULL;
static int list_count = 0;

void list_init() {
    head = NULL;
    list_count = 0;
}

int list_size() {
    return list_count;
}

void list_insert(Element e) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = e;
    new_node->next = NULL;

    if (!head || e.priority < head->data.priority) {
        new_node->next = head;
        head = new_node;
    } else {
        Node* curr = head;
        while (curr->next && curr->next->data.priority <= e.priority) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    list_count++;
}

Element list_peek() {
    if (!head) return (Element){0,0};
    return head->data;
}

Element list_pop() {
    if (!head) return (Element){0,0};
    Node* tmp = head;
    Element result = tmp->data;
    head = head->next;
    free(tmp);
    list_count--;
    return result;
}

void list_change_priority(int value, int new_priority) {
    Node* curr = head;
    Node* prev = NULL;
    while (curr) {
        if (curr->data.value == value) {
            // wyjmij
            Node* to_remove = curr;
            if (prev) prev->next = curr->next;
            else head = curr->next;
            list_count--;
            Element e = to_remove->data;
            e.priority = new_priority;
            free(to_remove);
            // wstaw ponownie
            list_insert(e);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void list_free() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    head = NULL;
    list_count = 0;
}
