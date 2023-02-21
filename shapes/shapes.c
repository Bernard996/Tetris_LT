#include "../GLCD_advanced/GLCD.h"

#include "LPC17xx.h"

#include "shapes.h"

#include "../gameControls/gameControls.h"

const uint16_t width = 24;
uint8_t line_or = 0;
uint8_t z_or = 0;
uint8_t s_or = 0;
uint8_t t_or = 0;
uint8_t ll_or = 0;
uint8_t rl_or = 0;
uint8_t t_or_old = 0;
uint8_t s_or_old = 0;
uint8_t z_or_old = 0;
uint8_t ll_or_old = 0;
uint8_t rl_or_old = 0;
uint8_t goingDown = 1;

uint8_t line(uint16_t x0, uint16_t y0) {
  uint8_t i, j, canMove = 1;

  if (!line_or) {
    for (i = 0; i < 4; i++) {
      if (gameMatrix[y0][x0 + i] != 0) {
        canMove = 0;
        break;
      }
    }
    if (canMove) {
      x0 = x0 * 24;
      y0 = y0 * 24 + 80;
      for (i = 0; i < 4; i++) {
        deleteBaseSquare((24 * prevPosX) + (24 * i), 24 * prevPosY + 80);
      }
      for (i = 0; i < 4; i++) {
        drawBaseSquare(x0 + (24 * i), y0, Red);
      }
      return 1;
    } 
    else {
      if(goingDown){
        y0--;
        for (i = 0; i < 4; i++) {
          gameMatrix[y0][x0 + i] = 2;
        }
        return 0;
      }
      else {
        goingDown = 1;
        return 2;
      }
    }
  } 
  else {
    for (i = 0; i < 4; i++) {
      if (gameMatrix[y0 + i][x0] != 0) {
        canMove = 0;
        break;
      }
    }
    if (canMove) {
      x0 = x0 * 24;
      y0 = y0 * 24 + 80;
      for (i = 0; i < 4; i++) {
        deleteBaseSquare(24 * prevPosX, (24 * prevPosY) + (24 * i) + 80);
      }
      for (i = 0; i < 4; i++) {
        drawBaseSquare(x0, y0 + (24 * i), Red);
      }
      return 1;
    } 
    else {
      if(goingDown){
        y0--;
        for (i = 0; i < 4; i++) {
          gameMatrix[y0 + i][x0] = 2;
        }
        return 0;
      }
      else {
        goingDown = 1;
        return 2;
      }
    }
  }
}

uint8_t cube(uint16_t x0, uint16_t y0) {
  uint8_t canMove = 1, i, j;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      if (gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    x0 = x0 * 24;
    y0 = y0 * 24 + 80;

    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++) {
        deleteBaseSquare((24 * prevPosX) + (24 * j), (24 * prevPosY) + (24 * i) + 80);
      }
    }
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++) {
        drawBaseSquare(x0 + (24 * i), y0 + (24 * j), Yellow);
      }
    }
    return 1;
  } 
  else {
    if(goingDown){
      y0--;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
          gameMatrix[y0 + i][x0 + j] = 3;
        }
      }
      return 0;
    }
    else {
      goingDown = 1;
      return 2;
    }
  }
}

uint8_t t_shape(uint16_t x0, uint16_t y0) {
  
  uint8_t shapes[4][3][3] = {
    {
      1,1,1,
      0,1,0,
      0,0,0
    },
    {
      0,1,0,
      1,1,0,
      0,1,0
    },
    {
      0,1,0,
      1,1,1,
      0,0,0
    },
    {
      1,0,0,
      1,1,0,
      1,0,0
    }
  };
  int i, j, canMove = 1;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (shapes[t_or][i][j] == 1 && gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[t_or_old][i][j] == 1) {
          deleteBaseSquare((prevPosX + j) * 24, (prevPosY + i) * 24 + 80);
        }
      }
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[t_or][i][j] == 1) {
          drawBaseSquare((x0 + j) * 24, (y0 + i) * 24 + 80, Green);
        }
      }
    }
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[t_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 4;
          }
        }
      }
      return 0;
    }
    else {
      goingDown = 1;
      return 2;
    }
  }

  t_or_old = t_or;

  return 1;
}

