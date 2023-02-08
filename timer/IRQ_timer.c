/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../RIT/RIT.h"
#include "../shapes/shapes.h"
#include "../gameControls/gameControls.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/



void TIMER0_IRQHandler (void)
{
  switch(actualShape){
    case 0:
      if(line(posX, posY)){
        prevPosX = posX;
        prevPosY = posY;
        posY = posY+1;
      }
      else {
				prevPosX = initPosX;
        prevPosY = initPosY;
				posX = initPosX;
				posY = initPosY;
        actualShape = actualShape + 1;
      }
    break;
    case 1:
      if(cube(posX, posY)){
        prevPosX = posX;
        prevPosY = posY;
        posY = posY+1;
      }
      else {
        prevPosX = initPosX;
        prevPosY = initPosY;
				posX = initPosX;
				posY = initPosY;
        // actualShape = actualShape + 1;
      }
    break;
  }
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
