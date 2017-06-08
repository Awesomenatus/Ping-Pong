#include <vector>
#include "fill_vector.h"
void Fill_vector::Fill_vector_platform(std::vector<char>& PlayingField,
                          int Coordinate,
                          int Length,
                          int yPlayingField,
                          int Position) {
  for (int i = Coordinate; i != (Coordinate + Length); i++) {
    PlayingField[Position + i * yPlayingField] = '|';
  }
}

void Fill_vector::Fill_vector_border(std::vector<char>& PlayingField,
                        int xPlayingField,
                        int yPlayingField) {
  for (int count = 0; count < xPlayingField; count++) {
    PlayingField[0 + count * yPlayingField] = 'X';
    PlayingField[yPlayingField - 1 + count * yPlayingField] = 'X';
  }
  for (int count = 0; count < yPlayingField; count++) {
    PlayingField[0 + count] = 'X';
    PlayingField[0 + (xPlayingField - 1) * yPlayingField + count] = 'X';
  }
}

void Fill_vector::Fill_vector_ball(std::vector<char>& PlayingField,
                      int xBall,
                      int yBall,
                      int yPlayingField) {
  PlayingField[xBall * yPlayingField + yBall] = 'o';
}

void Fill_vector::Fill_vector_all_space(std::vector<char>& PlayingField,
                       int xPlayingField,
                       int yPlayingField) {
  for (int x = 0; x < xPlayingField * yPlayingField - 1; x++) {
    PlayingField.push_back(' ');
  };
}

void Fill_vector::Fill_vector_space(std::vector<char>& PlayingField, int pos) {
  PlayingField[pos] = ' ';
}