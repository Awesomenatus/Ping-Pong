#include "game_object.h"
#include <ncurses.h>
#include <unistd.h>

GameObject::GameObject(GameSettings &game_settings) {
  this->playing_field = PlayingField(game_settings.playing_field_settings);
  this->ball = Ball(game_settings.playing_field_settings.x_playing_field / 2, game_settings.playing_field_settings.y_playing_field / 2);
  this->platform.frst_platform = Platform((game_settings.playing_field_settings.x_playing_field - game_settings.platform_length) / 2,
                         game_settings.platform_length);
  this->platform.scnd_platform = Platform((game_settings.playing_field_settings.x_playing_field - game_settings.platform_length) / 2,
                         game_settings.platform_length);
  this->platform_controllers.frst = PlatformControllerFactory::newPlatformController(
      game_settings.ai_settings.AICheck, 'w', 's', game_settings.ai_settings.difficulty);
  this->platform_controllers.scnd = PlatformControllerFactory::newPlatformController(
      0, KEY_UP, KEY_DOWN, game_settings.ai_settings.difficulty);
  this->game_settings = game_settings;
}
