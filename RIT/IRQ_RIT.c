/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../shapes/shapes.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void RIT_IRQHandler (void)
{					
	int left = LPC_GPIO1->FIOPIN & (1<<27), right = LPC_GPIO1->FIOPIN & (1<<28);
	static int pressed = 0;
	
	if(!pressed){
		if(!left){
			t_orientation--;
			t_shape(70, 100);
			pressed = 1;
		}
		if(!right){
			t_orientation++;
			t_shape(70, 100);
			pressed = 1;
		}
	}
	if(left && right) {
		pressed = 0;
	}

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
