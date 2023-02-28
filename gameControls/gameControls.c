#include "LPC17xx.h"
#include "gameControls.h"
#include "../shapes/shapes.h"
#include "../GLCD_advanced/GLCD.h"

// uint8_t gameMatrix [11][10] = {
//   0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,0,0,
//   0,0,0,0,7,0,0,0,0,0,
//   2,0,6,0,7,0,6,0,0,0,
//   2,0,6,6,7,7,6,6,0,8,
//   2,3,3,6,4,5,5,6,0,8,
//   2,3,3,4,4,4,5,5,8,8,
//   1,1,1,1,1,1,1,1,1,1
// };
uint8_t gameMatrix [11][10] = {
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1
};

int points = 0;

void drawMatrix() {
  int i, j, x, y;
  for(i=0; i<11; i++) {
    for(j=0; j<10; j++) {
      x = j*24;
      y = i*24+80;
      switch (gameMatrix[i][j]) {
        case 0:
          deleteBaseSquare(x, y);
          break;
        case 2:
          drawBaseSquare(x,y,Red);
          break;
        case 3:
          drawBaseSquare(x,y,Yellow);
          break;
        case 4:
          drawBaseSquare(x,y,Green);
          break;
        case 5:
          drawBaseSquare(x,y,Blue);
          break;
        case 6:
          drawBaseSquare(x,y,Cyan);
          break;
        case 7:
          drawBaseSquare(x,y,Magenta);
          break;
        case 8:
          drawBaseSquare(x,y,Orange);
          break;
      }
    }
  }
}

void clearGlitch(void){
  int i, j, x, y;
  for(i=0; i<11; i++) {
    for(j=0; j<10; j++) {
      x = j*24;
      y = i*24+80;
      if (gameMatrix[i][j] == 0) {
        deleteBaseSquare(x, y);
      }
    }
  }
}

void checkMatrix(){
  int i, j, k, l, x, y, fullCells = 0, matrixChanged = 0;
  for(i=0; i<10; i++) {
    for(j=0; j<10; j++) {
      if(gameMatrix[i][j] == 0){
        continue;
      }
      else {
        fullCells++;
      }
    }
    if(fullCells == 10) {
      points++;
      drawPoints();
      matrixChanged = 1;
      for(k=0; k<10; k++){
        gameMatrix[i][k] = 0;
      }
      for(k=i; k>=0; k--){
        for(l=0; l<10; l++) {
          if(k)
            gameMatrix[k][l] = gameMatrix[k-1][l];
          else
            gameMatrix[k][l] = 0;
        }
      }
    }
    fullCells = 0;
  }

  if(matrixChanged){
    drawMatrix();
    matrixChanged = 0;
  }
}

void drawPoints() {
  char s[10];
  sprintf(s, "%d", points-1);
  GUI_Text(180, 30, (uint8_t*)s, White, White);
  sprintf(s, "%d", points);
  GUI_Text(180, 30, (uint8_t*)s, Black, White);
  GUI_Text(180, 10, (uint8_t*)"Points:", Black, White);
}

uint8_t initPosX = 4, initPosY = 0, posX, posY, prevPosX, prevPosY, actualShape;