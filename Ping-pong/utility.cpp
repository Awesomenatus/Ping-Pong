#include <vector>
#include "Platform.h"
#include <ncurses.h>
#include "utility.h"

PlayingField::PlayingField(int x, int y) {
  this->y_playing_field = y;
  this->x_playing_field = x;
  this->Vector = std::vector<char>(x * y);
}

int PlayingField::Position(int x, int y) {
  return (x * y_playing_field + y);
}

void PlayingField::setChar(int pos, char c) {
  this->Vector.at(pos) = c;
}

char PlayingField::getChar(int pos) {
  return (this->Vector.at(pos));
}

void Draw_field(PlayingField& PlayingField) {
  clear();
  curs_set(0);
  for (int x = 0; x < PlayingField.getX() * PlayingField.getY(); x++) {
    if (((x % (PlayingField.getY())) == 0) && (x != 0)) {
      addch('\n');
    }
    addch(PlayingField.getChar(x));
  }
  refresh();
}

bool Draw_win(int BallY, int y_playing_field) {
  if (BallY == 1) {
    printw("\nThe player on the right won");
    return 1;
  }
  if (BallY == y_playing_field - 2) {
    printw("\nThe player on the left won");
    return 1;
  }
  return 0;
}

void Fill_vector_platform(PlayingField& PlayingField,
                          int Coordinate,
                          int Length,
                          int Pos) {
  for (int count = Coordinate; count != (Coordinate + Length); count++) {
    PlayingField.setChar(PlayingField.Position(count, Pos), '|');
  }
}

void Fill_vector_border(PlayingField& PlayingField) {
  for (int count = 0; count < PlayingField.getX(); count++) {
    PlayingField.setChar(PlayingField.Position(count, 0), 'X');
    PlayingField.setChar(PlayingField.Position(count, PlayingField.getY() - 1),
                         'X');
  }
  for (int count = 0; count < PlayingField.getY(); count++) {
    PlayingField.setChar(PlayingField.Position(0, count), 'X');
    PlayingField.setChar(PlayingField.Position(PlayingField.getX() - 1, count),
                         'X');
  }
}

void Fill_vector_ball(PlayingField& PlayingField, int xBall, int yBall) {
  PlayingField.setChar(PlayingField.Position(xBall, yBall), 'o');
}

void Fill_vector_all_space(PlayingField& PlayingField) {
  for (int count = 0; count < (PlayingField.getX() * PlayingField.getY());
       count++) {
    PlayingField.setChar(count, ' ');
  };
}

void Fill_vector_space(PlayingField& PlayingField, int x, int y) {
  int pos = PlayingField.Position(x, y);
  PlayingField.setChar(pos, ' ');
}