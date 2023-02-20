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
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD_advanced/GLCD.h" 
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
  int i,j;
  char s[10];
  switch(actualShape){
    case 0:
      if(line(posX-1, posY)){
        prevPosX = posX-1;
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
    case 2:
      if(t_shape(posX, posY)){
        // t_or++;
        // if(t_or == 4) t_or = 0;
        prevPosX = posX;
        prevPosY = posY;
        posY = posY+1;
      }
      else {
        prevPosX = initPosX;
        prevPosY = initPosY;
				posX = initPosX;
				posY = initPosY;
      }
  }
  for(i=0; i<11; i++) {
    for(j=0; j<10; j++) {
      s[j] = gameMatrix[i][j] + '0';
    }
    GUI_Text(0, 15*i, (uint8_t*)s, Black, White);
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
