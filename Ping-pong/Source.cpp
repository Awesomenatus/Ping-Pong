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
  char AI;
  bool AICheck;
  getmaxyx(stdscr, mx, my);

  printw("Enter the number of rows (less than %i but more than 5) \n", mx);
  scanw("%d", &x_playing_field);
  while ((x_playing_field < 5) || (x_playing_field > mx)) {
    clear();
    printw("Try again \n");
    printw("Enter the number of rows (less than %i but more than 5) \n", mx);
    scanw("%d", &x_playing_field);
  };

  clear();
  printw("Enter the number of columns (less than %i but more than 10)\n", my);
  scanw("%d", &y_playing_field);
  while ((y_playing_field < 10) || (y_playing_field > my)) {
    clear();
    printw("Try again \n");
    printw("Enter the number of columns (less than %i but more than 10)\n", my);
    scanw("%d", &y_playing_field);
  };

  clear();
  printw("Enter the length of the platform (less than %i atleast by 2)\n",
         x_playing_field);
  scanw("%d", &platform_length);
  while ((platform_length > (x_playing_field - 2)) && (platform_length < 1)) {
    clear();
    printw("Try again \n");
    printw("Enter the length of the platform (less than %i atleast by 2)\n",
           x_playing_field);
    scanw("%d", &platform_length);
  };

  clear();
  printw("Second player AI? (y / n)\n");
  scanw("%c", &AI);
  while ((AI != 'y') && (AI != 'n')) {
    clear();
    printw("Try again \n");
    printw("Second player AI? (y / n)\n");
    scanw("%d", &AI);
  };

  clear();
  if ((AI == 'y') || (AI == 'Y')) {
    printw("Game difficulty (1-hard,2-normal, 3-easy)\n");
    scanw("%d", &difficulty);
    while ((difficulty < 1) || (difficulty > 3)) {
      clear();
      printw("Try again \n");
      printw("Game difficulty (1-hard,2-normal, 3-easy)\n");
      scanw("%d", &difficulty);
    };
    AICheck = 1;
  } else {
    AICheck = 0;
  }
  PlayingField playing_field(x_playing_field, y_playing_field);
  Ball ball(x_playing_field / 2, y_playing_field / 2);
  Platform frst_platform((x_playing_field - platform_length) / 2,
                         platform_length);
  Platform scnd_platform((x_playing_field - platform_length) / 2,
                         platform_length);
  auto frst = PlatformControllerFactory::newPlatformController(AICheck, 'w',
                                                               's', difficulty);
  auto scnd = PlatformControllerFactory::newPlatformController(
      0, KEY_UP, KEY_DOWN, difficulty);
  playing_field.drawField(frst_platform, scnd_platform, ball);
  while (true) {
    noecho();
    usleep(80000);
    nodelay(stdscr, 1);
    int n = getch();
    frst->Move(playing_field, frst_platform, ball, n);
    scnd->Move(playing_field, scnd_platform, ball, n);
    ball.move(frst_platform, scnd_platform, x_playing_field, y_playing_field);
    if (n == 27)
      break;
    nodelay(stdscr, 0);
    if (playing_field.drawField(frst_platform, scnd_platform, ball)) {
      break;
    }
  }
  sleep(3);
  endwin();
  return 0;
}