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

void Ball::move(PlayingField playing_field) {
  int Potential =
      (xCoordinate + XMove) * playing_field.getY() + (yCoordinate + YMove);
  if ((playing_field.getChar(Potential) == '|') &&
      ((playing_field.getChar(Potential - XMove * playing_field.getY()) ==
        ' '))) {
    xChange();
    yChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  if (playing_field.getChar(Potential) == 'X') {
    xChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  if (playing_field.getChar(Potential) == '|') {
    yChange();
    Potential = (xCoordinate + XMove) * (yCoordinate + YMove);
  }

  xCoordinate += XMove;
  yCoordinate += YMove;
}
