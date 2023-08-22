#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item_s {
    float data;
    struct item_s *next;
} Item;

typedef struct list_s {
    int size;
    Item *head;
    Item *tail;
} List;

List *create();
int append(List *list, float data);
void print(List *list);
void destroy(List *list);

#endif /* LINKEDLIST_H */