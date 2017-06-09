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

void Ball::move(PlayingField PlayingField) {
  int Potential = (xCoordinate + XMove) * PlayingField.yPlayingField +
                  (yCoordinate + YMove);
  if ((PlayingField.vector[Potential] == '|') &&
      ((PlayingField.vector[Potential - XMove * PlayingField.yPlayingField] ==
        ' '))) {
    xChange();
    yChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  if (PlayingField.vector[Potential] == 'X') {
    xChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  if (PlayingField.vector[Potential] == '|') {
    yChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  xCoordinate += XMove;
  yCoordinate += YMove;
}
