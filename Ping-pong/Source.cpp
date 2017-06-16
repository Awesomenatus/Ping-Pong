#include <iostream>
#include "Platform.h"
#include "Ball.h"
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "utility.h"

using namespace std;
int main() {
  initscr();
  echo();
  keypad(stdscr, 1);
  cbreak();
  int x_playing_field, y_playing_field, platform_length, difficulty, mx, my;
  char AI, new_game, new_game_new_value = 'y';
  bool AICheck;

  do {
    new_game = 0;
    if (new_game_new_value == 'y') {
      getmaxyx(stdscr, mx, my);

      x_playing_field = EnterValue(
          "Enter the number of rows (less than %i but more than 5) \n", 5, mx);

      y_playing_field = EnterValue(
          "Enter the number of columns (less than %i but more than 10)\n", 10,
          my);

      platform_length =
          EnterValue("Enter the length of the platform (less than %i)\n", 1,
                     x_playing_field - 2);

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
        difficulty =
            EnterValue("Game difficulty (1-hard,2-normal, 3-easy)\n", 1, 3);
        AICheck = 1;
      } else {
        AICheck = 0;
      }
    }
    PlayingField playing_field(x_playing_field, y_playing_field);
    Ball ball(x_playing_field / 2, y_playing_field / 2);
    Platform frst_platform((x_playing_field - platform_length) / 2,
                           platform_length);
    Platform scnd_platform((x_playing_field - platform_length) / 2,
                           platform_length);
    auto frst = PlatformControllerFactory::newPlatformController(
        AICheck, 'w', 's', difficulty);
    auto scnd = PlatformControllerFactory::newPlatformController(
        0, KEY_UP, KEY_DOWN, difficulty);
    playing_field.drawField(frst_platform, scnd_platform, ball);
    while (true) {
      noecho();
      usleep(80000);
      cbreak();
      nodelay(stdscr, 1);
      int n = getch();
      nodelay(stdscr, 0);
      frst->Move(playing_field, frst_platform, ball, n);
      scnd->Move(playing_field, scnd_platform, ball, n);
      ball.move(frst_platform, scnd_platform, x_playing_field, y_playing_field);
      if (n == 27)
        break;
      if (playing_field.drawField(frst_platform, scnd_platform, ball)) {
        break;
      }
    }
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