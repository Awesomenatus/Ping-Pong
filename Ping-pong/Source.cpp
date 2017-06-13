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
  PlatformAI frstAI(platform_length, ((x_playing_field - platform_length) / 2),
                    difficulty);
  PlatformPlayer frst(platform_length,
                      ((x_playing_field - platform_length) / 2));
  PlatformPlayer scnd(platform_length,
                      ((x_playing_field - platform_length) / 2));
  Ball ball(x_playing_field / 2, y_playing_field / 2);
  if (AICheck)
    playing_field.drawField(frstAI, scnd, ball);
  else
    playing_field.drawField(frst, scnd, ball);
  while (true) {
    noecho();
    int n;
    usleep(80000);
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    n = getch();
    switch (n) {
      case KEY_UP:
        scnd.MoveUp();
        break;
      case KEY_DOWN:
        scnd.MoveDown(x_playing_field);
        break;
    }
    if (!AICheck) {
      switch (n) {
        case 'w':
          frst.MoveUp();
          break;
        case 's':
          frst.MoveDown(x_playing_field);
          break;
      }
      ball.move(frst, scnd, x_playing_field, y_playing_field);
    } else {
      frstAI.Move(x_playing_field, y_playing_field, ball.getX(), ball.getY());
      ball.move(frstAI, scnd, x_playing_field, y_playing_field);
    }
    if (n == 27)
      break;
    nodelay(stdscr, 0);
    if (AICheck) {
      if (playing_field.drawField(frstAI, scnd, ball)) {
        break;
      }
    } else {
      if (playing_field.drawField(frst, scnd, ball)) {
        break;
      }
    }
  }
  sleep(3);
  endwin();
  return 0;
}
