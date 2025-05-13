// list_queue.c
#include "list_queue.h"
#include <stdlib.h>

static Node *head = NULL;
static int list_count = 0;

List_queue list_init() {
    List_queue queue = {0, NULL};
    return queue;
}

int list_size(List_queue *queue) { return queue->size; }

void list_insert(List_queue *queue, Element e) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return;
    new_node->data = e;
    new_node->next = NULL;

    if (!queue->head || e.priority < queue->head->data.priority) {
        new_node->next = queue->head;
        queue->head = new_node;
    } else {
        Node *curr = queue->head;
        while (curr->next && curr->next->data.priority <= e.priority) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
    queue->size++;
}

Element list_peek(List_queue *queue) {
    if (!queue->head)
        return (Element){0, 0};
    return queue->head->data;
}

Element list_pop(List_queue *queue) {
    if (!queue->head)
        return (Element){0, 0};
    Node *tmp = queue->head;
    Element result = tmp->data;
    queue->head = queue->head->next;
    free(tmp);
    queue->size--;
    return result;
}

void list_change_priority(List_queue *queue, int value, int new_priority) {
    Node *curr = queue->head;
    Node *prev = NULL;
    while (curr) {
        if (curr->data.value == value) {
            // wyjmij
            Node *to_remove = curr;
            if (prev)
                prev->next = curr->next;
            else
                queue->head = curr->next;
            queue->size--;
            Element e = to_remove->data;
            e.priority = new_priority;
            free(to_remove);
            // wstaw ponownie
            list_insert(queue, e);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void list_free(List_queue *queue) {
    Node *curr = queue->head;
    while (curr) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    head = NULL;
    queue->size = 0;
}
