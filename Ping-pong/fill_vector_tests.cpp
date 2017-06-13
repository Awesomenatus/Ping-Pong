#include <gtest/gtest.h>
#include <vector>
#include "utility.h"

class fillvectorFixture : public ::testing::Test {
 public:
  PlayingField* playing_field;
  int x, y;
  void SetUp() {
    x = 10;
    y = 10;
    playing_field = new PlayingField(x, y);
  }

  void TearDown() {}
};

TEST_F(fillvectorFixture, all_spacetest) {
  Fill_vector_all_space(*playing_field);
  for (int count = 0; count < (x * y); count++)
    ASSERT_EQ(' ', playing_field->getChar(count));
}

TEST_F(fillvectorFixture, balltest) {
  Fill_vector_ball(*playing_field, 5, 5);
  ASSERT_EQ('o', playing_field->getChar(55));
}

TEST_F(fillvectorFixture, bordertest) {
  Fill_vector_border(*playing_field);
  for (int count = 0; count < x; count++) {
    ASSERT_EQ('X', playing_field->getChar(0 + count * y));
    ASSERT_EQ('X', playing_field->getChar(y - 1 + count * y));
  }
  for (int count = 0; count < y; count++) {
    ASSERT_EQ('X', playing_field->getChar(0 + count));
    ASSERT_EQ('X', playing_field->getChar(0 + (x - 1) * y + count));
  }
}

TEST_F(fillvectorFixture, Platformtest) {
  Fill_vector_platform(*playing_field, 3, 3, 2);
  for (int count = 3; count != 6; count++) {
    ASSERT_EQ('|', playing_field->getChar(count * y + 2));
  }
}

TEST_F(fillvectorFixture, Spacetest) {
  Fill_vector_space(*playing_field, 6, 5);
  ASSERT_EQ(' ', playing_field->getChar(65));
}