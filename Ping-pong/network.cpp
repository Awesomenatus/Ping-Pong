#include "network.h"
#include "game_settings.h"
#include "game_object.h"
#include <boost/asio.hpp> 
#include <ncurses.h>

using namespace boost::asio;

io_service service;

NetworkClass::~NetworkClass(){}

NetworkServerClass::NetworkServerClass() : sock(service),acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001)) {
}

void NetworkServerClass::Connect (GameSettings& game_settings, std::condition_variable& connect_check) {
  printw("wait client connect");
  refresh();
  acceptor.accept(sock);
  Send(game_settings.playing_field_settings.x_playing_field);
  Send(game_settings.playing_field_settings.y_playing_field);
  Send(game_settings.platform_length);
  connect_check.notify_one();
}

void NetworkServerClass::Game (GameObject& game_object, Score& score, int& pressed_button) {
  //acceptor.accept(sock);
  std::lock_guard<std::mutex> lock_t(mutex_thread);
  char button[3];
  sock.read_some(buffer(button));
  pressed_button = atoi(button);
  Send(game_object.platform.frst_platform.getxCoordinate());
  Send(game_object.platform.scnd_platform.getxCoordinate());
  Send(game_object.ball.getX());
  Send(game_object.ball.getX());
  Send(score.frst_score);
  Send(score.scnd_score);
}

void NetworkServerClass::Send (int info) {
  char tmp[3];
  sprintf(tmp, "%i", info);
  sock.write_some(buffer(tmp));
}

NetworkServerClass::~NetworkServerClass(){}

NetworkClientClass::NetworkClientClass() : sock(service) {
  
}
void NetworkClientClass::Game (GameObject& game_object, Score& score, int& pressed_button) {
  std::lock_guard<std::mutex> lock_t(mutex_thread);
  Send(pressed_button);
  char tmp[3];
  sock.read_some(buffer(tmp));
  game_object.platform.frst_platform.setxCoordinate(atoi(tmp));
  sock.read_some(buffer(tmp));
  game_object.platform.scnd_platform.setxCoordinate(atoi(tmp));
  sock.read_some(buffer(tmp));
  game_object.ball.setX(atoi(tmp));
  sock.read_some(buffer(tmp));
  game_object.ball.setY(atoi(tmp));
  sock.read_some(buffer(tmp));
  score.frst_score = atoi(tmp);
  sock.read_some(buffer(tmp));
  score.frst_score = atoi(tmp);
}

void NetworkClientClass::Connect (GameSettings& game_settings, std::condition_variable& connect_check) {
  ip::tcp::endpoint ep( ip::address::from_string(game_settings.network.IPServer), 8001);
	sock.connect(ep);
  //std::lock_guard<std::mutex> lock_t(mutex_thread);
  char tmp[3];
  sock.read_some(buffer(tmp));
  game_settings.playing_field_settings.x_playing_field = atoi(tmp);
  sock.read_some(buffer(tmp));
  game_settings.playing_field_settings.y_playing_field = atoi(tmp);
  sock.read_some(buffer(tmp));
  game_settings.platform_length = atoi(tmp);
  connect_check.notify_one();
}

void NetworkClientClass::Send (int info) {
  char tmp[3];
  sprintf(tmp, "%i", info);
  sock.write_some(buffer(tmp));
}

NetworkClientClass::~NetworkClientClass(){}

void Network (TaskQueue& task_queue) {
  while (1) {
    std::unique_lock<std::mutex> lock_t(task_queue.mutex_t);
    task_queue.cv.wait(lock_t);
    if (task_queue.task[0]() == 1) {
      task_queue.task.clear();
      break;
    }
    task_queue.task.erase(task_queue.task.begin());
  }
}
