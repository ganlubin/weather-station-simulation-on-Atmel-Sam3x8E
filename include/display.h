#ifndef DISPLAY_H
#define DISPLAY_H

#include "at91sam3x8.h"
#include "delay.h"
#include "keypad.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

void Initialize_Pins_Display();
unsigned char Read_Status_Display();
void Write_Command_2_Display(unsigned char Command);
void Write_Data_2_Display(unsigned char Data);
void Init_Display();
void Clear_Display();
void Print_From_Data(char key);
void PrintToDisplay(char string[]);
float RecupValue(int input);

#endif /* DISPLAY_H */