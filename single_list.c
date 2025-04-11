#include "single_list.h"
const bool empty(StringNode* head){
    return head == NULL;
}
const int front(StringNode* head){
    return head->elem;
}

void addFront(const int e, StringNode** head){
    StringNode* v = (StringNode*)malloc(sizeof(StringNode));
    if(v == NULL){
        return;
    }
    v->elem = e;
    v->next = *head;
    *head = v;
}

void removeFront(StringNode** head){
    StringNode* old = *head;
    *head = old->next;
    free(old);
}

void printList(StringNode* head){
    StringNode* temp = head;
    while(temp != NULL){
        printf("%d -> ", temp->elem);
        temp = temp-> next;
    }
    printf("NULL\n");
}
