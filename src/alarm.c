#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "temp.h"
#include "keypad.h"
int alarmchecked = 1;
typedef struct stats_alarm
{
	float lower;
	float upper;
}stats_alarm;

stats_alarm alarm;

void resetAlarm()
{
    alarm.lower = -20;
    alarm.upper = 25;
}

void updateAlarmLow(float low)
{
    alarm.lower = low;
}

void updateAlarmUp(float up)
{
    alarm.upper = up;
}

void checkAlarm(float temp)
{
    if (temp - alarm.upper > 0.01) 
    {
      PrintToDisplay("                              ");
      PrintToDisplay("Temp too high!!! Please check ");
      puts("Temp too high");
      alarmchecked = 0;
      printf("temp > upper : %.2f > %.2f\n", temp, alarm.upper);
      return;
    }
    if (alarm.lower - temp > 0.01) 
    {
      PrintToDisplay("                              ");
      PrintToDisplay("Temp too low !!! Please check ");
      puts("Temp too low");
      alarmchecked = 0;
      printf("temp < lower : %.2f < %.2f\n", temp, alarm.lower);
      return;
    }
}

void changeAlarm()
{
  PrintToDisplay("1. Update top temp            ");
  PrintToDisplay("2. Update low temp            ");
  int key = -1;
  while (key != 1 && key != 2) key = key_pad();
  Clear_Display();
  if (key == 1)//change up
  {
    PrintToDisplay("Please Input New Top Temp End*");
    float top = RecupValue(1);
    alarm.upper = top;
    printf("%.2f\n", top);
  }
  else
  {
    PrintToDisplay("Please Input New Low Temp End*");
    float down = RecupValue(2);
    alarm.lower = down;
    printf("%.2f\n", down);
  }
}

void printAlarm()
{
  if (alarm.lower > alarm.upper) 
  {
    PrintToDisplay("Temp not normal please check! ");
    return;
  }
  char infoAlarm[100] = {0};
  sprintf(infoAlarm, "Alarm lower:%.2f upper:%.2f \0", alarm.lower, alarm.upper);
  int i = 0;
  while (infoAlarm[i] != '\0')
  {
    Print_From_Data(infoAlarm[i]);
    i++;
  }
}
