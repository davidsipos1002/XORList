#include "XORList.h"

void printFunction(void *data)
{
    printf("%s\n", (char *) data);
}

int main(int argc, const char *argv[])
{
    ListT* list = createEmptyList();
    char *a = (char *) malloc(11);
    strcpy(a, "Oliver");
    char *b = (char *) malloc(11);
    strcpy(b, "David");
    char *c = (char *) malloc(11);
    strcpy(c, "Sipos");
    insertAtFront(list, a);
    insertAtRear(list, c);
    insertAtFront(list, b);
    printList(list, printFunction);
    deleteFirst(list, true);
    printList(list, printFunction);
    destroyList(list, true);
    printf("%s\n", b);
    return 0;
}
