#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linkedList.h"
#include "display.h"

typedef struct stats_vars
{
    float average;
    float min;
    float max;
}stats_vars;



float average(List * list,int n)
{
    float av = 0;
    Item * item;
    if (list->head != NULL) 
      for (item = list->head; NULL != item; item = item->next) 
        av+=item->data;
    return av /= n;
}
float min(List * list)
{
    float min = 0;
    Item * item;
    if (list->head != NULL) 
    {
      min=list->head->data;
      for (item = list->head; NULL != item; item = item->next) 
        if(min>item->data)
           min = item->data;
    }
    return min;
}

float max(List * list)
{
    float max = 0;
    Item * item;
    if (list->head != NULL) 
    {
       max=list->head->data;
       for (item = list->head; NULL != item; item = item->next) 
          if(max<item->data)
              max = item->data;
    }
    return max;
}

void print_data(stats_vars data)
{
   
  char info[100] = {0};
  sprintf(info, "min:%.2f max:%.2f avg:%.2f \0", data.min, data.max, data.average);
  printf("%s\n", info);
  int i = 0;
  while (info[i] != '\0')
  {
    Print_From_Data(info[i]);
    i++;
  }
}

stats_vars calc_stats(List * list)
{
    stats_vars stats;
    stats.average = average(list, list->size);
    stats.min = min(list);
    stats.max = max(list);
    return stats;
}
