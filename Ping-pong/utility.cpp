#include <vector>
#include <ncurses.h>
#include "utility.h"
#include <string>
#include "game_object.h"
#include <unistd.h>
#include <thread>
#include "network.h"
#include <mutex>
#include <exception>

using namespace std;

void PlatformControll(GameObject& game_object, int pressed_key, int pressed_key_network) {
  game_object.platform_controllers.frst->Move(
      game_object.game_settings, game_object.platform.frst_platform,
      game_object.ball, pressed_key_network);
  game_object.platform_controllers.scnd->Move(
      game_object.game_settings, game_object.platform.scnd_platform,
      game_object.ball, pressed_key);
}

int WhoWin(Score& score) {
  const int point_limit = 11;
  if ((score.scnd_score >= point_limit) &&
      (score.scnd_score > (score.frst_score + 1))) {
    return 2;
  } else if ((score.frst_score >= point_limit) &&
             (score.frst_score > (score.scnd_score + 1))) {
    return 1;
  }
  return 0;
}

int ScoreCount(GameObject& game_object, Score& score) {
  if (game_object.ball.getY() == 1) {
    if (!game_object.game_settings.network.isNetwork ||
        game_object.game_settings.network.isServer) {
      score.scnd_score++;
    }
    if (WhoWin(score) == 2) {
      printw("\nThe player on the right won game.");
      return 2;
    }
    return 3;
  } else if (game_object.ball.getY() == game_object.playing_field.getY() - 2) {
    if (!game_object.game_settings.network.isNetwork ||
        game_object.game_settings.network.isServer) {
      score.frst_score++;
    }
    if (WhoWin(score) == 1) {
      printw("\nThe player on the left won game.");
      return 1;
    }
    return 3;
  }
  return 0;
}

void DrawPlatform(Platform& platform, PlayingField& playing_field, int player) {
  for (int count = platform.getxCoordinate();
       count != (platform.getxCoordinate() + platform.getlength()); count++) {
    playing_field.setChar(playing_field.Position(count, player), '|');
  }
}

void DrawBorder(PlayingField& playing_field) {
  for (int count = 0; count < playing_field.getX(); count++) {
    playing_field.setChar(playing_field.Position(count, 0), 'X');
    playing_field.setChar(
        playing_field.Position(count, playing_field.getY() - 1), 'X');
  };
  for (int count = 0; count < playing_field.getY(); count++) {
    playing_field.setChar(playing_field.Position(0, count), 'X');
    playing_field.setChar(
        playing_field.Position(playing_field.getX() - 1, count), 'X');
  };
}

void DrawBall(GameObject& game_object) {
  game_object.playing_field.setChar(
      game_object.playing_field.Position(game_object.ball.getX(),
                                         game_object.ball.getY()),
      'o');
}

int ReadUserInput() {
  nodelay(stdscr, 1);
  int n = getch();
  nodelay(stdscr, 0);
  return n;
}

void DrawField(GameObject& game_object, Score& score) {
  wclear(stdscr);
  curs_set(0);
  for (int count = 0; count < (game_object.playing_field.getX() *
                               game_object.playing_field.getY());
       count++) {
    game_object.playing_field.setChar(count, ' ');
  };

  DrawBorder(game_object.playing_field);

  DrawBall(game_object);

  int PlayerPosition = 2;
  DrawPlatform(game_object.platform.frst_platform, game_object.playing_field,
               PlayerPosition);
  PlayerPosition = game_object.playing_field.getY() - 3;
  DrawPlatform(game_object.platform.scnd_platform, game_object.playing_field,
               PlayerPosition);

  for (int x = 0; x < (game_object.playing_field.getX() *
                       game_object.playing_field.getY());
       x++) {
    if (((x % (game_object.playing_field.getY())) == 0) && (x != 0)) {
      addch('\n');
    }
    addch(game_object.playing_field.getChar(x));
  };
  printw("\n%i : %i", score.frst_score, score.scnd_score);
  refresh();
}

