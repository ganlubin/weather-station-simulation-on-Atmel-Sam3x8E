#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "data.h"
#include "display.h"

typedef struct Ditem_s
{
    List *day;
    stats_vars stats;
    struct Ditem_s *next;
    struct Ditem_s *prev;
} DItem;

typedef struct Dlist_s
{
    int size;
    DItem *head;
    DItem *tail;
} DList;

DList *Dcreate();
int Dappend(DList *list, List *day);
void rem_head(DList *list);
void Ddestroy(DList *list);
void Dprint_fwd(DList *list);
void Dprint_rev(DList *list);

#endif /* DOUBLELINKEDLIST_H */