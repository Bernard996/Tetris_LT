#include "../GLCD_advanced/GLCD.h"
#include "LPC17xx.h"
#include "shapes.h"


const uint16_t width = 24;
int8_t line_orientation = 0;
int8_t z_orientation = 0;
int8_t s_orientation = 0;
int8_t t_orientation = 0;


void line(uint16_t x0, uint16_t y0){
  if(!line_orientation){
    LCD_DrawRectangle(x0, y0, width*4, width, Black);
    LCD_DrawRectangle(x0+(0*width)+1, y0+1, width-2, width-2, Red);
    LCD_DrawRectangle(x0+(1*width)+1, y0+1, width-2, width-2, Red);
    LCD_DrawRectangle(x0+(2*width)+1, y0+1, width-2, width-2, Red);
    LCD_DrawRectangle(x0+(3*width)+1, y0+1, width-2, width-2, Red);
  }
  else {
    LCD_DrawRectangle(x0, y0, width, width*4, Black);
    LCD_DrawRectangle(x0+1, y0+(0*width)+1, width-2, width-2, Green);
    LCD_DrawRectangle(x0+1, y0+(1*width)+1, width-2, width-2, Green);
    LCD_DrawRectangle(x0+1, y0+(2*width)+1, width-2, width-2, Green);
    LCD_DrawRectangle(x0+1, y0+(3*width)+1, width-2, width-2, Green);
  }

}
  

void cube(uint16_t x0, uint16_t y0){
  LCD_DrawRectangle(x0, y0, width*2, width*2, Black);
  LCD_DrawRectangle(x0+(0*width)+1, y0+1, width-2, width-2, Yellow);
  LCD_DrawRectangle(x0+(1*width)+1, y0+1, width-2, width-2, Yellow);
  LCD_DrawRectangle(x0+1, y0+(1*width)+1, width-2, width-2, Yellow);
  LCD_DrawRectangle(x0+(1*width)+1, y0+(1*width)+1, width-2, width-2, Yellow);
}

void t_shape(uint16_t x0, uint16_t y0) {
  int i, j;

  if (t_orientation == -1) {
    t_orientation = 3;
  }
  else if (t_orientation == 4) {
    t_orientation = 0;
  }
  
  if (t_orientation == 0) {
    uint8_t m[2][3] = {
      1,1,1,
      0,1,0,
    };
    LCD_DrawRectangle(x0, y0, 2*width, 3*width, White);
    for(i=0; i<2; i++) {
      for(j=0; j<3; j++) {
        if(m[i][j]==1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Blue);
        }
      }
    }
  }
  else if(t_orientation == 1){
    uint8_t m[3][2] = {
      0,1,
      1,1,
      0,1
    };
    LCD_DrawRectangle(x0, y0, 3*width, 2*width, White);
    for(i=0; i<3; i++) {
      for(j=0; j<2; j++) {
        if(m[i][j]==1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Blue);
        }
      }
    }
  }
  else if (t_orientation == 2){
    uint8_t m[2][3] = {
      0,1,0,
      1,1,1
    };
    LCD_DrawRectangle(x0, y0, 2*width, 3*width, White);
    for(i=0; i<2; i++) {
      for(j=0; j<3; j++) {
        if(m[i][j]==1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Blue);
        }
      }
    }
  }
  else if (t_orientation == 3){
    uint8_t m[3][2] = {
      1,0,
      1,1,
      1,0
    };
    LCD_DrawRectangle(x0, y0, 3*width, 2*width, White);
    for(i=0; i<3; i++) {
      for(j=0; j<2; j++) {
        if(m[i][j]==1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Blue);
        }
      }
    }
  }
}

void z_shape(uint16_t x0, uint16_t y0) {
  int i, j;
  if(!z_orientation) {
    uint8_t m[2][3] = {
      1,1,0,
      0,1,1
    };
    for (i=0; i<2; i++) {
      for (j=0; j<3; j++){
        if(m[i][j] == 1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Orange);
        }
      } 
    }
  }
  else {
    uint8_t m[3][2] = {
      0,1,
      1,1,
      1,0
    };
    for (i=0; i<3; i++) {
      for (j=0; j<2; j++){
        if(m[i][j] == 1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Orange);
        }
      } 
    }
  }
}

void s_shape(uint16_t x0, uint16_t y0) {
  int i, j;
  if(!s_orientation) {
    uint8_t m[2][3] = {
      0,1,1,
      1,1,0
    };
    for (i=0; i<2; i++) {
      for (j=0; j<3; j++){
        if(m[i][j] == 1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Cyan);
        }
      } 
    }
  }
  else {
    uint8_t m[3][2] = {
      1,0,
      1,1,
      0,1
    };
    for (i=0; i<3; i++) {
      for (j=0; j<2; j++){
        if(m[i][j] == 1){
          LCD_DrawRectangle(x0+(j*width), y0+(i*width), width, width, Black);
          LCD_DrawRectangle(x0+(j*width)+1, y0+(i*width)+1, width-2, width-2, Cyan);
        }
      } 
    }
  }
}