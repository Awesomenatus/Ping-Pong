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
  Fill_vector_all_space(playing_field);

  Fill_vector_border(playing_field);

  Fill_vector_platform(playing_field, scnd.getxCoordinate(), scnd.getlength(),
                       playing_field.getY() - 3);
  Fill_vector_platform(playing_field, frst.getxCoordinate(), frst.getlength(),
                       2);
  Fill_vector_platform(playing_field, frstAI.getxCoordinate(),
                       frstAI.getlength(), 2);

  Fill_vector_ball(playing_field, ball.getX(), ball.getY());
  Draw_field(playing_field);
  while (true) {
    noecho();
    int n;
    usleep(80000);
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    n = getch();
    switch (n) {
      case KEY_UP:
        Fill_vector_space(playing_field,
                          scnd.getxCoordinate() + scnd.getlength() - 1,
                          playing_field.getY() - 3);
        scnd.MoveUp();
        break;
      case KEY_DOWN:
        Fill_vector_space(playing_field, scnd.getxCoordinate(),
                          playing_field.getY() - 3);
        scnd.MoveDown(x_playing_field);
        break;
    }
    if (!AICheck) {
      switch (n) {
        case 'w':
          Fill_vector_space(playing_field,
                            frst.getxCoordinate() + frst.getlength() - 1, 2);
          frst.MoveUp();
          break;
        case 's':
          Fill_vector_space(playing_field, frst.getxCoordinate(), 2);
          frst.MoveDown(x_playing_field);
          break;
      }
    } else {
      int tmp = frstAI.Move(x_playing_field, y_playing_field, ball.getX(),
                            ball.getY());
      if (tmp == 1)
        Fill_vector_space(playing_field, frstAI.getxCoordinate() - 1, 2);
      else if (tmp == -1)
        Fill_vector_space(playing_field,
                          frstAI.getxCoordinate() + frstAI.getlength(), 2);
    }
    if (n == 27)
      break;
    nodelay(stdscr, 0);
    Fill_vector_space(playing_field, ball.getX(), ball.getY());
    ball.move(playing_field);
    if (Draw_win(ball.getY(), playing_field.getY())) {
      break;
    }
    if (AICheck) {
      Fill_vector_platform(playing_field, frstAI.getxCoordinate(),
                           frstAI.getlength(), 2);
    } else {
      Fill_vector_platform(playing_field, frst.getxCoordinate(),
                           frst.getlength(), 2);
    }
    Fill_vector_platform(playing_field, scnd.getxCoordinate(), scnd.getlength(),
                         playing_field.getY() - 3);
    Fill_vector_ball(playing_field, ball.getX(), ball.getY());
    clear();
    Draw_field(playing_field);
  }
  refresh();
  sleep(3);
  endwin();
  return 0;
}