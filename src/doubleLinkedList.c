#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "data.h"
#include "display.h"

typedef struct Ditem_s 
{
  List * day;
  stats_vars stats;
  struct Ditem_s * next;
  struct Ditem_s * prev;
}DItem;


typedef struct Dlist_s 
{
  int size;
  DItem * head;
  DItem * tail;
}DList;


DList * Dcreate ()
{
  DList * list;
  
  list = calloc (1, sizeof *list);
  if (NULL == list) return 0;
  list->size = 0;
  return list;
}

int Dappend (DList * list, List * day)
{
  DItem * item;
  
  item = malloc(sizeof *item);
  if (NULL == item) return 0;
  item->day = day;
  item->stats = calc_stats(day);
  item->next = NULL;
  
  if (NULL == list->head) 
  {
    list->head = item;
    list->tail = item;
    item->prev = NULL;
  }
  else 
  {
    list->tail->next = item;
    item->prev = list->tail;
    list->tail = item;
  }
  list->size++;
  return 1;
}

void rem_head (DList * list)
{
	DItem * old_item;
	old_item = list->head;
	if(old_item == NULL) printf("List is empty");
	else 
        {
          if(old_item->next == NULL) printf("Error!!");
          old_item = list->head;
	  list->head = list->head->next;
	}
        destroy(old_item->day);
	free(old_item);
}

void Ddestroy (DList * list)
{
  DItem * tmp;
  while (NULL != list->head) 
  {
    tmp = list->head->next;
    destroy(list->head->day);
    free (list->head);
    list->head = tmp;
  }
  free (list);
}

void Dprint_fwd (DList * list)  //print
{
  DItem * item;
  if (NULL == list->head) puts("Now list is empty");
  else {
    puts("");
    for (item = list->head; NULL != item; item = item->next) print_data(item->stats);
    puts("");
  }
}

void Dprint_rev (DList * list)
{
  DItem * item;
  if (NULL == list->head) puts("Now list is empty");
  else {
    puts("");
    for (item = list->tail; NULL != item; item = item->prev) print(item->day);
    puts("");
  }
}