uint8_t z_shape(uint16_t x0, uint16_t y0) {
  uint8_t shapes[2][3][3] = {
    {
      1,1,0,
      0,1,1,
      0,0,0
    },
    {
      0,1,0,
      1,1,0,
      1,0,0
    }
  };
  int i, j, canMove = 1;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (shapes[z_or][i][j] == 1 && gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[z_or_old][i][j] == 1) {
          deleteBaseSquare((prevPosX + j) * 24, (prevPosY + i) * 24 + 80);
        }
      }
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[z_or][i][j] == 1) {
          drawBaseSquare((x0 + j) * 24, (y0 + i) * 24 + 80, Blue);
        }
      }
    }
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[z_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 4;
          }
        }
      }
      return 0;
    }
    else {
      goingDown = 1;
      return 2;
    }
  }

  z_or_old = z_or;

  return 1;
}

uint8_t s_shape(uint16_t x0, uint16_t y0) {
  uint8_t shapes[2][3][3] = {
    {
      0,1,1,
      1,1,0,
      0,0,0
    },
    {
      1,0,0,
      1,1,0,
      0,1,0
    }
  };
  int i, j, canMove = 1;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (shapes[s_or][i][j] == 1 && gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[s_or_old][i][j] == 1) {
          deleteBaseSquare((prevPosX + j) * 24, (prevPosY + i) * 24 + 80);
        }
      }
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[s_or][i][j] == 1) {
          drawBaseSquare((x0 + j) * 24, (y0 + i) * 24 + 80, Cyan);
        }
      }
    }
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[s_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 4;
          }
        }
      }
      return 0;
    }
    else {
      goingDown = 1;
      return 2;
    }
  }

  s_or_old = s_or;

  return 1;
}

uint8_t ll_shape(uint16_t x0, uint16_t y0) {
  uint8_t shapes[4][3][3] = {
    {
      0,0,1,
      1,1,1,
      0,0,0
    },
    {
      1,0,0,
      1,0,0,
      1,1,0
    },
    {
      1,1,1,
      1,0,0,
      0,0,0
    },
    {
      1,1,0,
      0,1,0,
      0,1,0
    }
  };
  int i, j, canMove = 1;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (shapes[ll_or][i][j] == 1 && gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[ll_or_old][i][j] == 1) {
          deleteBaseSquare((prevPosX + j) * 24, (prevPosY + i) * 24 + 80);
        }
      }
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[ll_or][i][j] == 1) {
          drawBaseSquare((x0 + j) * 24, (y0 + i) * 24 + 80, Magenta);
        }
      }
    }
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[ll_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 4;
          }
        }
      }
      return 0;
    }
    else {
      goingDown = 1;
      return 2;
    }
  }

  ll_or_old = ll_or;

  return 1;
}

uint8_t rl_shape(uint16_t x0, uint16_t y0) {
  uint8_t shapes[4][3][3] = {
    {
      1,0,0,
      1,1,1,
      0,0,0
    },
    {
      1,1,0,
      1,0,0,
      1,0,0
    },
    {
      1,1,1,
      0,0,1,
      0,0,0
    },
    {
      0,1,0,
      0,1,0,
      1,1,0
    }
  };
  int i, j, canMove = 1;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (shapes[rl_or][i][j] == 1 && gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[rl_or_old][i][j] == 1) {
          deleteBaseSquare((prevPosX + j) * 24, (prevPosY + i) * 24 + 80);
        }
      }
    }
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        if (shapes[rl_or][i][j] == 1) {
          drawBaseSquare((x0 + j) * 24, (y0 + i) * 24 + 80, Orange);
        }
      }
    }
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[rl_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 4;
          }
        }
      }
      return 0;
    }
    else {
      goingDown = 1;
      return 2;
    }
  }

  rl_or_old = rl_or;

  return 1;
}

void drawBaseSquare(uint8_t x0, uint16_t y0, uint16_t Color) {
  LCD_DrawRectangle(x0, y0, 24, 24, Black);
  LCD_DrawRectangle(x0 + 1, y0 + 1, 22, 22, Color);
}

void deleteBaseSquare(uint8_t x0, uint16_t y0) {
  LCD_DrawRectangle(x0, y0, 24, 24, White);
}