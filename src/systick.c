#include "core_cm3.h"
#define ticks 84000

int handler = 0;
int alarmSys = 0;
void InitSystick()
{
  SysTick_Config(ticks);	//set systick to 1 ms
}
void SysTick_Handler()
{
  handler++;
  alarmSys++;
}
