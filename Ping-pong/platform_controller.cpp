#include "platform_controller.h"

PlatformController::~PlatformController() {}

void PlatformControllerPlayer::setkeyUP(int c) {
  this->keyUP = c;
}

void PlatformControllerPlayer::setkeyDown(int c) {
  this->keyDown = c;
}

PlatformControllerPlayer::PlatformControllerPlayer(int up, int down) {
  this->keyUP = up;
  this->keyDown = down;
}

PlatformControllerPlayer::~PlatformControllerPlayer() {}

void PlatformControllerPlayer::Move(GameSettings game_settings,
                                    Platform& platform,
                                    Ball ball,
                                    int key) {
  if (key == keyUP) {
    if (platform.getxCoordinate() > 1)
      platform.MoveUp();
  } else if (key == keyDown) {
    if ((platform.getxCoordinate() + platform.getlength()) <
        (game_settings.playing_field_settings.x_playing_field - 1))
      platform.MoveDown();
  }
}

PlatformControllerAI::PlatformControllerAI(int difficulty) {
  this->difficulty = difficulty;
}

PlatformControllerAI::~PlatformControllerAI() {}

void PlatformControllerAI::SetDifficulty(int x) {
  this->difficulty = x;
}

void PlatformControllerAI::Move(GameSettings game_settings,
                                Platform& platform,
                                Ball ball,
                                int key) {
  if ((ball.getY() < (game_settings.playing_field_settings.y_playing_field / difficulty))) {
    if ((platform.getxCoordinate() + platform.getlength() / 2 < ball.getX()) &&
        ((platform.getxCoordinate() + platform.getlength()) <
         (game_settings.playing_field_settings.x_playing_field - 1))) {
      platform.MoveDown();
    } else if ((platform.getxCoordinate() + platform.getlength() / 2 >
                ball.getX()) &&
               (platform.getxCoordinate() > 1)) {
      platform.MoveUp();
    }
  }
}