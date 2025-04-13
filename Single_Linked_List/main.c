#include <stdlib.h>
#include <stdio.h>

#include "single_list.h"

int main(){
    LinkedList list;
    initList(&list);

    pushFront(&list, &(int){10}, sizeof(int));
    pushFront(&list, &(int){20}, sizeof(int));

    printList(&list, printInt);

}
