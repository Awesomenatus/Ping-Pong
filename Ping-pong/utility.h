#ifndef H_UTILITY
#define H_UTILITY

#include <memory>
#include "game_object.h"

void DrawField(GameObject& game_object, Score& score);

void PrepareGame(GameObject& game_object, Score& score);

int GameControl(GameObject& game_object, Score& score);

void Game(GameSettings& game_settings);

int ScoreCount(GameObject& game_object, Score& score);
#endif