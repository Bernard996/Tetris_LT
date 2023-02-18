#include "../GLCD_advanced/GLCD.h"
#include "LPC17xx.h"
#include "shapes.h"
#include "../gameControls/gameControls.h"

const uint16_t width = 24;
int8_t line_orientation = 0;
int8_t z_orientation = 0;
int8_t s_orientation = 0;
int8_t t_orientation = 0;

uint8_t line(uint16_t x0, uint16_t y0){
  uint8_t i, j, canMove = 1;

  if (!line_orientation){
    for (i = 0; i < 4; i++){
      if (gameMatrix[y0][x0 + i] != 0){
        canMove = 0;
        break;
      }
    }
    if (canMove){
      x0 = x0 * 24;
      y0 = y0 * 24 + 80;
      for(i=0; i < 4; i++){
        deleteBaseSquare((24*prevPosX)+(24*i),24*prevPosY+80);
      }
      for(i=0; i < 4; i++){
        drawBaseSquare(x0+(24*i),y0,Red);
      }
      return 1;
    }
    else {
      for (i = 0; i < 4; i++) {
        gameMatrix[y0][x0 + i] = 0;
      }
    }
  }
  else{
    for (i = 0; i < 4; i++){
        if (gameMatrix[y0 + i][x0] != 0){
          canMove = 0;
          break;
        }
    }
    if (canMove){
      x0 = x0 * 24;
      y0 = y0 * 24 + 80;
      for(i=0; i<4; i++) {
        deleteBaseSquare(24*prevPosX,(24*prevPosY)+(24*i)+80);
      }
      for(i=0; i<4; i++) {
        drawBaseSquare(x0, y0+(24*i), Red);
      }
      return 1;
    }
    else {
      gameMatrix[y0 + i][x0] = 0;
    }
  }
  return 0;
}

uint8_t cube(uint16_t x0, uint16_t y0){
  uint8_t canMove = 1, i, j;

  if(x0 - prevPosX == -1){
    if(gameMatrix[x0][y0] != 0 || gameMatrix[x0][y0+1] != 0){
      canMove = 0;
    }
  }
  else if(x0 + prevPosX == 0) {
    if(gameMatrix[x0][y0+1] != 0 || gameMatrix[x0+1][y0+1] != 0){
      canMove = 0;
    }
  }
  else {
    if(gameMatrix[x0+1][y0] != 0 || gameMatrix[x0+1][y0+1] != 0){
      canMove = 0;
    }
  }


  // for (i = 0; i < 2; i++){
  //   for (j = 0; j < 2; j++){
  //     if (gameMatrix[y0 + i][x0 + j] != 0){
  //       canMove = 0;
  //       break;
  //     }
  //   }
  // }

  if (canMove){
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++){
        gameMatrix[prevPosY + i][prevPosX + j] = 0;
      }
    }
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++){
        gameMatrix[y0 + i][x0 + j] = 3;
      }
    }

    x0 = x0 * 24;
    y0 = y0 * 24 + 80;
    LCD_DrawRectangle(prevPosX * 24, prevPosY * 24 + 80, 2 * width, 2 * width, White);
    LCD_DrawRectangle(x0, y0, width * 2, width * 2, Black);
    LCD_DrawRectangle(x0 + (0 * width) + 1, y0 + 1, width - 2, width - 2, Yellow);
    LCD_DrawRectangle(x0 + (1 * width) + 1, y0 + 1, width - 2, width - 2, Yellow);
    LCD_DrawRectangle(x0 + 1, y0 + (1 * width) + 1, width - 2, width - 2, Yellow);
    LCD_DrawRectangle(x0 + (1 * width) + 1, y0 + (1 * width) + 1, width - 2, width - 2, Yellow);
    return 1;
  }
  return 0;
}

uint8_t t_shape(uint16_t x0, uint16_t y0)
{
  int i, j;

  x0 = x0 * 24;
  y0 = y0 * 24 + 80;

  if (t_orientation == -1)
  {
    t_orientation = 3;
  }
  else if (t_orientation == 4)
  {
    t_orientation = 0;
  }

  if (t_orientation == 0)
  {
    uint8_t m[2][3] = {
        1,
        1,
        1,
        0,
        1,
        0,
    };
    LCD_DrawRectangle(x0, y0, 2 * width, 3 * width, White);
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < 3; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Blue);
        }
      }
    }
  }
  else if (t_orientation == 1)
  {
    uint8_t m[3][2] = {
        0, 1,
        1, 1,
        0, 1};
    LCD_DrawRectangle(x0, y0, 3 * width, 2 * width, White);
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 2; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Blue);
        }
      }
    }
  }
  else if (t_orientation == 2)
  {
    uint8_t m[2][3] = {
        0, 1, 0,
        1, 1, 1};
    LCD_DrawRectangle(x0, y0, 2 * width, 3 * width, White);
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < 3; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Blue);
        }
      }
    }
  }
  else if (t_orientation == 3)
  {
    uint8_t m[3][2] = {
        1, 0,
        1, 1,
        1, 0};
    LCD_DrawRectangle(x0, y0, 3 * width, 2 * width, White);
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 2; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Blue);
        }
      }
    }
  }
}

uint8_t z_shape(uint16_t x0, uint16_t y0)
{
  int i, j;

  x0 = x0 * 24;
  y0 = y0 * 24 + 80;
  if (!z_orientation)
  {
    uint8_t m[2][3] = {
        1, 1, 0,
        0, 1, 1};
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < 3; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Orange);
        }
      }
    }
  }
  else
  {
    uint8_t m[3][2] = {
        0, 1,
        1, 1,
        1, 0};
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 2; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Orange);
        }
      }
    }
  }
}

uint8_t s_shape(uint16_t x0, uint16_t y0)
{
  int i, j;

  x0 = x0 * 24;
  y0 = y0 * 24 + 80;
  if (!s_orientation)
  {
    uint8_t m[2][3] = {
        0, 1, 1,
        1, 1, 0};
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < 3; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Cyan);
        }
      }
    }
  }
  else
  {
    uint8_t m[3][2] = {
        1, 0,
        1, 1,
        0, 1};
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 2; j++)
      {
        if (m[i][j] == 1)
        {
          LCD_DrawRectangle(x0 + (j * width), y0 + (i * width), width, width, Black);
          LCD_DrawRectangle(x0 + (j * width) + 1, y0 + (i * width) + 1, width - 2, width - 2, Cyan);
        }
      }
    }
  }
}

void drawBaseSquare(uint8_t x0, uint8_t y0, uint16_t Color) {
  LCD_DrawRectangle(x0, y0, 24, 24, Black);
  LCD_DrawRectangle(x0+1, y0+1, 22, 22, Color);
}

void deleteBaseSquare(uint8_t x0, uint8_t y0) {
  LCD_DrawRectangle(x0, y0, 24, 24, White);
}