#ifndef H_BALL
#define H_BALL
#include <vector>
#include "Platform.h"

class Ball {
 protected:
  int xCoordinate;
  int yCoordinate;
  int XMove;
  int YMove;

 public:
  Ball(int x, int y);
  void xChange();
  void yChange();
  void move(Platform platform_1,
            Platform platform_2,
            int x_playing_field,
            int y_playing_field);
  int getX() const { return xCoordinate; };
  int getY() const { return yCoordinate; };
};

#endif