#ifndef H_GAMEOBJECT
#define H_GAMEOBJECT
#include "Platform.h"
#include "platform_controller.h"
#include "playing_field.h"
#include "Ball.h"
#include "game_settings.h"
#include <memory>

struct Platforms {
  Platform frst_platform;
  Platform scnd_platform;
};

struct PlatformControllers {
  std::unique_ptr<PlatformController> frst;
  std::unique_ptr<PlatformController> scnd;
};

struct GameObject {
  GameObject(GameSettings &game_settings);
  PlayingField playing_field;
  Ball ball;
  Platforms platform;
  PlatformControllers platform_controllers;
  GameSettings game_settings;
};

#endif