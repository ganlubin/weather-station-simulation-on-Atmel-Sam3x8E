#ifndef ADC_H
#define ADC_H

#include "at91sam3x8.h"

void initADC();
float ADC_Right();
float ADC_Left();
void changeDirection();

#endif /* ADC_H */