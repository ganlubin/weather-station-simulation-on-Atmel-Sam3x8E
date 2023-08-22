#ifndef ALARM_H
#define ALARM_H

#include <stdio.h>
#include "display.h"
#include "temp.h"
#include "keypad.h"

extern int alarmchecked;

typedef struct stats_alarm
{
    float lower;
    float upper;
} stats_alarm;

extern stats_alarm alarm;

void resetAlarm();
void updateAlarmLow(float low);
void updateAlarmUp(float up);
void checkAlarm(float temp);
void changeAlarm();
void printAlarm();

#endif /* ALARM_H */