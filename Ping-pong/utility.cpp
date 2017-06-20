#include <vector>
#include <ncurses.h>
#include "utility.h"
#include <string>
#include "game_object.h"
#include <unistd.h>

void DrawField(GameObject& game_object, Score& score) {
  clear();
  curs_set(0);
  for (int count = 0; count < (game_object.playing_field.getX() *
                               game_object.playing_field.getY());
       count++) {
    game_object.playing_field.setChar(count, ' ');
  };

  for (int count = 0; count < game_object.playing_field.getX(); count++) {
    game_object.playing_field.setChar(
        game_object.playing_field.Position(count, 0), 'X');
    game_object.playing_field.setChar(
        game_object.playing_field.Position(
            count, game_object.playing_field.getY() - 1),
        'X');
  }
  for (int count = 0; count < game_object.playing_field.getY(); count++) {
    game_object.playing_field.setChar(
        game_object.playing_field.Position(0, count), 'X');
    game_object.playing_field.setChar(
        game_object.playing_field.Position(game_object.playing_field.getX() - 1,
                                           count),
        'X');
  }

  game_object.playing_field.setChar(
      game_object.playing_field.Position(game_object.ball.getX(),
                                         game_object.ball.getY()),
      'o');

  for (int count = game_object.platform.frst_platform.getxCoordinate();
       count != (game_object.platform.frst_platform.getxCoordinate() +
                 game_object.platform.frst_platform.getlength());
       count++) {
    game_object.playing_field.setChar(
        game_object.playing_field.Position(count, 2), '|');
  }
  for (int count = game_object.platform.scnd_platform.getxCoordinate();
       count != (game_object.platform.scnd_platform.getxCoordinate() +
                 game_object.platform.scnd_platform.getlength());
       count++) {
    game_object.playing_field.setChar(
        game_object.playing_field.Position(
            count, (game_object.playing_field.getY()) - 3),
        '|');
  }

  for (int x = 0; x < (game_object.playing_field.getX() *
                       game_object.playing_field.getY());
       x++) {
    if (((x % (game_object.playing_field.getY())) == 0) && (x != 0)) {
      addch('\n');
    }
    addch(game_object.playing_field.getChar(x));
  }
  printw("\n%i : %i", score.frst_score, score.scnd_score);
  refresh();
}

void PrepareGame(GameObject& game_object, Score& score) {
  int prepare_count = 0, prepare_time = 0;
  DrawField(game_object, score);
  while (prepare_time < 3) {
    usleep(100000);
    cbreak();
    nodelay(stdscr, 1);
    int n = getch();
    nodelay(stdscr, 0);
    if (!game_object.game_settings.ai_settings.AICheck)
      game_object.platform_controllers.frst->Move(
          game_object.game_settings, game_object.platform.frst_platform,
          game_object.ball, n);
    game_object.platform_controllers.scnd->Move(
        game_object.game_settings, game_object.platform.scnd_platform,
        game_object.ball, n);
    DrawField(game_object, score);
    printw("\nGame starts in %i...", 3 - prepare_time);
    refresh();
    prepare_count++;
    if (prepare_count == 10) {
      prepare_time++;
      prepare_count = 0;
    }
  }
}

int GameControl(GameObject& game_object, Score& score) {
  int i;
  while (true) {
    noecho();
    usleep(80000);
    cbreak();
    nodelay(stdscr, 1);
    int n = getch();
    nodelay(stdscr, 0);
    i = ScoreCount(game_object, score);
    refresh();
    if (i != 0) {
      return i;
    }
    game_object.platform_controllers.frst->Move(
        game_object.game_settings, game_object.platform.frst_platform,
        game_object.ball, n);
    game_object.platform_controllers.scnd->Move(
        game_object.game_settings, game_object.platform.scnd_platform,
        game_object.ball, n);
    game_object.ball.move(game_object.platform.frst_platform,
                          game_object.platform.scnd_platform,
                          game_object.game_settings.playing_field_settings);
    DrawField(game_object, score);
    if (n == 27) {
      return -1;
    }
  }
  return 0;
}

void Game(GameSettings& game_settings) {
  int i;
  Score score;
  score.frst_score = 0;
  score.scnd_score = 0;
  while ((i != 1) && (i != 2)) {
    GameObject game_object = GameObject(game_settings);
    PrepareGame(game_object, score);
    i = GameControl(game_object, score);
    if (i == -1)
      break;
    getch();
    usleep(100000);
  };
}

int ScoreCount(GameObject& game_object, Score& score) {
  if (game_object.ball.getY() == 1) {
    printw("\nThe player on the right won round.");
    score.scnd_score++;
    if ((score.scnd_score >= 11) &&
        (score.scnd_score > (score.frst_score + 1))) {
      printw("\nThe player on the right won game.");
      return 2;
    }
    return 3;
  } else if (game_object.ball.getY() == game_object.playing_field.getY() - 2) {
    printw("\nThe player on the left won round.");
    score.frst_score++;
    if ((score.frst_score >= 11) &&
        (score.frst_score > (score.scnd_score + 1))) {
      printw("\nThe player on the left won game.");
      return 1;
    }
    return 3;
  }
  return 0;
}