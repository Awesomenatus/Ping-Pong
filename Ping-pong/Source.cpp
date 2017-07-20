#include <iostream>
#include <ncurses.h>
#include "utility.h"
#include "game_settings.h"
#include <unistd.h>

using namespace std;
int main() {
  initscr();
  echo();
  keypad(stdscr, 1);
  cbreak();
  GameSettings game_settings;
  char new_game, new_game_new_value = 'y';
  printw("Do you want to load the settings? (y/n)\n");

  char load;
  scanw("%c", &load);
  do {
    new_game = 0;
    if (new_game_new_value == 'y') {
      int isloaded = 0;
      if (load == 'y') {
        game_settings = LoadSettings(isloaded);
        load = ' ';
      }
      if (!isloaded) {
        game_settings = getGameSettings();
        clear();
        printw("Do you want to save the settings?\n");

        char save;
        scanw("%c", &save);
        if (save == 'y') {
          SaveSettings(game_settings);
          clear();
        }
      }
    }
    refresh();
    Game(game_settings);
    clear();
    printw("Try again?\n");
    scanw("%c", &new_game);
    if (new_game == 'y') {
      printw("Enter new settings?\n");
      scanw("%c", &new_game_new_value);
    }
  } while (new_game == 'y');
  endwin();
  return 0;
}