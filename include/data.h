#ifndef DATA_H
#define DATA_H

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
} stats_vars;

float average(List *list, int n);
float min(List *list);
float max(List *list);
void print_data(stats_vars data);
stats_vars calc_stats(List *list);

#endif /* DATA_H */