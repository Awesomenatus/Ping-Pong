#include "Ball.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

Ball::Ball(int x, int y) {
  srand(time(0));
  xCoordinate = x;
  yCoordinate = y;
  (rand() % 10 + 1 < 5) ? XMove = -1 : XMove = 1;
  (rand() % 10 + 1 < 5) ? YMove = -1 : YMove = 1;
}

void Ball::xChange() {
  XMove = -XMove;
}

void Ball::yChange() {
  YMove = -YMove;
}

void Ball::move(Platform platform_1,
                Platform platform_2,
                int x_playing_field,
                int y_playing_field) {
  int xPotential = (xCoordinate + XMove);
  int yPotential = (yCoordinate + YMove);
  if (((xPotential == platform_1.getxCoordinate()) && (yPotential == 2)) ||
      ((xPotential == platform_2.getxCoordinate()) &&
       (yPotential == (y_playing_field - 3)))) {
    xChange();
    yChange();
    xPotential = (xCoordinate + XMove);
    yPotential = (yCoordinate + YMove);
  }
  if (((xPotential ==
        (platform_1.getxCoordinate() + platform_1.getlength() - 1)) &&
       (yPotential == 2)) ||
      ((xPotential ==
        (platform_2.getxCoordinate() + platform_2.getlength() - 1)) &&
       (yPotential == (y_playing_field - 3)))) {
    xChange();
    yChange();
    xPotential = (xCoordinate + XMove);
    yPotential = (yCoordinate + YMove);
  }
  if ((xPotential == 0) || (xPotential == (x_playing_field - 1))) {
    xChange();
    xPotential = (xCoordinate + XMove);
  }

  if (((xPotential > platform_1.getxCoordinate()) &&
       (xPotential < (platform_1.getxCoordinate() + platform_1.getlength())) &&
       (yPotential == 2)) ||
      (((xPotential > platform_2.getxCoordinate())) &&
       (xPotential < (platform_2.getxCoordinate() + platform_2.getlength())) &&
       (yPotential == (y_playing_field - 3)))) {
    yChange();
    yPotential = (yCoordinate + YMove);
  }

  xCoordinate += XMove;
  yCoordinate += YMove;
}
