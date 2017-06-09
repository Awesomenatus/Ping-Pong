#ifndef H_UTILITY
#define H_UTILITY

#include <vector>

struct PlayingField {
  std::vector<char> vector;
  int yPlayingField;
};

int Position(int x, int y, int z);

void Draw_field(PlayingField& PlayingField, int xPlayingField);

bool Draw_win(int BallY, int yPlayingField);

void Fill_vector_platform(PlayingField& PlayingField,
                          int Coordinate,
                          int Length,
                          int Position);

void Fill_vector_border(PlayingField& PlayingField, int xPlayingField);

void Fill_vector_ball(PlayingField& PlayingField, int xBall, int yBall);

void Fill_vector_all_space(PlayingField& PlayingField, int xPlayingField);

void Fill_vector_space(PlayingField& PlayingField, int pos);

#endif