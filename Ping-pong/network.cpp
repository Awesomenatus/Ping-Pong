#include "network.h"
#include "game_settings.h"
#include "game_object.h"
#include <boost/asio.hpp>
#include <exception>

using namespace boost::asio;

io_service service;

NetworkClass::~NetworkClass() {}

void NetworkClass::Send(ip::tcp::socket& sock, int info) {
  char tmp[4];
  snprintf(tmp, 4, "%i", info);
  sock.write_some(buffer(tmp));
}

int NetworkClass::Read(ip::tcp::socket& sock) {
  char tmp[4];
  sock.read_some(buffer(tmp));
  return atoi(tmp);
}

NetworkServerClass::NetworkServerClass()
    : sock(service),
      acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001)) {}

void NetworkServerClass::Connect(GameSettings& game_settings,
                                 std::condition_variable& connect_check, std::exception_ptr& thread_exception) {
  acceptor.accept(sock);
  Send(sock, game_settings.playing_field_settings.x_playing_field);
  Send(sock, game_settings.playing_field_settings.y_playing_field);
  Send(sock, game_settings.platform_length);
  connect_check.notify_one();
}

void NetworkServerClass::Game(GameObject& game_object,
                              Score& score,
                              int& pressed_key_network, std::exception_ptr& thread_exception) {
  try {
  std::lock_guard<std::mutex> lock_t(mutex_thread);
    pressed_key_network = Read(sock);
    Send(sock, game_object.platform.frst_platform.getxCoordinate());
    Send(sock, game_object.platform.scnd_platform.getxCoordinate());
    Send(sock, game_object.ball.getX());
    Send(sock, game_object.ball.getY());
    Send(sock, score.frst_score);
    Send(sock, score.scnd_score);
  }
  catch (...) {
    thread_exception = std::current_exception();
    return;
  }
}

NetworkServerClass::~NetworkServerClass() {}

NetworkClientClass::NetworkClientClass() : sock(service) {}

void NetworkClientClass::Game(GameObject& game_object,
                              Score& score,
                              int& pressed_key_network, std::exception_ptr& thread_exception) {
  try {
    Send(sock, pressed_key_network);
    std::lock_guard<std::mutex> lock_t(mutex_thread);
    game_object.platform.frst_platform.setxCoordinate(Read(sock));
    game_object.platform.scnd_platform.setxCoordinate(Read(sock));
    game_object.ball.setX(Read(sock));
    game_object.ball.setY(Read(sock));
    score.frst_score = Read(sock);
    score.scnd_score = Read(sock);
  }
  catch (...) {
    thread_exception = std::current_exception();
    return;
  }
}

void NetworkClientClass::Connect(GameSettings& game_settings,
                                 std::condition_variable& connect_check, std::exception_ptr& thread_exception) {
  ip::tcp::endpoint ep;
  try {
  ep = ip::tcp::endpoint (ip::address::from_string(game_settings.network.IPServer),
                       8001);
  }
  catch (...) {
    connect_check.notify_one();
    thread_exception = std::current_exception();
    return;
  }
  try {
  sock.connect(ep);
  }
  catch (...) {
    connect_check.notify_one();
    thread_exception = std::current_exception();
    return;
  }
  game_settings.playing_field_settings.x_playing_field = Read(sock);
  game_settings.playing_field_settings.y_playing_field = Read(sock);
  game_settings.platform_length = Read(sock);
  connect_check.notify_one();
}

NetworkClientClass::~NetworkClientClass() {}

void Network(TaskQueue& task_queue) {
  while (1) {
    std::function<bool()> x;
    task_queue.pop(x);
    if (x() == 1) {
      break;
    }
  }
}
