#include "at91sam3x8.h"

void initPower(){
  *AT91C_PMC_PCER1 = (1 << 4);
  *AT91C_PIOC_ABMR |= (1 << 22);//Activate peripheral B to control the pin in REG_PIOB_ABSR  
  *AT91C_PIOC_PDR = (1 << 22);  
  
  *AT91C_PWMC_ENA = (1 << 5);
  *((volatile unsigned int*)0x400942A0) |= 5;
  *AT91C_PWMC_CH5_CPRDR |= 52500; //52500
  *AT91C_PWMC_CH5_CDTYR |= 2625;  //52500 / 20
}

void turnServor(int degree){
  *AT91C_PWMC_CH5_CDTYR = degree;
}