void PrepareGame(GameObject& game_object,
                 Score& score,
                 TaskQueue& task_queue,
                 int& pressed_key_network,
                 std::unique_ptr<NetworkClass>& network_class,
                 std::exception_ptr& thread_exception) {
  int prepare_count = 0, prepare_time = 0, pressed_key = 0;
  const int frame_prepare_duration = 100000;
  DrawField(game_object, score);
  while (prepare_time < 3) {
    usleep(frame_prepare_duration);
    if ((!game_object.game_settings.network.isServer) &&
        (game_object.game_settings.network.isNetwork)) {
      pressed_key_network = ReadUserInput();
      task_queue.AddTask([&]() {
        network_class->Game(game_object, score, pressed_key_network,
                            thread_exception);
        return 0;
      });
      {
        std::lock_guard<std::mutex> lock(network_class->mutex_thread);
        DrawField(game_object, score);
      }
    } else {
      pressed_key = ReadUserInput();
      if (!game_object.game_settings.network.isNetwork) {
        pressed_key_network = pressed_key;
      }
      if (game_object.game_settings.network.isNetwork) {
        task_queue.AddTask([&]() {
          network_class->Game(game_object, score, pressed_key_network,
                              thread_exception);
          return 0;
        });
      }
      {
        std::lock_guard<std::mutex> lock(network_class->mutex_thread);
        PlatformControll(game_object, pressed_key, pressed_key_network);
      }
      DrawField(game_object, score);
    }
    printw("\nRound starts in %i...", 3 - prepare_time);
    refresh();
    prepare_count++;
    if (prepare_count == 10) {
      prepare_time++;
      prepare_count = 0;
    }
  }
}

int GameControl(GameObject& game_object,
                Score& score,
                TaskQueue& task_queue,
                int& pressed_key_network,
                std::unique_ptr<NetworkClass>& network_class,
                std::exception_ptr& thread_exception) {
  while (true) {
    const int frame_duration = 70000;
    const int esc_key = 27;
    if ((!game_object.game_settings.network.isServer) &&
        (game_object.game_settings.network.isNetwork)) {
      usleep(frame_duration);
      pressed_key_network = ReadUserInput();
      if (pressed_key_network == esc_key) {
        return 0;
      }
      task_queue.AddTask([&]() {
        network_class->Game(game_object, score, pressed_key_network,
                            thread_exception);
        return 0;
      });
      {
        std::lock_guard<std::mutex> lock(network_class->mutex_thread);
        const int who_finished_round = ScoreCount(game_object, score);
        const int no_one = 0;
        refresh();
        if (who_finished_round != no_one) {
          return who_finished_round;
        }
        DrawField(game_object, score);
      }
      if (thread_exception)
        return 1;
    } else {
      usleep(frame_duration);
      int pressed_key = ReadUserInput();
      if (pressed_key == esc_key) {
        return 0;
      }
      if (game_object.game_settings.network.isNetwork)
        task_queue.AddTask([&]() {
          network_class->Game(game_object, score, pressed_key_network,
                              thread_exception);
          return 0;
        });

      if (!game_object.game_settings.network.isNetwork) {
        pressed_key_network = pressed_key;
      }
      {
        std::lock_guard<std::mutex> lock(network_class->mutex_thread);
        const int who_finished_round = ScoreCount(game_object, score);
        const int no_one = 0;
        refresh();
        if (who_finished_round != no_one) {
          return who_finished_round;
        }
        PlatformControll(game_object, pressed_key, pressed_key_network);
        game_object.ball.move(game_object.platform.frst_platform,
                              game_object.platform.scnd_platform,
                              game_object.game_settings.playing_field_settings);
      }
      DrawField(game_object, score);
      if (thread_exception)
        return 1;
    }
  }
}

void Game(GameSettings& game_settings) {
  int round_result = 0;
  TaskQueue task_queue;
  thread network(Network, ref(task_queue));
  std::unique_ptr<NetworkClass> network_class =
      NetworkClassFactory::newNetworkClass(game_settings);
  std::exception_ptr thread_exception = nullptr;
  if (game_settings.network.isNetwork) {
    std::condition_variable connect_check;
    task_queue.AddTask([&]() {
      network_class->Connect(game_settings, connect_check, thread_exception);
      return 0;
    });
    if (game_settings.network.isServer) {
      printw("wait client connect");
      refresh();
    }
    mutex mutex_main_thread;
    std::unique_lock<std::mutex> lock(mutex_main_thread);
    connect_check.wait(lock);
  }
  Score score;
  score.frst_score = 0;
  score.scnd_score = 0;
  int pressed_key_network = 0;
  if (thread_exception) {
    try {
      std::rethrow_exception(thread_exception);
    } catch (const std::exception& ex) {
      printw("Wrong IP adress");
      refresh();
    }
  } else {
    while ((round_result != 1) && (round_result != 2)) {
      GameObject game_object(game_settings);
      PrepareGame(game_object, score, task_queue, pressed_key_network,
                  network_class, thread_exception);
      round_result =
          GameControl(game_object, score, task_queue, pressed_key_network,
                      network_class, thread_exception);
      if (thread_exception) {
        try {
          std::rethrow_exception(thread_exception);
        } catch (...) {
          if (game_object.game_settings.network.isServer) {
            printw("Client disconnect from the game");
          } else {
            printw("Server disconnect from the game");
          }
          refresh();
          break;
        }
      } else {
        if (round_result == 0)
          break;
      }
    };
  }
  task_queue.AddTask([]() { return 1; });
  network.join();
  sleep(2);
}