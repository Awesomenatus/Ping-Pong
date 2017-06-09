#include <iostream>
#include "Platform.h"
#include "Ball.h"
#include <ncurses.h>  //сторонняя библиотека для работы с консолью
#include <unistd.h>
#include <vector>
#include "utility.h"

using namespace std;
int main() {
  initscr();
  echo();
  int xPlayingField, yPlayingField, Platformlength, difficulty;
  char AI;
  bool AICheck;
  printw("Enter the number of rows and columns \n");  // ввод размеров поля
  scanw("%d", &xPlayingField);
  scanw("%d", &yPlayingField);
  PlayingField PlayingField;
  PlayingField.vector = vector<char>(xPlayingField * yPlayingField);
  PlayingField.yPlayingField = yPlayingField;
  printw("Enter the length of the platform\n");  // ввод длинны платформы
  scanw("%d", &Platformlength);
  printw("Second player AI? (y / n)\n");
  scanw("%c", &AI);
  if ((AI == 'y') || (AI == 'Y')) {
    printw("Game difficulty (1-hard,2-normal, 3-easy)\n");  // сложность
    scanw("%d", &difficulty);
    AICheck = 1;
  } else {
    AICheck = 0;
  }
  // **** создание объектов
  PlatformAI frstAI(Platformlength, ((xPlayingField - Platformlength) / 2),
                    difficulty);
  PlatformPlayer frst(Platformlength, ((xPlayingField - Platformlength) / 2));
  PlatformPlayer scnd(Platformlength, ((xPlayingField - Platformlength) / 2));
  Ball ball(xPlayingField / 2, yPlayingField / 2);
  //*****
  // создание стартового состояния
  Fill_vector_all_space(PlayingField, xPlayingField);

  Fill_vector_border(PlayingField, xPlayingField);

  Fill_vector_platform(PlayingField, scnd.getxCoordinate(), scnd.getlength(),
                       PlayingField.yPlayingField - 3);
  Fill_vector_platform(PlayingField, frst.getxCoordinate(), frst.getlength(),
                       2);
  Fill_vector_platform(PlayingField, frstAI.getxCoordinate(),
                       frstAI.getlength(), 2);

  Fill_vector_ball(PlayingField, ball.getX(), ball.getY());
  Draw_field(PlayingField, xPlayingField);
  //*****
  while (true)  // цикл обработки нажатий и движения мячика
  {
    noecho();
    int n;
    usleep(80000);
    keypad(stdscr, 1);
    nodelay(stdscr, 1);
    n = getch();
    switch (n) {
      case KEY_UP:
        Fill_vector_space(PlayingField,
                          Position(scnd.getxCoordinate() + scnd.getlength() - 1,
                                   PlayingField.yPlayingField,
                                   PlayingField.yPlayingField - 3));
        scnd.MoveUp();
        break;
      case KEY_DOWN:
        Fill_vector_space(
            PlayingField,
            Position(scnd.getxCoordinate(), PlayingField.yPlayingField,
                     PlayingField.yPlayingField - 3));
        scnd.MoveDown(xPlayingField);
        break;
    }
    if (!AICheck) {
      switch (n) {
        case 'w':
          Fill_vector_space(
              PlayingField,
              Position(frst.getxCoordinate() + frst.getlength() - 1,
                       PlayingField.yPlayingField, 2));
          frst.MoveUp();
          break;
        case 's':
          Fill_vector_space(
              PlayingField,
              Position(frst.getxCoordinate(), PlayingField.yPlayingField, 2));
          frst.MoveDown(xPlayingField);
          break;
      }
    } else {
      int tmp =
          frstAI.Move(xPlayingField, yPlayingField, ball.getX(), ball.getY());
      if (tmp == 1)
        Fill_vector_space(PlayingField,
                          Position(frstAI.getxCoordinate() - 1,
                                   PlayingField.yPlayingField, 2));
      else if (tmp == -1)
        Fill_vector_space(PlayingField,
                          Position(frstAI.getxCoordinate() + frstAI.getlength(),
                                   PlayingField.yPlayingField, 2));
    }
    if (n == 27)
      break;
    nodelay(stdscr, 0);
    Fill_vector_space(
        PlayingField,
        Position(ball.getX(), PlayingField.yPlayingField, ball.getY()));
    ball.move(PlayingField);
    if (Draw_win(ball.getY(), PlayingField.yPlayingField)) {
      break;
    }
    if (AICheck) {
      Fill_vector_platform(PlayingField, frstAI.getxCoordinate(),
                           frstAI.getlength(), 2);
    } else {
      Fill_vector_platform(PlayingField, frst.getxCoordinate(),
                           frst.getlength(), 2);
    }
    Fill_vector_platform(PlayingField, scnd.getxCoordinate(), scnd.getlength(),
                         PlayingField.yPlayingField - 3);
    Fill_vector_ball(PlayingField, ball.getX(), ball.getY());
    clear();
    Draw_field(PlayingField, xPlayingField);
  }
  refresh();
  sleep(3);
  endwin();
  return 0;
}