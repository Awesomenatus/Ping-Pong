#include "Platform.h"
#include <vector>
#include "draw.h"
#include <ncurses.h>
void Draw::Draw_field(std::vector<char>& PlayingField,
                int xPlayingField,
                int yPlayingField) {
  clear();
  curs_set(0);
  for (int x = 0; x < xPlayingField * yPlayingField; x++) {
    if (((x % (yPlayingField)) == 0) && (x != 0)) {
      addch('\n');
    }
    addch(PlayingField[x]);
  }
  refresh();
}

bool Draw::Draw_win(int BallY, int yPlayingField) {
	if (BallY == 1) {
    printw("\nThe player on the right won");
		return 1;
  }
  if (BallY == yPlayingField - 2) {
    printw("\nThe player on the left won");
    return 1;
  }
	return 0;
}