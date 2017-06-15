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
  int x_playing_field, y_playing_field, platform_length, difficulty;
  char AI;
  bool AICheck;
  printw("Enter the number of rows and columns \n");
  scanw("%d", &x_playing_field);
  scanw("%d", &y_playing_field);
  PlayingField playing_field(x_playing_field, y_playing_field);
  printw("Enter the length of the platform\n");
  scanw("%d", &platform_length);
  printw("Second player AI? (y / n)\n");
  scanw("%c", &AI);
  if ((AI == 'y') || (AI == 'Y')) {
    printw("Game difficulty (1-hard,2-normal, 3-easy)\n");
    scanw("%d", &difficulty);
    AICheck = 1;
  } else {
    AICheck = 0;
  }
  Ball ball(x_playing_field / 2, y_playing_field / 2);
  Platform frst_platform((x_playing_field - platform_length) / 2,
                         platform_length);
  Platform scnd_platform((x_playing_field - platform_length) / 2,
                         platform_length);
  PlatformController* frst = PlatformControllerFactory::newPlatformController(
      AICheck, 'w', 's', difficulty);
  PlatformController* scnd = PlatformControllerFactory::newPlatformController(
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