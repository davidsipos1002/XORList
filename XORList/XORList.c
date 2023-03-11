#include "XORList.h"

ListT* createEmptyList()
{
    ListT* list = (ListT*) malloc(sizeof(ListT));
    list->count = 0;
    list->f = (uintptr_t) NULL;
    list->l = (uintptr_t) NULL;
    return list;
}

void destroyList(ListT *list, bool freeData)
{
    uintptr_t prev = 0;
    uintptr_t curr = list->f;
    uintptr_t aux = 0;
    while(curr != 0)
    {
        aux = curr;
        curr = ((NodeT *) curr)->link ^ prev;
        if(freeData)
            free(((NodeT*) aux)->data);
        free((NodeT*)aux);
        prev = aux;
    }
    list->f = list->l = 0;
    list->count = 0;
    free(list);
}

void insertAtFront(ListT *list, void* data)
{
    NodeT *nw = (NodeT *) malloc(sizeof(NodeT));
    nw->data = data;
    if(list->count == 0)
    {
        nw->link = 0;
        list->f = list->l = (uintptr_t) nw;
    }
    else
    {
        nw->link = list->f;
        ((NodeT *) list->f)->link = (uintptr_t) nw ^ (uintptr_t) ((NodeT *) list->f)->link;
        list->f = (uintptr_t) nw;
    }
    list->count++;
}

void insertAtRear(ListT *list, void* data)
{
    NodeT *nw = (NodeT *) malloc(sizeof(NodeT));
    nw->data = data;
    if(list->count == 0)
    {
        nw->link = 0;
        list->f = list->l = (uintptr_t) nw;
    }
    else
    {
        nw->link = (uintptr_t) list->l;
        ((NodeT *) list->l)->link = (uintptr_t) nw ^ (uintptr_t) ((NodeT *) list->l)->link;
        list->l = (uintptr_t) nw;
    }
    list->count++;
}

NodeT* find(ListT *list, void* data)
{
    uintptr_t prev = 0;
    uintptr_t curr = list->f;
    uintptr_t aux = 0;
    while(curr != 0)
    {
        if(memcmp(data, ((NodeT*) curr)->data, sizeof(data)) == 0)
            return (NodeT *) curr;
        aux = curr;
        curr = ((NodeT *) curr)->link ^ prev;
        prev = aux;
    }
    return NULL;
}

void insertAfter(ListT *list, void* after, void* data)
{
    uintptr_t prev = 0;
    uintptr_t curr = list->f;
    uintptr_t aux = 0;
    while(curr != 0 && memcmp(after, ((NodeT*) curr)->data, sizeof(after)) != 0)
    {
        aux = curr;
        curr = ((NodeT *) curr)->link ^ prev;
        prev = aux;
    }
    if(curr == 0)
        return;
    else if(curr == list->l)
        insertAtRear(list, data);
    else
    {
        aux = prev ^ (uintptr_t) ((NodeT*) curr)->link;
        NodeT *nw = (NodeT *) malloc(sizeof(NodeT));
        nw->data = data;
        nw->link = curr ^ aux;
        ((NodeT*) aux)->link = (((NodeT*) aux)->link ^ curr) ^ (uintptr_t) nw;
        ((NodeT*) curr)->link = (((NodeT*) curr)->link ^ aux)^ (uintptr_t) nw;
        list->count++;
    }
}

void deleteFirst(ListT *list, bool freeData)
{
    if(list->count == 0)
        return;
    if(list->count == 1)
    {
        free(((NodeT*) list->f)->data);
        free((NodeT*) list->f);
        list->f = list->l = 0;
        list->count--;
        return;
    }
    uintptr_t del = list->f;
    uintptr_t next = ((NodeT*) list->f)->link;
    ((NodeT*) next)->link = ((NodeT*) next)->link ^ del;
    list->f = next;
    if(freeData)
        free(((NodeT*) del)->data);
    free((NodeT*) del);
    list->count--;
}

void deleteLast(ListT *list, bool freeData)
{
    if(list->count == 0)
        return;
    if(list->count == 1)
    {
        if(freeData)
            free(((NodeT*) list->f)->data);
        free((NodeT*) list->f);
        list->f = list->l = 0;
        list->count--;
        return;
    }
    uintptr_t del = list->l;
    uintptr_t prev = ((NodeT*) list->l)->link;
    ((NodeT*) prev)->link = ((NodeT*) prev)->link ^ del;
    list->l = prev;
    if(freeData)
        free(((NodeT*) del)->data);
    free((NodeT*) del);
    list->count--;
}

void deleteValue(ListT *list, void* delete, bool freeData)
{
    uintptr_t prev = 0;
    uintptr_t curr = list->f;
    uintptr_t aux = 0;
    while(curr != 0 && memcmp(delete, ((NodeT*) curr)->data, sizeof(delete)) != 0)
    {
        aux = curr;
        curr = ((NodeT *) curr)->link ^ prev;
        prev = aux;
    }
    if(curr == 0)
        return;
    else if(curr == list->f)
        deleteFirst(list, freeData);
    else if(curr == list->l)
        deleteLast(list, freeData);
    else
    {
        aux = prev ^ (uintptr_t) ((NodeT*) curr)->link;
        ((NodeT*) prev)->link = (((NodeT*) prev)->link ^ curr) ^ aux;
        ((NodeT*) aux)->link = (((NodeT*) aux)->link ^ curr) ^ prev;
        if(freeData)
            free(((NodeT*) curr)->data);
        free((NodeT*) curr);
        list->count--;
    }
}

void printList(ListT *list, fPtrPrint printElement)
{
    if(list->count == 0)
        printf("Empty list!");
    uintptr_t prev = 0;
    uintptr_t curr = list->f;
    uintptr_t aux = 0;
    while(curr != 0)
    {
        printElement(((NodeT *) curr)->data);
        aux = curr;
        curr = ((NodeT *) curr)->link ^ prev;
        prev = aux;
    }
}

void printReversedList(ListT *list, fPtrPrint printElement)
{
    if(list->count == 0)
        printf("Empty list!");
    uintptr_t prev = 0;
    uintptr_t curr = list->l;
    uintptr_t aux = 0;
    while(curr != 0)
    {
        printElement(((NodeT *) curr)->data);
        aux = curr;
        curr = ((NodeT *) curr)->link ^ prev;
        prev = aux;
    }
}
