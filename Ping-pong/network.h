#ifndef H_NETWORK
#define H_NETWORK

#include "game_settings.h"
#include "game_object.h"
#include <mutex>
#include <vector>
#include <condition_variable>
#include <boost/asio.hpp>
#include <ncurses.h>
class NetworkClass {
public:
  std::mutex mutex_thread;
  virtual void Connect (GameSettings& game_settings, std::condition_variable& connect_check) = 0;
  virtual void Game (GameObject& game_object, Score& score, int& pressed_button) = 0;
  virtual void Send(int info) = 0;
  virtual ~NetworkClass();
};

class NetworkServerClass : public NetworkClass{ 
public:
  boost::asio::ip::tcp::socket sock;
  boost::asio::ip::tcp::acceptor acceptor;
  NetworkServerClass();
  void Connect (GameSettings& game_settings, std::condition_variable& connect_check);
  void Game (GameObject& game_object, Score& score, int& pressed_button);
  void Send(int info);
  virtual ~NetworkServerClass();
};

class NetworkClientClass : public NetworkClass {
public:
  boost::asio::ip::tcp::socket sock;
  NetworkClientClass();
  void Connect (GameSettings& game_settings, std::condition_variable& connect_check);
  void Game (GameObject& game_object, Score& score, int& pressed_button);
  void Send(int info);
  virtual ~NetworkClientClass();
};


struct TaskQueue {
  std::vector <std::function <bool ()>> task;
  std::mutex mutex_t;
  std::condition_variable cv;
  template <typename F>
  void AddTask(F&& function) {
    //printw("ADDTASK");
    //refresh();
    
    std::unique_lock<std::mutex> lock_t(mutex_t);
    task.emplace_back(std::forward<F>(function));
    
    cv.notify_one();
  }
};

void Network (TaskQueue& task_queue);

void Connect(GameSettings& game_settings);

void NetworkGame(GameObject& game_object, Score& score, int& pressed_button);

class NetworkClassFactory {
 public:
  static std::unique_ptr<NetworkClass>
  newNetworkClass(GameSettings game_settings) {
    if (game_settings.network.isNetwork) {
       if (game_settings.network.isServer == 1) {
         return std::unique_ptr<NetworkClass>(new NetworkServerClass());
       }else {
         return std::unique_ptr<NetworkClass>(new NetworkClientClass());
       }
    } else return nullptr;
  }
};
#endif