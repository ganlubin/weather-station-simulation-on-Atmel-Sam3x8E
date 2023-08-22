#include "at91sam3x8.h"
#include "core_cm3.h"
#include "delay.h"
#include "alarm.h"
#include "linkedList.h"
#include "doubleLinkedList.h"
#include "stdio.h"

char tempFlag = 0;
int time = 0;
int previousKey = 0;
int onemin = 60 * 1000;
int min_day = 24 * 60;
int mode_fast_test = 0;//Bool
List * tempDay; 
DList * tempWeek;
void InitTemp()
{
  *AT91C_PMC_PCER = 134221824;		//ENABLE CLOCK FOR TC0 and PIOB
  *AT91C_TC0_CMR = 0;	//CHOOSE TIMER_CLOCK1 AS TCCLK
  *AT91C_TC0_CCR = 5;			//ENABLE CLOCK AND SW RESET
  *AT91C_TC0_CMR = 0x60000;		//SET REGB TO RISING
  *AT91C_PIOB_PER = (1 << 25);		//ENABLE PIOB25
  
  *AT91C_PIOB_OER = 1 << 25;
  *AT91C_PIOB_CODR = 1 << 25;
  
  
  NVIC_ClearPendingIRQ((IRQn_Type)27);
  NVIC_EnableIRQ((IRQn_Type)27);
}

void StartTemp()
{
  *AT91C_PIOB_OER = (1 << 25);		//LOW START PULSE
  delay(25);
  *AT91C_PIOB_ODR = (1 << 25);		//END START PULSE
  *AT91C_TC0_CCR = 4;			//RESET TC
  unsigned int interrupt = *AT91C_TC0_SR;
  *AT91C_TC0_IER = (1 << 6);		//ENABLE INTERRUPT ON LDRBS
  delay(35000);
}

double ReadTemp()
{
  unsigned int a = *AT91C_TC0_RA;
  unsigned int b = *AT91C_TC0_RB;
  double timeUs = (double)(b - a) / (double)42.0;
  double temp = timeUs / 5 - 273.15;
  return temp;
}

void TC0_Handler()
{
  *AT91C_TC0_IDR = (1 << 6);		//DISABLE INTERRUPT ON LDRBS
  tempFlag = 1;
}

void addToList()
{
  int res;
  StartTemp();
  float temp = ReadTemp();
  while(temp < -100 || temp > 100)
  {
   StartTemp();
   temp = ReadTemp();
  }
  printf("real time temp : %.2f\n", temp);
  if (alarmchecked) checkAlarm(temp);
  if(time < min_day)
  { 
     res = append(tempDay, temp);
     if(!res) rem_head(tempWeek);
  }
  else
  {
     time = 0;
     res = Dappend(tempWeek,tempDay);
     tempDay = create();
     if(!res)
     {
       rem_head(tempWeek);
       tempDay = create();
     }
   }
}
