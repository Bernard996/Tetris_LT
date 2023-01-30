/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../Drawing.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

int AD_current;   
uint8_t  AD_last = 0xFF;     /* Last converted value               */

void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if(AD_current != AD_last){ //se diverso da quello precedente, scriviamo un nuovo valore in output
		if(AD_current<=0x333){
		ChangeVolume(0);
		}
			else if (AD_current<=0x666){
			ChangeVolume(1);
			}
				else if(AD_current<=0x999){
				ChangeVolume(2);
				}
					else if (AD_current<=0xCCC){
						ChangeVolume(3);
					}
					else {
						ChangeVolume(4);
					}
			
		AD_last = AD_current;
  }	
}
