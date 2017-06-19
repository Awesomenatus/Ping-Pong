#include <ncurses.h>
#include "playing_field.h"

PlayingField::PlayingField(PlayingFieldSettings& playing_field_setting) {
  this->playing_field_settings = playing_field_setting;
  this->Vector = std::vector<char>(playing_field_setting.x_playing_field *
                                   playing_field_setting.y_playing_field);
}

PlayingField::PlayingField() {
  // this->playing_field_settings = nullptr;
  // this->Vector = std::vector<char>(0);
}

int PlayingField::Position(int x, int y) {
  return (x * playing_field_settings.y_playing_field + y);
}

void PlayingField::setChar(int pos, char c) {
  this->Vector.at(pos) = c;
}

char PlayingField::getChar(int pos) {
  return (this->Vector.at(pos));
}