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

class PlatformController {
 public:
  virtual void Move(PlayingField playing_field,
                    Platform& platorm,
                    Ball ball,
                    int key) = 0;
};

class PlatformControllerPlayer
    : public PlatformController  // Дочерний класс игрока/игроков
{
 protected:
  int keyUP;
  int keyDown;

 public:
  PlatformControllerPlayer(int up, int down);
  void Move(PlayingField playing_field, Platform& platform, Ball ball, int key);
  void setkeyUP(int c);
  void setkeyDown(int c);
};

class PlatformControllerAI : public PlatformController  // Дочерний класс ИИ
{
 protected:
  int difficulty;

 public:
  PlatformControllerAI(int difficulty);
  void SetDifficulty(int difficulty);
  void Move(PlayingField playing_field, Platform& platform, Ball ball, int key);
};

class PlatformControllerFactory {
 public:
  static PlatformController* newPlatformController(bool check,
                                                   int up,
                                                   int down,
                                                   int difficulty) {
    if (check)
      return new PlatformControllerAI(difficulty);
    else
      return new PlatformControllerPlayer(up, down);
  }
};

#endif