#include "Platform.h"

void Platform::setlength(int x) {
  this->length = x;
}

void Platform::setxCoordinate(int x) {
  this->xCoordinate = x;
}

PlatformPlayer::PlatformPlayer(int x, int y) {
  setlength(x);
  setxCoordinate(y);
}

void PlatformPlayer::MoveUp() {
  if (xCoordinate > 1)
    this->xCoordinate--;
}

void PlatformPlayer::MoveDown(int x_playing_field) {
  if ((xCoordinate + length) < x_playing_field - 1)
    this->xCoordinate++;
}

PlatformAI::PlatformAI(int x, int y, int difficulty) {
  setlength(x);
  setxCoordinate(y);
  SetDifficulty(difficulty);
}

void PlatformAI::SetDifficulty(int x) {
  this->difficulty = x;
}

int PlatformAI::Move(int x_playing_field,
                     int y_playing_field,
                     int BallX,
                     int BallY) {
  if ((BallY < (y_playing_field / difficulty))) {
    if ((xCoordinate + length / 2 < BallX) &&
        ((xCoordinate + length) < (x_playing_field - 1))) {
      this->xCoordinate++;
      return 1;
    } else if ((xCoordinate + length / 2 > BallX) && (xCoordinate > 1)) {
      this->xCoordinate--;
      return -1;
    }
  }
  return 0;
}