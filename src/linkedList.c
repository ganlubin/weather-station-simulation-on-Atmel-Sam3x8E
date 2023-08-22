#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item_s {
  float data;
  struct item_s * next;
}Item;

typedef struct list_s {
  int size;
  Item * head;
  Item * tail;
}List;

List * create ()
{
  List * list;
  list = calloc (1, sizeof *list);
  if (NULL == list) printf ("EXIT_FAILURE, %s: calloc", __func__);
  list->size = 0;
  return list;
}

int append (List * list,float data)
{
  Item * item;
  item = malloc (sizeof *item);
  if (NULL == item) {
    printf("EXIT_FAILURE, %s: malloc", __func__);
    return 0;    
  }
  item->data = data;
  item->next = NULL;
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
  }
  else {
    list->tail->next = item;
    list->tail = item;
  }
  list->size++;
  return 1;
}

void print (List * list)
{
  Item * item;
  if (NULL == list->head) puts("Now list is empty");
  else {
    puts("");
    for (item = list->head; NULL != item; item = item->next) printf (" %.3f", item->data);
    puts("");
  }
}

void destroy (List * list)
{
  Item * tmp;
  while (NULL != list->head) 
  {
    tmp = list->head->next;
    free (list->head);
    list->head = tmp;
  }
  free (list);
}

