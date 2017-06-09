#include <vector>
#include "Platform.h"
#include <ncurses.h>
#include "utility.h"

int Position(int x, int y, int z) {
  return (x * y + z);
}

void Draw_field(PlayingField& PlayingField, int xPlayingField) {
  clear();
  curs_set(0);
  for (int x = 0; x < xPlayingField * PlayingField.yPlayingField; x++) {
    if (((x % (PlayingField.yPlayingField)) == 0) && (x != 0)) {
      addch('\n');
    }
    addch(PlayingField.vector[x]);
  }
  refresh();
}

bool Draw_win(int BallY, int yPlayingField) {
  if (BallY == 1) {
    printw("\nThe player on the right won");
    return 1;
  }
  if (BallY == yPlayingField - 2) {
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
    PlayingField.vector[Position(count, PlayingField.yPlayingField, Pos)] = '|';
  }
}

void Fill_vector_border(PlayingField& PlayingField, int xPlayingField) {
  for (int count = 0; count < xPlayingField; count++) {
    PlayingField.vector.at(Position(count, PlayingField.yPlayingField, 0)) =
        'X';
    PlayingField.vector.at(Position(count, PlayingField.yPlayingField,
                                    PlayingField.yPlayingField - 1)) = 'X';
  }
  for (int count = 0; count < PlayingField.yPlayingField; count++) {
    PlayingField.vector.at(Position(0, 0, count)) = 'X';
    PlayingField.vector.at(
        Position(xPlayingField - 1, PlayingField.yPlayingField, count)) = 'X';
  }
}

void Fill_vector_ball(PlayingField& PlayingField, int xBall, int yBall) {
  PlayingField.vector[Position(xBall, PlayingField.yPlayingField, yBall)] = 'o';
}

void Fill_vector_all_space(PlayingField& PlayingField, int xPlayingField) {
  for (int count = 0;
       count < (Position(xPlayingField, PlayingField.yPlayingField, -1));
       count++) {
    PlayingField.vector[count] = ' ';
  };
}

void Fill_vector_space(PlayingField& PlayingField, int pos) {
  PlayingField.vector[pos] = ' ';
}