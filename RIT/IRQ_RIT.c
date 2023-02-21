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
#include "../gameControls/gameControls.h"

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
		goingDown = 0;
		if(!left){
			switch(actualShape){
				case 0:
					// line(posX, posY);			
					if(line_or > 0) {
						line_or--;
					}
					else {
						line_or = 1;
					}
					line(posX, posY);			
					break;
				// case 1:
				// 	break;
				case 2:
					if(t_or > 0) {
						t_or--;
					}
					else {
						t_or = 3;
					}
					t_shape(posX, posY);
					break;
				case 3:
					if(z_or > 0) {
						z_or--;
					}
					else {
						z_or = 1;
					}
					z_shape(posX, posY);
					break;
				case 4:
					if(s_or > 0) {
						s_or--;
					}
					else {
						s_or = 1;
					}
					s_shape(posX, posY);
					break;
				case 5:
					if(ll_or > 0) {
						ll_or--;
					}
					else {
						ll_or = 3;
					}
					ll_shape(posX, posY);
					break;
				case 6:
					if(rl_or > 0) {
						rl_or--;
					}
					else {
						rl_or = 3;
					}
					rl_shape(posX, posY);
					break;
			}
		}
		if(!right){
			switch(actualShape){
				case 0:
					if(line_or < 1) {
						line_or++;
					}
					else {
						line_or = 0;
					}
					line(posX, posY);			
					break;
				// case 1:
				// 	break;
				case 2:
					if(t_or < 3) {
						t_or++;
					}
					else {
						t_or = 0;
					}
					t_shape(posX, posY);
					break;
				case 3:
					if(z_or < 1) {
						z_or++;
					}
					else {
						z_or = 0;
					}
					z_shape(posX, posY);
					break;
				case 4:
					if(s_or < 1) {
						s_or++;
					}
					else {
						s_or = 0;
					}
					s_shape(posX, posY);
					break;
				case 5:
					if(ll_or < 3) {
						ll_or++;
					}
					else {
						ll_or = 0;
					}
					ll_shape(posX, posY);
					break;
				case 6:
					if(rl_or < 3) {
						rl_or++;
					}
					else {
						rl_or = 0;
					}
					rl_shape(posX, posY);
					break;
			}
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
