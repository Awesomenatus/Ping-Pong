#include <gtest/gtest.h>
#include <vector>
#include "utility.h"

class fillvectorFixture : public ::testing::Test {
 public:
  PlayingField Playingfield;
  int x, y;
  void SetUp() {
    x = 10;
    y = 10;
    Playingfield.vector = std::vector<char>(x * y);
    Playingfield.yPlayingField = 10;
  }

  void TearDown() {}
};

TEST_F(fillvectorFixture, all_spacetest) {
  Fill_vector_all_space(Playingfield, x);
  for (int count = 0; count < (x * y - 1); count++)
    ASSERT_EQ(' ', Playingfield.vector[count]);
}

TEST_F(fillvectorFixture, balltest) {
  Fill_vector_ball(Playingfield, 5, 5);
  ASSERT_EQ('o', Playingfield.vector[55]);
}

TEST_F(fillvectorFixture, bordertest) {
  Fill_vector_border(Playingfield, x);
  for (int count = 0; count < x; count++) {
    ASSERT_EQ('X', Playingfield.vector[0 + count * y]);
    ASSERT_EQ('X', Playingfield.vector[y - 1 + count * y]);
  }
  for (int count = 0; count < y; count++) {
    ASSERT_EQ('X', Playingfield.vector[0 + count]);
    ASSERT_EQ('X', Playingfield.vector[0 + (x - 1) * y + count]);
  }
}

TEST_F(fillvectorFixture, Platformtest) {
  Fill_vector_platform(Playingfield, 3, 3, 2);
  for (int count = 3; count != 6; count++) {
    ASSERT_EQ('|', Playingfield.vector[count * y + 2]);
  }
}

TEST_F(fillvectorFixture, Spacetest) {
  Fill_vector_space(Playingfield, 65);
  ASSERT_EQ(' ', Playingfield.vector[65]);
}