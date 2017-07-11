#ifndef H_NETWORK
#define H_NETWORK

#include "game_settings.h"
#include "game_object.h"
#include <mutex>
#include <deque>
#include <condition_variable>
#include <boost/asio.hpp>
#include <ncurses.h>
#include <exception>

class NetworkClass {
 public:
  std::mutex mutex_thread;
  virtual void Connect(GameSettings& game_settings,
                       std::condition_variable& connect_check, std::exception_ptr& thread_exception) = 0;
  virtual void Game(GameObject& game_object,
                    Score& score,
                    int& pressed_button, std::exception_ptr& thread_exception) = 0;
  void Send(boost::asio::ip::tcp::socket& sock, int info);
  int Read(boost::asio::ip::tcp::socket& sock);
  virtual ~NetworkClass();
};

class NetworkServerClass : public NetworkClass {
 public:
  boost::asio::ip::tcp::socket sock;
  boost::asio::ip::tcp::acceptor acceptor;
  NetworkServerClass();
  void Connect(GameSettings& game_settings,
               std::condition_variable& connect_check, std::exception_ptr& thread_exception);
  void Game(GameObject& game_object, Score& score, int& pressed_button, std::exception_ptr& thread_exception);
  virtual ~NetworkServerClass();
};

class NetworkClientClass : public NetworkClass {
 public:
  boost::asio::ip::tcp::socket sock;
  NetworkClientClass();
  void Connect(GameSettings& game_settings,
               std::condition_variable& connect_check, std::exception_ptr& thread_exception);
  void Game(GameObject& game_object, Score& score, int& pressed_button, std::exception_ptr& thread_exception);
  virtual ~NetworkClientClass();
};

class TaskQueue {
  std::deque<std::function<bool()>> task;
  std::mutex mutex_task;
  std::condition_variable cv;

 public:
  template <typename F>
  void AddTask(F&& function) {
    {
      std::unique_lock<std::mutex> lock_task(mutex_task);
      task.emplace_back(std::forward<F>(function));
    }
    cv.notify_one();
  }

  void pop(std::function<bool()>& x) {
    std::unique_lock<std::mutex> lock_task(mutex_task);
    cv.wait(lock_task, [&]() { return !task.empty(); });
    x = move(task.front());
    task.pop_front();
  }
};

void Network(TaskQueue& task_queue);

void Connect(GameSettings& game_settings);

void NetworkGame(GameObject& game_object, Score& score, int& pressed_button);

class NetworkClassFactory {
 public:
  static std::unique_ptr<NetworkClass> newNetworkClass(
      GameSettings game_settings) {
    if (game_settings.network.isNetwork) {
      if (game_settings.network.isServer == 1) {
        return std::unique_ptr<NetworkClass>(new NetworkServerClass());
      } else {
        return std::unique_ptr<NetworkClass>(new NetworkClientClass());
      }
    } else
      return nullptr;
  }
};
#endif