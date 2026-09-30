#include "adc.h"
void adc_init ()
{
//puertos     
RCC->APB2ENR |=RCC_APB2ENR_IOPAEN| RCC_APB2ENR_IOPBEN;
//adon
ADC1->CR2|=ADC_CR2_ADON;
//espera de estabilizacion   
for(volatile int i=0; i<1000; i++);
//reset de calibracion
ADC1->CR2|=ADC_CR2_RSTCAL;
while (ADC1->CR2 & ADC_CR2_RSTCAL);
//calibracion 
ADC1->CR2|=ADC_CR2_CAL;
while (ADC1->CR2 & ADC_CR2_CAL);
//habilitar trigger para conversiones regulares 
ADC1->CR2|=ADC_CR2_EXTTRIG;
//extsel = 111
ADC1->CR2|=ADC_CR2_EXTSEL;}
uint16_t ADC_READ(unsigned int canal)
//habilitar pines como entrada analogica 
{if (canal<=7){
//para los pines del 0 al 7 (puerto a)   
GPIOA->CRL &= ~ (0xF<<(canal*4));
}
else if (canal <=9){
//para los pines del 0 al 9 (puerto b)   
GPIOB->CRL &= ~ (0xF<<((canal % 8)*4));
}
//seleccion de canal
ADC1->SQR3 = 0;
ADC1->SQR3 |= (canal & 0x1F);
//tiempo de muestreo 
ADC1->SMPR2 = 0;
ADC1->SMPR2 |=(0b111 << (canal * 3));
//inicio de conversion
ADC1->CR2 |=ADC_CR2_SWSTART;//fin de conversion 
while(!(ADC1->SR & ADC_SR_EOC));
//devuelve valor adc de 12 bits 
// de 0 a 4095
return ADC1->DR;
}
