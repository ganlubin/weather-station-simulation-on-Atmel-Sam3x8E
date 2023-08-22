#ifndef SYSTICK_H
#define SYSTICK_H

#include "core_cm3.h"

#define ticks 84000

extern int handler;
extern int alarmSys;

void InitSystick();
void SysTick_Handler();

#endif /* SYSTICK_H */