#ifndef H_PLAYINGFIELD
#define H_PLAYINGFIELD

#include "game_settings.h"
#include <vector>

class PlayingField {
 protected:
  std::vector<char> Vector;
  PlayingFieldSettings playing_field_settings;

 public:
  PlayingField(PlayingFieldSettings& playing_field_settings);
  PlayingField();
  int Position(int x, int y);
  void setChar(int pos, char c);
  char getChar(int pos);
  int getX() const { return playing_field_settings.x_playing_field; };
  int getY() const { return playing_field_settings.y_playing_field; };
};
#endif