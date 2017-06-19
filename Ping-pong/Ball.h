#ifndef H_BALL
#define H_BALL
#include <vector>
#include "Platform.h"
#include "game_settings.h"

class Ball {
 protected:
  int xCoordinate;
  int yCoordinate;
  int XMove;
  int YMove;

 public:
  Ball(int x, int y);
  Ball();
  void xChange();
  void yChange();
  void move(Platform platform_1,
            Platform platform_2,
            PlayingFieldSettings playing_field_settings);
  int getX() const { return xCoordinate; };
  int getY() const { return yCoordinate; };
};

#endif