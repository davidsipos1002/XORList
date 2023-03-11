#ifndef XORLIST_INCL
#define XORLIST_INCL

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    void* data;
    uintptr_t link;
}NodeT;

typedef struct
{
    uintptr_t f, l;
    int count;
}ListT;

typedef void (*fPtrPrint)(void *data);

ListT* createEmptyList(void);
void destroyList(ListT*, bool);
void insertAtFront(ListT*, void*);
void insertAtRear(ListT*, void*);
NodeT* find(ListT*, void*);
void insertAfter(ListT*, void*, void*);
void deleteFirst(ListT*, bool);
void deleteLast(ListT*, bool);
void deleteValue(ListT*, void*, bool);
void printList(ListT*, fPtrPrint);
void printReversedList(ListT*, fPtrPrint);

#endif
