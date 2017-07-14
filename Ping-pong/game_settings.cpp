#include "game_settings.h"
#include <ncurses.h>
#include <fstream>
#include <string>

int EnterValue(std::string String, int left, int right) {
  int res;
  clear();
  printw(String.c_str(), right, left);
  scanw("%d", &res);
  while ((res < left) || (res > right)) {
    clear();
    printw("Try again \n");
    printw(String.c_str(), right, left);
    scanw("%d", &res);
  };
  return res;
}

PlayingFieldSettings SetPlayingField(int rows_min,
                                     int cols_min,
                                     int mx,
                                     int my) {
  PlayingFieldSettings playing_field;
  playing_field.x_playing_field =
      EnterValue("Enter the number of rows (less than %i but more than %i) \n",
                 rows_min, mx);

  playing_field.y_playing_field = EnterValue(
      "Enter the number of columns (less than %i but more than %i)\n", cols_min,
      my);
  return playing_field;
}

int SetPlatform(int x_playing_field) {
  return EnterValue("Enter the length of the platform (less than %i)\n", 1,
                    x_playing_field / 5);
}

GameSettings getGameSettings() {
  GameSettings game_settings;
  const int rows_min = 12, cols_min = 20;
  int mx, my;
  char AI;
  getmaxyx(stdscr, mx, my);

  printw("You want play online?\n");
  char network;
  scanw("%c", &network);
  if (network == 'y') {
    game_settings.ai_settings.AICheck = 0;
    game_settings.ai_settings.difficulty = 0;
    game_settings.network.isNetwork = 1;
    printw("You want to be server?\n");
    char server;
    scanw("%c", &server);
    if (server == 'y') {
      game_settings.playing_field_settings =
          SetPlayingField(rows_min, cols_min, mx, my);

      game_settings.platform_length =
          SetPlatform(game_settings.playing_field_settings.x_playing_field);

      game_settings.network.isServer = 1;

    } else {
      printw("Enter server's IP\n");
      auto& IPServer = game_settings.network.IPServer;
      IPServer.reserve(16);
      scanw("%16s", IPServer.data());

      game_settings.network.isServer = 0;
    }
  } else {
    game_settings.network.isNetwork = 0;

    game_settings.playing_field_settings =
        SetPlayingField(rows_min, cols_min, mx, my);

    game_settings.platform_length =
        SetPlatform(game_settings.playing_field_settings.x_playing_field);

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
  }
  return game_settings;
}

bool SaveSettings(GameSettings game_settings) {
  std::ofstream fout("settings", std::ios_base::out | std::ios_base::trunc);
  if (!fout.is_open()) {
    printw("File can't be open or create\n");
    return 0;
  }
  fout << "Rows number     "
       << game_settings.playing_field_settings.x_playing_field << "\n";
  fout << "Cols number     "
       << game_settings.playing_field_settings.y_playing_field << "\n";
  fout << "Platform length " << game_settings.platform_length << "\n";
  fout << "AI?             " << game_settings.ai_settings.AICheck << "\n";
  fout << "AI difficulty   " << game_settings.ai_settings.difficulty << "\n";
  fout << "Is network?     " << game_settings.network.isNetwork << "\n";
  fout << "Is server?      " << game_settings.network.isServer << "\n";
  fout << "Server IP       " << game_settings.network.IPServer << "\n";
  fout.close();
  return 1;
}

GameSettings LoadSettings(int& isloaded) {
  GameSettings game_settings;
  std::string tmp;
  std::ifstream fin("settings", std::ios::in);
  if (fin.is_open()) {
    std::getline(fin, tmp);
    game_settings.playing_field_settings.x_playing_field =
        std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.playing_field_settings.y_playing_field =
        std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.platform_length = std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.ai_settings.AICheck = std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.ai_settings.difficulty =
        std::stoi(tmp.substr(tmp.rfind(" ")));
    std::getline(fin, tmp);
    game_settings.network.isNetwork = std::stoi(tmp.substr(tmp.rfind(" ")));;
    std::getline(fin, tmp);
    game_settings.network.isServer = std::stoi(tmp.substr(tmp.rfind(" ")));;
    if (game_settings.network.isNetwork && !game_settings.network.isServer) {
      std::getline(fin, tmp);
      game_settings.network.IPServer = std::stoi(tmp.substr(tmp.rfind(" ")));;
    }
    isloaded = 1;
    fin.close();
  } else {
    isloaded = 0;
    printw("Unable to open file\n");
  }
  return game_settings;
}

GameSettings::GameSettings() {
  playing_field_settings.y_playing_field = 0;
  playing_field_settings.x_playing_field = 0;
  platform_length = 0;
  ai_settings.difficulty = 0;
  ai_settings.AICheck = 0;
  network.isNetwork = 0;
  network.isServer = 0;
  network.IPServer = "";
}