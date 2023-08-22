#include "at91sam3x8.h"
#include <stdio.h>
#include "PWM.h"
#include "display.h"
#include "keypad.h"

void initADC()
{
  *AT91C_PMC_PCER1 = (1 << 5);	//ENABLE CLOCK FOR ADC
  *AT91C_ADCC_MR = (2 << 8);	//SET PRESCALER TO 2
}

float ADC_Right() 
{
    *AT91C_ADCC_CHER = (1 << 1); //Select channel 1
    *AT91C_ADCC_CR = (1 << 1); //Start an ADC  
    float temp;
    while(1)
       if((*AT91C_ADCC_SR & (1 << 24)) == (1 << 24))
       {
         temp = *AT91C_ADCC_LCDR & 0xFFF;
         temp = (temp / 0xFFF) * 3.3;
         return temp;
       }
}

float ADC_Left() // more closed to temp-sensor
{
    *AT91C_ADCC_CHER = (1 << 2); //Select channel 2
    *AT91C_ADCC_CR = (1 << 1); //Start an ADC  
    float temp;
    while(1)
       if((*AT91C_ADCC_SR & (1 << 24)) == (1 << 24))
       {
         temp = *AT91C_ADCC_LCDR & 0xFFF;
         temp = (temp / 0xFFF) * 3.3;
         *AT91C_ADCC_CHDR = (1 << 2); //Disable channel 2
         return temp;
       }
}

void changeDirection()
{
  PrintToDisplay("Please put under the light    ");
  PrintToDisplay("The resistance is the dir     ");
  PrintToDisplay("Press # to return            ");
  while(1)
  {
    initADC();
    float left = ADC_Left();
    initADC();
    float right = ADC_Right();
    if (left - 1 < 1e-2 && right - left > 0.4) turnServor(1838);
    else if (right - 1.2 < 1e-2 && left - right > 0.5) turnServor(5705);
    int key = -1;
    key = key_pad();
    if (key == 12) return;
  }
}
