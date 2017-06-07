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

void Ball::move(const std::vector<char>& PlayingField, int yPlayingField) {
  int Potential = (xCoordinate + XMove) * yPlayingField + (yCoordinate + YMove);
  if ((PlayingField[Potential] == '|') &&
      ((PlayingField[Potential - XMove * yPlayingField] == ' '))) {
    xChange();
    yChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  if (PlayingField[Potential] == 'X') {
    xChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  if (PlayingField[Potential] == '|') {
    yChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  xCoordinate += XMove;
  yCoordinate += YMove;
}
