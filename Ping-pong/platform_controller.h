#ifndef H_PLATFORMCONTROLLER
#define H_PLATFORMCONTROLLER

#include "game_settings.h"
#include "Ball.h"
#include "Platform.h"
#include <memory>

class PlatformController {
 public:
  virtual void Move(GameSettings game_settings,
                    Platform& platorm,
                    Ball ball,
                    int key) = 0;
  virtual ~PlatformController();
};

class PlatformControllerPlayer : public PlatformController {
 protected:
  int keyUP;
  int keyDown;

 public:
  PlatformControllerPlayer(int up, int down);
  void Move(GameSettings game_settings, Platform& platform, Ball ball, int key);
  void setkeyUP(int c);
  void setkeyDown(int c);
  virtual ~PlatformControllerPlayer();
};

class PlatformControllerAI : public PlatformController {
 protected:
  int difficulty;

 public:
  PlatformControllerAI(int difficulty);
  void SetDifficulty(int difficulty);
  void Move(GameSettings game_settings, Platform& platform, Ball ball, int key);
  virtual ~PlatformControllerAI();
};

class PlatformControllerFactory {
 public:
  static std::unique_ptr<PlatformController>
  newPlatformController(bool check, int up, int down, int difficulty) {
    if (check)
      return std::unique_ptr<PlatformController>(
          new PlatformControllerAI(difficulty));
    else
      return std::unique_ptr<PlatformController>(
          new PlatformControllerPlayer(up, down));
  }
};

#endif