#include <vector>
#include "Platform.h"
#include "Ball.h"
#include <ncurses.h>
#include "utility.h"

PlayingField::PlayingField(int x, int y) {
  this->y_playing_field = y;
  this->x_playing_field = x;
  this->Vector = std::vector<char>(x * y);
}

int PlayingField::Position(int x, int y) {
  return (x * y_playing_field + y);
}

void PlayingField::setChar(int pos, char c) {
  this->Vector.at(pos) = c;
}

char PlayingField::getChar(int pos) {
  return (this->Vector.at(pos));
}

bool PlayingField::drawField(Platform platform_1,
                             Platform platform_2,
                             Ball ball) {
  clear();
  curs_set(0);
  bool res;
  if (ball.getY() == 1) {
    printw("The player on the right won");
    res = 1;
  } else if (ball.getY() == y_playing_field - 2) {
    printw("The player on the left won");
    res = 1;
  } else {
    for (int count = 0; count < (x_playing_field * y_playing_field); count++) {
      this->setChar(count, ' ');
    };

    for (int count = 0; count < x_playing_field; count++) {
      this->setChar(this->Position(count, 0), 'X');
      this->setChar(this->Position(count, y_playing_field - 1), 'X');
    }
    for (int count = 0; count < this->getY(); count++) {
      this->setChar(this->Position(0, count), 'X');
      this->setChar(this->Position(x_playing_field - 1, count), 'X');
    }

    this->setChar(this->Position(ball.getX(), ball.getY()), 'o');

    for (int count = platform_1.getxCoordinate();
         count != (platform_1.getxCoordinate() + platform_1.getlength());
         count++) {
      this->setChar(this->Position(count, 2), '|');
    }
    for (int count = platform_2.getxCoordinate();
         count != (platform_2.getxCoordinate() + platform_2.getlength());
         count++) {
      this->setChar(this->Position(count, (this->y_playing_field) - 3), '|');
    }

    for (int x = 0; x < (x_playing_field * y_playing_field); x++) {
      if (((x % (y_playing_field)) == 0) && (x != 0)) {
        addch('\n');
      }
      addch(this->getChar(x));
    }
    res = 0;
  }
  refresh();
  return res;
}
