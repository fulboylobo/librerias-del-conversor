#ifndef adc.h
#include "stm32f103xb.h"
#include "stdint.h"
void adc_init();
uint16_t adc_read(unsigned int canal);
float adc_read (unsigned int canal, int vmax);
#endif