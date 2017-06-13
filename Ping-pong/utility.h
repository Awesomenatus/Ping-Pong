#ifndef H_UTILITY
#define H_UTILITY

#include <vector>

class PlayingField {
 protected:
  std::vector<char> Vector;
  int y_playing_field;
  int x_playing_field;

 public:
  PlayingField(int x, int y);
  int Position(int x, int y);
  void setChar(int pos, char c);
  char getChar(int pos);
  int getX() const { return x_playing_field; };
  int getY() const { return y_playing_field; };
};

struct PlayingFieldasd {
  std::vector<char> vector;
  int y_playing_field;
};

void Draw_field(PlayingField& PlayingField);

bool Draw_win(int BallY, int yPlayingField);

void Fill_vector_platform(PlayingField& PlayingField,
                          int Coordinate,
                          int Length,
                          int Position);

void Fill_vector_border(PlayingField& PlayingField);

void Fill_vector_ball(PlayingField& PlayingField, int xBall, int yBall);

void Fill_vector_all_space(PlayingField& PlayingField);

void Fill_vector_space(PlayingField& PlayingField, int x, int y);

#endif