#include <stdio.h>
#include <stdlib.h>

#include "double_list.h"
#include "single_list.h"

int main() {
    DoubleNode *node = NULL;
    int data = 69;
    int result;
    result = doubleCreateNode(&data, sizeof(int), node);
    if (result == 0) {
        printf("Ok");
    } else {
        printf("Shit");
    };

    Node *singleNode = createNode(&data, sizeof(int));

    //    LinkedList list;
    //    initList(&list);
    //
    //    pushFront(&list, &(int){10}, sizeof(int));
    //    pushFront(&list, &(int){20}, sizeof(int));
    //
    //    printList(&list, printInt);
    printf("Test");
}
