#include "Platform.h"
#include "Ball.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "game_settings.h"

Ball::Ball(int x, int y) {
  srand(time(0));
  xCoordinate = x;
  yCoordinate = y;
  (rand() % 10 + 1 < 5) ? XMove = -1 : XMove = 1;
  (rand() % 10 + 1 < 5) ? YMove = -1 : YMove = 1;
}

Ball::Ball() {
  xCoordinate = 0;
  yCoordinate = 0;
  XMove = 0;
  YMove = 0;  
}
void Ball::xChange() {
  XMove = -XMove;
}

void Ball::yChange() {
  YMove = -YMove;
}

void Ball::move(Platform platform_1,
                Platform platform_2,
                PlayingFieldSettings playing_field_settings) {
  int xPotential = (xCoordinate + XMove);
  int yPotential = (yCoordinate + YMove);
  if (((xPotential == platform_1.getxCoordinate()) && (yPotential == 2) &&
       (XMove == 1)) ||
      ((xPotential == platform_2.getxCoordinate()) &&
       (yPotential == (playing_field_settings.y_playing_field - 3)) && (XMove == 1))) {
    xChange();
    yChange();
    xPotential = (xCoordinate + XMove);
    yPotential = (yCoordinate + YMove);
  }
  if (((xPotential ==
        (platform_1.getxCoordinate() + platform_1.getlength() - 1)) &&
       (yPotential == 2) && (XMove == -1)) ||
      ((xPotential ==
        (platform_2.getxCoordinate() + platform_2.getlength() - 1)) &&
       (yPotential == (playing_field_settings.y_playing_field - 3)) && (XMove == -1))) {
    xChange();
    yChange();
    xPotential = (xCoordinate + XMove);
    yPotential = (yCoordinate + YMove);
  }
  if ((xPotential == 0) || (xPotential == (playing_field_settings.x_playing_field - 1))) {
    xChange();
    xPotential = (xCoordinate + XMove);
  }

  if (((xPotential >= platform_1.getxCoordinate()) &&
       (xPotential <= (platform_1.getxCoordinate() + platform_1.getlength())) &&
       (yPotential == 2)) ||
      ((xPotential >= platform_2.getxCoordinate()) &&
       (xPotential <= (platform_2.getxCoordinate() + platform_2.getlength())) &&
       (yPotential == (playing_field_settings.y_playing_field - 3)))) {
    yChange();
    yPotential = (yCoordinate + YMove);
  }

  xCoordinate += XMove;
  yCoordinate += YMove;
}
