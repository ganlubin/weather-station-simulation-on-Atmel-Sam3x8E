#include "at91sam3x8.h"

int key_pad(void){
  int rowIndex[4] = {5,2,3,4};
  int colIndex[3] = {8,9,7};
  int value = -1;

  //Clear OE KEY BUS (Active Low)
  *AT91C_PIOD_CODR = 1 << 2;

  // Make all Column pin as output
  //Set all Column pin as high  7,8,9
    *AT91C_PIOC_PER = 0x380;
    *AT91C_PIOC_OER = 0x380;
    *AT91C_PIOC_SODR = 0x380;
  // Loop Column 0 & 1 &3
  for(int col = 0; col < 3; col++)
  {
    //Clear one column at the time
    *AT91C_PIOC_CODR = (1 << colIndex[col]);

    //Loop Row 
    for(int row = 0; row < 4; row++)
    {
      int readRow = *AT91C_PIOC_PDSR;
      //Read row and check if bit is zero
      if ((~readRow & (1 << rowIndex[row])) == (1 << rowIndex[row]))
        value = row*3+col+1;
    }//end loop Row
      //Set the column again
      *AT91C_PIOC_SODR=(1<<colIndex[col]);
    }

  // Make all Column pin as input
  *AT91C_PIOC_PER = 0x380;
  *AT91C_PIOC_ODR = 0x380;
  return value;
}
