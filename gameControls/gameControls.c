#include "LPC17xx.h"
#include "gameControls.h"
#include "../shapes/shapes.h"
#include "../GLCD_advanced/GLCD.h"

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

void checkMatrix(){
  int i, j, k, l, x, y, fullCells = 0;
  for(i=0; j<11; j++) {
    for(j=0; j<10; j++) {
      if(gameMatrix[i][j] == 0){
        continue;
      }
      else {
        fullCells++;
      }
    }
    if(fullCells == 10) {
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
  }

  for(i=0; j<11; j++) {
    for(j=0; j<10; j++) {
      x = j*24;
      y = j*24+80;
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

uint8_t initPosX = 4, initPosY = 0, posX, posY, prevPosX, prevPosY, actualShape;