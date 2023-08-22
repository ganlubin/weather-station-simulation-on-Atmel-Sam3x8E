#include "at91sam3x8.h"
#include "core_cm3.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "system_sam3x.h"
#include <stdio.h>
#include <stdlib.h>
#include "temp.h"
#include "delay.h"
#include "PWM.h"
#include "systick.h"
#include "linkedList.h"
#include "doubleLinkedList.h"
#include "display.h"
#include "alarm.h"
#include "keypad.h"
#include "ADC.h"


void writeMenu()
{
  Clear_Display();
  PrintToDisplay("1. Show Temperatures          ");
  PrintToDisplay("2. Find Sun                   ");
  PrintToDisplay("3. Show Alarm                 ");
  PrintToDisplay("4. Fast Mode                  ");
  PrintToDisplay("5. Update Alarm               ");
  PrintToDisplay("#. Clean                      ");
}

void operation()
{  
   int key = key_pad();
  
   if(key != previousKey)
   {
    switch(key){
      case 1: Clear_Display();
              if(mode_fast_test) PrintToDisplay("Mode fast  ...                # to back                      ");
              else PrintToDisplay("# to back                      ");
              Dprint_fwd(tempWeek);
              break;
      case 2: Clear_Display();
              PrintToDisplay("Now Searching the light...    ");
              changeDirection();
              break;
      case 3: Clear_Display();
              printAlarm();
              PrintToDisplay("                               ");
              PrintToDisplay("# to back                      ");
              break;
      case 4: if (mode_fast_test) 
              {
                PrintToDisplay("Do Not press again!           ");
                break;
              }
              mode_fast_test = 1;
              onemin = 1000;
              min_day = 24; // one hour
              PrintToDisplay("                              Now Fast Mode ...             ");
              break;
      case 5: Clear_Display();
              changeAlarm();
      case 12:Clear_Display();
              alarmchecked = 1;
              writeMenu();
              break;
     }
      previousKey = key;
   }
}



void main(){
  SystemInit();
  InitSystick();
  Initialize_Pins_Display();
  Init_Display();
  Clear_Display();
  InitTemp();
  initADC();
  initPower();
  tempDay = create();
  tempWeek = Dcreate();
  resetAlarm();
  writeMenu();
 
  while(1)
  {  
    if(alarmSys % onemin == 0)     
    {      
      time++;
      printf("time : %d ",time);
      addToList();
    }
    operation();
    int key = -1;
    key = key_pad();
    if (key == 12) 
      if (mode_fast_test)
      {
        writeMenu();
        PrintToDisplay("                              Now Fast Mode ...             ");
      }
  }
}
