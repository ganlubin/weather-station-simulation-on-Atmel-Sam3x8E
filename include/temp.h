#ifndef TEMP_H
#define TEMP_H

#include "at91sam3x8.h"
#include "core_cm3.h"
#include "delay.h"
#include "alarm.h"
#include "linkedList.h"
#include "doubleLinkedList.h"
#include <stdio.h>

extern char tempFlag;
extern int time;
extern int previousKey;
extern int onemin;
extern int min_day;
extern int mode_fast_test;
extern List *tempDay;
extern DList *tempWeek;

void InitTemp();
void StartTemp();
double ReadTemp();
void TC0_Handler();
void addToList();

#endif /* TEMP_H */