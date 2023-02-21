/*********************************************************************************************************
**--------------File
*Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "../GLCD_advanced/GLCD.h"
#include "../RIT/RIT.h"
#include "../TouchPanel/TouchPanel.h"
#include "../gameControls/gameControls.h"
#include "../shapes/shapes.h"
#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER0_IRQHandler(void) {
  int i, j;
  static int minutes = 0, seconds = 0;
  char s[5];
  sprintf(s, "%02d:%02d", minutes, seconds);
  GUI_Text(10, 10, (uint8_t*)s, Black, White);
  switch (actualShape) {
    case 0:
      if (line(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
    case 1:
      if (cube(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
    case 2:
      if (t_shape(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
    case 3:
      if (z_shape(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } 
      else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
    case 4:
      if (s_shape(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } 
      else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
    case 5:
      if (ll_shape(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } 
      else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
    case 6:
      if (rl_shape(posX, posY)) {
        prevPosX = posX;
        prevPosY = posY;
        posY = posY + 1;
      } 
      else {
        prevPosX = initPosX;
        prevPosY = initPosY;
        posX = initPosX;
        posY = initPosY;
        actualShape = LPC_RIT->RICOUNTER %7;
      }
      break;
  }
  // for (i = 0; i < 11; i++) {
  //   for (j = 0; j < 10; j++) {
  //     s[j] = gameMatrix[i][j] + '0';
  //   }
  //   GUI_Text(0, 15 * i, (uint8_t*)s, Black, White);
  // }
  seconds ++;
  if(seconds == 60){
    seconds = 0;
    minutes++;
  }
  disable_timer(0);
  disable_RIT();
  checkMatrix();
  enable_timer(0);
  enable_RIT();

  LPC_TIM0->IR = 1; /* clear interrupt flag */
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
void TIMER1_IRQHandler(void) {
  LPC_TIM1->IR = 1; /* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
