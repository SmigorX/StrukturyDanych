#include <stdlib.h>
#include <stdio.h>

#include "single_list.h"

int main(){
    StringNode* head = NULL;
    addFront(10, &head);
    addFront(20, &head);

    printList(head);
}
