#include <iostream>
#include <ncurses.h>
#include "utility.h"
#include "game_settings.h"
#include "game_object.h"
#include <unistd.h>

using namespace std;
int main() {
  initscr();
  echo();
  keypad(stdscr, 1);
  cbreak();
  GameSettings game_settings;
  int prepare_time = 0, speed = 80000, prepare_count = 0, i;
  char AI, new_game, new_game_new_value = 'y', save, load;
  bool AICheck;

  do {
    new_game = 0;

    if (new_game_new_value == 'y') {
      printw("Do you want to load the settings?\n");
      scanw("%c", &load);
      if (load == 'y') {
        game_settings = LoadSettings();
        clear();
      } else {
        game_settings = getGameSettings();
        clear();
        printw("Do you want to save the settings?\n");
        scanw("%c", &save);
        if (save == 'y') {
          SaveSettings(game_settings);
          clear();
        }
      }
    }
    refresh();
    Game(game_settings);
    sleep(2);
    echo();
    clear();
    printw("Restart game?\n");
    scanw("%c", &new_game);
    if (new_game == 'y') {
      printw("Enter new value?\n");
      scanw("%c", &new_game_new_value);
    }
  } while (new_game == 'y');
  endwin();
  return 0;
}