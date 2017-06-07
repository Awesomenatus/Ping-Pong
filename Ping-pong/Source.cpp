#include <iostream>
#include "Platform.h"
#include "Ball.h"
#include <ncurses.h>  //сторонняя библиотека для работы с консолью
#include <unistd.h>
#include <vector>

using namespace std;
int main() {
  initscr();
  echo();
  int xPlayingField, yPlayingField, Platformlength, difficulty;
  char AI;
  bool AICheck;
  printw("Enter the number of rows and columns \n");  // ввод размеров поля (я
  // не стал писать
  // конструкции типа try
  // catch, надеясь на вашу
  // сознательность)
  scanw("%d", &xPlayingField);
  scanw("%d", &yPlayingField);
  vector<char> PlayingField;
  printw("Enter the length of the platform\n");  // ввод длинны платформы
  scanw("%d", &Platformlength);
  printw("Second player AI? (y / n)\n");
  scanw("%c", &AI);
  if (AI == 'y') {
    printw("Game difficulty (1-hard,2-normal, 3-easy)\n");  // сложность
    scanw("%d", &difficulty);
    AICheck = TRUE;
  } else {
    AICheck = FALSE;
  }
  // **** создание объектов
  PlatformAI frstAI(Platformlength, ((xPlayingField - Platformlength) / 2),
                    difficulty);
  PlatformPlayer frst(Platformlength, ((xPlayingField - Platformlength) / 2));
  PlatformPlayer scnd(Platformlength, ((xPlayingField - Platformlength) / 2));

  Ball ball(xPlayingField / 2, yPlayingField / 2);
  //*****
  // создание стартового состояния
  for (int x = 0; x < xPlayingField*yPlayingField-1; x++) {
    PlayingField.push_back(' ');
  };
  for (int count = 0; count < xPlayingField; count++) {
    PlayingField[0+count*yPlayingField] = 'X';
	PlayingField[yPlayingField-1+count*yPlayingField] = 'X';
  };
  for (int count = 0; count < yPlayingField; count++) {
    PlayingField[0+count] = 'X';
    PlayingField[0+(xPlayingField-1)*yPlayingField+count] = 'X';
  };
  for (int i = scnd.getxCoordinate();
       i != (scnd.getxCoordinate() + scnd.getlength()); i++) {
    PlayingField[yPlayingField - 3 + i*yPlayingField] = '|';
  };
  for (int i = frstAI.getxCoordinate();
       i != (frstAI.getxCoordinate() + frstAI.getlength()); i++) {
    PlayingField[2+i*yPlayingField] = '|';
  };
  for (int i = frst.getxCoordinate();
       i != (frst.getxCoordinate() + frst.getlength()); i++) {
    PlayingField[2+i*yPlayingField] = '|';
  };

  PlayingField[ball.getX()*yPlayingField+ball.getY()] = 'o';
  for (int x = 0; x < xPlayingField*yPlayingField; x++) {
	if (((x%(yPlayingField))==0) && (x!=0)) {
	  addch('\n');
	}
    addch(PlayingField[x]);
  }
  //*****
  clear();
  while (true)  // цикл обработки нажатий и движения мячика
  {
    noecho();
    int n;
    usleep(80000);
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    n = getch();
    switch (n) {
      case KEY_UP:
        PlayingField[yPlayingField - 3 + ((scnd.getxCoordinate()+scnd.getlength()-1)*yPlayingField)] = ' ';
        scnd.MoveUp();
        break;
      case KEY_DOWN:
        PlayingField[scnd.getxCoordinate()*yPlayingField + yPlayingField - 3] = ' ';
        scnd.MoveDown(xPlayingField);
        break;
    }
    if (!AICheck) {
      switch (n) {
        case 'w':
          PlayingField[(frst.getxCoordinate() + frst.getlength()-1) * yPlayingField + 2] = ' ';
          frst.MoveUp();
          break;
        case 's':
          PlayingField[frst.getxCoordinate() * yPlayingField + 2] = ' ';
          frst.MoveDown(xPlayingField);
          break;
      }
    } else {
      int tmp =
          frstAI.Move(xPlayingField, yPlayingField, ball.getX(), ball.getY());
      if (tmp == 1) 
		PlayingField[(frstAI.getxCoordinate()-1) * yPlayingField + 2] = ' ';
      else if (tmp == -1) 
		PlayingField[(frstAI.getxCoordinate() + frstAI.getlength()) * yPlayingField + 2] = ' ';
    }
    if (n == 27)
      break;
    nodelay(stdscr, FALSE);
    PlayingField[ball.getX() * yPlayingField + ball.getY()] = ' ';
    ball.move(PlayingField, yPlayingField);
    if (ball.getY() == 1) {
      printw("\nThe player on the right won");
      break;
    }
    if (ball.getY() == yPlayingField - 2) {
      printw("\nThe player on the left won");
      break;
    }
    if (AICheck) {
	  for (int i = frstAI.getxCoordinate();
		   i != (frstAI.getxCoordinate() + frstAI.getlength()); i++) {
		PlayingField[2+i*yPlayingField] = '|';
	  }}
		else {
		  for (int i = frst.getxCoordinate();
		       i != (frst.getxCoordinate() + frst.getlength()); i++) {
	        PlayingField[2+i*yPlayingField] = '|';
  		  }	
		}
	for (int i = scnd.getxCoordinate();
    	  i != (scnd.getxCoordinate() + scnd.getlength()); i++) {
	  PlayingField[yPlayingField - 3 + i*yPlayingField] = '|';
	};
    PlayingField[ball.getX() * yPlayingField + ball.getY()] = 'o';
    clear();
    for (int x = 0; x < xPlayingField*yPlayingField; x++) {
	  if (((x%(yPlayingField))==0) && (x!=0)) {
	  addch('\n');
	  }
    addch(PlayingField[x]);
  }
    refresh();
  }
  refresh();
  sleep(3);
  endwin();
  return 0;
}