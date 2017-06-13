#ifndef H_UTILITY
#define H_UTILITY

#include <vector>
#include "Platform.h"
#include "Ball.h"

class PlayingField {
 protected:
  std::vector<char> Vector;
  int y_playing_field;
  int x_playing_field;

 public:
  PlayingField(int x, int y);
  int Position(int x, int y);
  void setChar(int pos, char c);
  char getChar(int pos);
  int getX() const { return x_playing_field; };
  int getY() const { return y_playing_field; };
  bool drawField(Platform platform_1, Platform platform_2, Ball ball);
};

#endif