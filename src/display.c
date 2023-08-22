#include "at91sam3x8.h"
#include "delay.h"
#include "systick.h"
#include "keypad.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

void Initialize_Pins_Display()
{
  * AT91C_PMC_PCER  = (3 << 13);	//enable clock on pio C and D
  * AT91C_PIOC_PER  = 0x3BC;		//enable pioc 2,3,4,5,7,8,9
  * AT91C_PIOC_ODR  = 0x3BC;		//set pins as input
  * AT91C_PIOD_PER  = (1 << 2);		//enable piod 2
  * AT91C_PIOD_OER  = (1 << 2);		//set as output
  * AT91C_PIOD_SODR = (1 << 2);		//set piod2 output as 1(turn off oe)

  //display
  * AT91C_PMC_PCER  = (3 << 13);		//enable clock on pio C and D
  * AT91C_PIOC_PER  = (0xFF << 2); 	//enable pioc 2-9
  * AT91C_PIOC_PER  = (0xFF << 12);	//enable pioc 12-19
  * AT91C_PIOC_ODR  = (0xFF << 2);	//set pins 2-9 as input(databus)
  * AT91C_PIOC_OER  = (0xFF << 12);	//set pins 12-19 as output
  * AT91C_PIOC_SODR = (0x9 << 14);	//set wr, rd, ce as high
  * AT91C_PIOC_SODR = (1 << 12);		//set pins 12 to 1 (oe = 1)
  * AT91C_PIOD_PER  = 1;			//enable pin0 piod
  * AT91C_PIOD_OER  = 1;			//set pin0 as output
}


unsigned char Read_Status_Display()
{
  //pin 34 to 41
  unsigned char Temp;
  *AT91C_PIOC_ODR = (255 << 2);// MAKE DATABUS AS INPUT
  *AT91C_PIOC_SODR =(1 << 13); // sets the dir pin to high // input
  *AT91C_PIOC_CODR = (1 << 12); // clears the OE
  *AT91C_PIOC_SODR = (1 << 14);//  set C/D to high
  *AT91C_PIOC_CODR = (1 << 15); // clear  CE (chip enable)
  *AT91C_PIOC_CODR = (1 << 16); // clear read control (RD)
  delay(10);
  Temp = (*AT91C_PIOC_PDSR >> 2);
  *AT91C_PIOC_SODR = (1 << 15); // set CE (chip enable)
  *AT91C_PIOC_SODR = (1 << 16); //set read control (RD)
  *AT91C_PIOC_SODR = (1 << 12); // disable the OE
  *AT91C_PIOC_CODR =(1 << 13); // set dir pin to low //output
  return Temp;
}

void Write_Command_2_Display(unsigned char Command)
{
  while(1){ 
    if((Read_Status_Display() & (3 << 0)) == (3 << 0)){
      
         *AT91C_PIOC_CODR = (255 << 2); // clear the pin form 34 to 41
         *AT91C_PIOC_SODR = (Command << 2);//  set Command to databus
         *AT91C_PIOC_CODR =(1 << 13); // set dir pin to low //output
         *AT91C_PIOC_CODR = (1 << 12); // clears/enable the OE
         *AT91C_PIOC_OER = (255 << 2);// MAKE DATABUS AS OUTPUT
         *AT91C_PIOC_SODR = (1 << 14);//  set C/D to high
         *AT91C_PIOC_CODR = (1 << 15); // clear CE (chip enable)
         *AT91C_PIOC_CODR = (1 << 17); // CLEAR WRITE DISPLAY
         delay(10);
         *AT91C_PIOC_SODR = (1 << 15); // SET CE (chip enable)
         *AT91C_PIOC_SODR = (1 << 17); // SET WRITE DISPLAY
         *AT91C_PIOC_SODR = (1 << 12); // disable the OE
         *AT91C_PIOC_ODR = (255 << 2);// MAKE DATABUS AS INPUT
         break;
    }
  }
} 

void Write_Data_2_Display(unsigned char Data)
{
  while(1){
   if((Read_Status_Display() & (3 << 0)) == (3 << 0)){
         *AT91C_PIOC_CODR = (255 << 2); // clear the pin form 34 to 41
         *AT91C_PIOC_SODR = (Data << 2); //Set Data to databus
         *AT91C_PIOC_CODR =(1 << 13); // set dir pin to low //output
         *AT91C_PIOC_CODR = (1 << 12); // clears/enable the OE
         *AT91C_PIOC_OER = (255 << 2);// MAKE DATABUS AS OUTPUT
         *AT91C_PIOC_CODR = (1 << 14);//  clear C/D
         *AT91C_PIOC_CODR = (1 << 15); // clear CE (chip enable)
         *AT91C_PIOC_CODR = (1 << 17); // CLEAR WRITE DISPLAY
         delay(10);
         *AT91C_PIOC_SODR = (1 << 15); // SET CE (chip enable)
         *AT91C_PIOC_SODR = (1 << 17); // SER WRITE DISPLAY
         *AT91C_PIOC_SODR = (1 << 12); // disable the OE
         *AT91C_PIOC_ODR = (255 << 2);// MAKE DATABUS AS INPUT
         break;
    }
  }
}

void Init_Display() 
{
   
    *AT91C_PIOD_CODR = (1 << 0);
    delay(10);
    *AT91C_PIOD_SODR = (1 << 0);
            
    Write_Data_2_Display(0x00);
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x40);//Set text home address
    Write_Data_2_Display(0x00);
    Write_Data_2_Display(0x40);
    Write_Command_2_Display(0x42); //Set graphic home address
    Write_Data_2_Display(0x1e);
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x41); // Set text area
    Write_Data_2_Display(0x1e); 
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x43); // Set graphic area
    Write_Command_2_Display(0x80); // text mode
    Write_Command_2_Display(0x94); // Text on graphic off 
}

void Clear_Display()
{
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x24);
    
    for(int i = 0; i< (16*40); i++){
      Write_Data_2_Display(0x00);
      Write_Command_2_Display(0xC0);
    }
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0x24);
}


void Print_From_Data(char key)
{
  key = key-' ';
  Write_Data_2_Display(key);
  Write_Command_2_Display(0xC0);
}

void PrintToDisplay(char string[])
{
  int i = 0;
  while (string[i] != '\0')
  {
       Print_From_Data(string[i]);
       i++;
  }
}

float RecupValue(int input)
{
    int key = -1;
    char value[10]={0};
    int i = 0;
    int prekey = input;
    int flag = 1;
    while(key != 10)
    {   
      key = key_pad();  
      if(key != -1 && prekey != key && key != 11 && key != 12)
      {
         value[i] = key + '0';
         Print_From_Data(value[i]);
         i++;
         prekey = key;
      }
      if (key == 11 && prekey != key && key != 12)
      {
        value[i] = '0';
        Print_From_Data(value[i]);
        i++;
        prekey = key;
      }
      if (key == 12 && prekey != key)
      {
        Print_From_Data('-');
        flag = -1;
        prekey = key;
      }
    }
    value[i] = '\0';
    return atof(value) * flag;
}
