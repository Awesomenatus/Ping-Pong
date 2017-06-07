#include "Ball.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

Ball::Ball(int x, int y) {
  srand(time(0));
  xCoordinate = x;
  yCoordinate = y;
  (rand() % 10 + 1 < 5)
      ? XMove = -1
      : XMove = 1;  // случайное изначальное направление движения
  (rand() % 10 + 1 < 5) ? YMove = -1 : YMove = 1;
}

void Ball::xChange() {
  XMove = -XMove;
}

void Ball::yChange() {
  YMove = -YMove;
}

void Ball::move(const std::vector<std::vector<char> >& PlayingField) {
  int xPotential = xCoordinate + XMove;
  int yPotential = yCoordinate + YMove;
  if ((PlayingField[xPotential][yPotential] == '|') &&
      ((PlayingField[xPotential - XMove][yPotential] == ' '))) {
    xChange();
    yChange();
    xPotential = xCoordinate + XMove;
    yPotential = yCoordinate + YMove;
  }

  if (PlayingField[xPotential][yPotential] == 'X') {
    xChange();
    xPotential = xCoordinate + XMove;
  }

  if (PlayingField[xPotential][yPotential] == '|') {
    yChange();
    yPotential = yCoordinate + YMove;
  }

  xCoordinate += XMove;
  yCoordinate += YMove;
}
