#ifndef H_BALL
#define H_BALL
#include <vector>

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
  void move(const std::vector<char> & PlayingField, int yPlayingField);
  int getX() const { return xCoordinate; };
  int getY() const { return yCoordinate; };
};

#endif