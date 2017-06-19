#ifndef H_PLATFORM
#define H_PLATFORM

class Platform {
 public:
  Platform(int yCoordinate, int length);
  Platform();
  int getlength() const { return length; };
  void setlength(int x);
  int getxCoordinate() const { return xCoordinate; };
  void setxCoordinate(int x);
  void MoveUp();
  void MoveDown();

 protected:
  int length;
  int xCoordinate;
};
#endif