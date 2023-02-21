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

void rotateLeft(void), rotateRight(void), moveLeft(void), moveRight(void);

void RIT_IRQHandler (void)
{					
	int down = LPC_GPIO1->FIOPIN & (1<<26);
	int left = LPC_GPIO1->FIOPIN & (1<<27);
	int right = LPC_GPIO1->FIOPIN & (1<<28);
	int up = LPC_GPIO1->FIOPIN & (1<<29);
	static int key1 = 0, key2 = 0;
	static int pressed = 0;
	static int fast = 0;

	disable_RIT();
	disable_timer(0);
	
	if(!(LPC_PINCON->PINSEL4 & (1<<22))){
		key1++;
		if(!(LPC_GPIO2->FIOPIN & (1<<11))){
			if(key1 == 1){
				rotateLeft();
			}
		}
		else {
			key1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4 |= (1 << 22);
		}
	}
	
	if(!(LPC_PINCON->PINSEL4 & (1<<24))){
		key2++;
		if(!(LPC_GPIO2->FIOPIN & (1<<12))){
			if(key2 == 1){
				rotateRight();
			}
		}
		else {
			key2 = 0;
			NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interr\ts			*/
			LPC_PINCON->PINSEL4 |= (1 << 24);
		}
	}

	if(!down){
		if(!fast){
			fast = 1;
			disable_timer(0);
			init_timer(0,12500000);
			enable_timer(0);
		}
	}
	if(!up){
		if(fast){
			fast = 0;
			disable_timer(0);
			init_timer(0,25000000);
			enable_timer(0);
		}
	}
	
	if(!pressed){
		pressed = 1;
		if(!left){
			moveLeft();
		}
		if(!right){
			moveRight();
		}
	}
	if(left && right) {
		pressed = 0;
	}

  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	enable_RIT();
	enable_timer(0);
  return;
}

void rotateLeft(){
	goingDown = 0;
	switch(actualShape){
		case 0:
			// line(posX, posY);			
			if(line_or > 0) {
				line_or--;
			}
			else {
				line_or = 1;
			}
			line(prevPosX, prevPosY);			
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
			t_shape(prevPosX, prevPosY);
			break;
		case 3:
			if(z_or > 0) {
				z_or--;
			}
			else {
				z_or = 1;
			}
			z_shape(prevPosX, prevPosY);
			break;
		case 4:
			if(s_or > 0) {
				s_or--;
			}
			else {
				s_or = 1;
			}
			s_shape(prevPosX, prevPosY);
			break;
		case 5:
			if(ll_or > 0) {
				ll_or--;
			}
			else {
				ll_or = 3;
			}
			ll_shape(prevPosX, prevPosY);
			break;
		case 6:
			if(rl_or > 0) {
				rl_or--;
			}
			else {
				rl_or = 3;
			}
			rl_shape(prevPosX, prevPosY);
			break;
	}
	goingDown = 1;
}

void rotateRight(){
	goingDown = 0;
	switch(actualShape){
		case 0:
			if(line_or < 1) {
				line_or++;
			}
			else {
				line_or = 0;
			}
			line(prevPosX, prevPosY);			
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
			t_shape(prevPosX, prevPosY);
			break;
		case 3:
			if(z_or < 1) {
				z_or++;
			}
			else {
				z_or = 0;
			}
			z_shape(prevPosX, prevPosY);
			break;
		case 4:
			if(s_or < 1) {
				s_or++;
			}
			else {
				s_or = 0;
			}
			s_shape(prevPosX, prevPosY);
			break;
		case 5:
			if(ll_or < 3) {
				ll_or++;
			}
			else {
				ll_or = 0;
			}
			ll_shape(prevPosX, prevPosY);
			break;
		case 6:
			if(rl_or < 3) {
				rl_or++;
			}
			else {
				rl_or = 0;
			}
			rl_shape(prevPosX, prevPosY);
			break;
	}
	goingDown = 1;
}

void moveLeft(void) {
	goingDown = 0;
	switch (actualShape){
		case 0:
			if(line(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
		case 1:
			if(cube(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
		case 2:
			if(t_shape(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
		case 3:
			if(z_shape(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
		case 4:
			if(s_shape(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
		case 5:
			if(ll_shape(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
		case 6:
			if(rl_shape(posX-1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX-1;
			}
			break;
	}
	goingDown = 1;
}
void moveRight(void) {
	goingDown = 0;
	switch (actualShape){
		case 0:
			if(line(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
		case 1:
			if(cube(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
		case 2:
			if(t_shape(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
		case 3:
			if(z_shape(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
		case 4:
			if(s_shape(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
		case 5:
			if(ll_shape(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
		case 6:
			if(rl_shape(posX+1, posY) == 1){
				prevPosX = posX;
				prevPosY = posY;
				posX = posX+1;
			}
			break;
	}
	goingDown = 1;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
