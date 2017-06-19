#include "game_settings.h"
#include <ncurses.h>
#include <fstream>
#include <string>

int EnterValue(std::string String, int left, int right) {
  int res;
  clear();
  printw(String.c_str(), right);
  scanw("%d", &res);
  while ((res < left) || (res > right)) {
    clear();
    printw("Try again \n");
    printw(String.c_str(), right);
    scanw("%d", &res);
  };
  return res;
}

GameSettings getGameSettings() {
  GameSettings game_settings;
  int mx, my;
  bool AICheck;
  char AI;
  getmaxyx(stdscr, mx, my);

  game_settings.playing_field_settings.x_playing_field = EnterValue(
    "Enter the number of rows (less than %i but more than 12) \n", 12, mx);

  game_settings.playing_field_settings.y_playing_field = EnterValue(
    "Enter the number of columns (less than %i but more than 20)\n", 20, my);

  game_settings.platform_length =
    EnterValue("Enter the length of the platform (less than %i)\n", 1,
                     game_settings.playing_field_settings.x_playing_field / 5);

  clear();
  printw("Second player AI? (y / n)\n");
  scanw("%c", &AI);
  while ((AI != 'y') && (AI != 'n')) {
    clear();
    printw("Try again \n");
    printw("Second player AI? (y / n)\n");
    scanw("%c", &AI);
  };

  if ((AI == 'y') || (AI == 'Y')) {
    game_settings.ai_settings.difficulty =
       EnterValue("Game difficulty (1-hard,2-normal, 3-easy)\n", 1, 3);
    game_settings.ai_settings.AICheck = 1;
  } else {
    game_settings.ai_settings.AICheck = 0;
    game_settings.ai_settings.difficulty = 0;
  }
  return game_settings;
}

bool SaveSettings (GameSettings game_settings) {
  std::ofstream fout("settings", std::ios_base::out | std::ios_base::trunc);
  if (!fout.is_open())
  {
   printw("File can't be open or create\n");
   return 0;
  }
  fout << "Rows number     " << game_settings.playing_field_settings.x_playing_field << "\n";
  fout << "Cols number     " << game_settings.playing_field_settings.y_playing_field << "\n";
  fout << "Platform length " << game_settings.platform_length << "\n";
  fout << "AI?             " << game_settings.ai_settings.AICheck << "\n";
  fout << "AI difficulty   " << game_settings.ai_settings.difficulty << "\n";
  fout.close();
  return 1;
}

GameSettings LoadSettings () {
  GameSettings game_settings;
  std::string tmp;
  std::ifstream fin("settings", std::ios::in);
  if (fin.is_open())
  {
    std::getline(fin, tmp);
    game_settings.playing_field_settings.x_playing_field = std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.playing_field_settings.y_playing_field = std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.platform_length = std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.ai_settings.AICheck = std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.ai_settings.difficulty = std::stoi(tmp.substr(tmp.rfind(" ")));
    fin.close();
  }
  else printw("Unable to open file"); 
  return game_settings;
}