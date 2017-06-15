#include "Platform.h"
#include <ncurses.h>

Platform::Platform(int xCoordinate, int length) {
  this->length = length;
  this->xCoordinate = xCoordinate;
}

void Platform::setlength(int x) {
  this->length = x;
}

void Platform::setxCoordinate(int x) {
  this->xCoordinate = x;
}

void Platform::MoveUp() {
  this->xCoordinate--;
}

void Platform::MoveDown() {
  this->xCoordinate++;
}
