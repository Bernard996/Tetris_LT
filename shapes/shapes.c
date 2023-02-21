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
uint8_t line_or_old = 0;
uint8_t t_or_old = 0;
uint8_t z_or_old = 0;
uint8_t s_or_old = 0;
uint8_t ll_or_old = 0;
uint8_t rl_or_old = 0;
uint8_t goingDown = 1;

uint8_t line(uint16_t x0, uint16_t y0) {
  uint8_t shapes[2][4][4] = {
    {
      1,1,1,1,
      0,0,0,0,
      0,0,0,0,
      0,0,0,0
    },
    {
      1,0,0,0,
      1,0,0,0,
      1,0,0,0,
      1,0,0,0
    }
  };
  int i, j, canMove = 1;

  if(x0 < 0 || ((line_or == 0 && x0 > 6) || (line_or == 1 && x0 > 9))){
    return 3;
  }

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (shapes[line_or][i][j] == 1 && gameMatrix[y0 + i][x0 + j] != 0) {
        canMove = 0;
        break;
      }
    }
  }

  if (canMove) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        if (shapes[line_or_old][i][j] == 1) {
          deleteBaseSquare((prevPosX + j) * 24, (prevPosY + i) * 24 + 80);
        }
      }
    }
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
        if (shapes[line_or][i][j] == 1) {
          drawBaseSquare((x0 + j) * 24, (y0 + i) * 24 + 80, Red);
        }
      }
    }
    line_or_old = line_or;
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
          if(shapes[line_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 2;
          }
        }
      }
      line_or = 0;
      line_or_old = 0;
      return 0;
    }
    else {
      goingDown = 1;
      line_or = line_or_old;
      return 2;
    }
  }
}

uint8_t cube(uint16_t x0, uint16_t y0) {
  uint8_t canMove = 1, i, j;

  if(x0 < 0 || x0 > 8){
    return 3;
  }

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

  if(x0 < 0 || 
     (((t_or == 0 || t_or == 2) && x0 > 7)) || 
     (((t_or == 1 || t_or == 3) && x0 > 8))
    ) 
  {
    return 3;
  }

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
    t_or_old = t_or;
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
      t_or = 0;
      t_or_old = 0;
      return 0;
    }
    else {
      goingDown = 1;
      t_or = t_or_old;
      return 2;
    }
  }
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

  if(x0 < 0 || 
     ((z_or == 0 && x0 > 7)) || 
     ((z_or == 1 && x0 > 8))
    ) 
  {
    return 3;
  }

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
    z_or_old = z_or;
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[z_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 5;
          }
        }
      }
      z_or_old = 0;
      z_or = 0;
      return 0;
    }
    else {
      goingDown = 1;
      z_or = z_or_old;
      return 2;
    }
  }
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

  if(x0 < 0 || 
     ((s_or == 0 && x0 > 7)) || 
     ((s_or == 1 && x0 > 8))
    ) 
  {
    return 3;
  }

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
    s_or_old = s_or;
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[s_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 6;
          }
        }
      }
      s_or_old = 0;
      s_or = 0;
      return 0;
    }
    else {
      goingDown = 1;
      s_or = s_or_old;
      return 2;
    }
  }
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

  if(x0 < 0 || 
     (((ll_or == 0 || ll_or == 2) && x0 > 7)) || 
     (((ll_or == 1 || ll_or == 3) && x0 > 8))
    ) 
  {
    return 3;
  }

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
    ll_or_old = ll_or;
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[ll_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 7;
          }
        }
      }
      ll_or_old = 0;
      ll_or = 0;
      return 0;
    }
    else {
      goingDown = 1;
      ll_or = ll_or_old;
      return 2;
    }
  }
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

  if(x0 < 0 || 
     (((rl_or == 0 || rl_or == 2) && x0 > 7)) || 
     (((rl_or == 1 || rl_or == 3) && x0 > 8))
    ) 
  {
    return 3;
  }

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
    rl_or_old = rl_or;
    return 1;
  } 
  else {
    if(goingDown){
      for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
          if(shapes[rl_or][i][j] == 1) {
            gameMatrix[prevPosY+i][prevPosX+j] = 8;
          }
        }
      }
      rl_or_old = 0;
      rl_or = 0;
      return 0;
    }
    else {
      goingDown = 1;
      rl_or = rl_or_old;
      return 2;
    }
  }
}

void drawBaseSquare(uint8_t x0, uint16_t y0, uint16_t Color) {
  LCD_DrawRectangle(x0, y0, 24, 24, Black);
  LCD_DrawRectangle(x0 + 1, y0 + 1, 22, 22, Color);
}

void deleteBaseSquare(uint8_t x0, uint16_t y0) {
  LCD_DrawRectangle(x0, y0, 24, 24, White);
}