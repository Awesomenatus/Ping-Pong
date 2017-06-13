#include <gtest/gtest.h>
#include <vector>
#include "utility.h"

class playingfieldFixture : public ::testing::Test {
 public:
  int x, y;
  PlayingField* playing_field;
  void SetUp() {
    x = 10;
    y = 9;
    playing_field = new PlayingField(x, y);
  }
  void TearDown() { delete playing_field; }
};

TEST_F(playingfieldFixture, getYtest) {
  ASSERT_EQ(9, playing_field->getY());
}

TEST_F(playingfieldFixture, getXtest) {
  ASSERT_EQ(10, playing_field->getX());
}

TEST_F(playingfieldFixture, constructortest) {
  PlayingField playing_field(10, 9);
  ASSERT_EQ(10, playing_field.getX());
  ASSERT_EQ(9, playing_field.getY());
  playing_field.setChar(89, 'c');
  ASSERT_EQ('c', playing_field.getChar(89));
}

TEST_F(playingfieldFixture, positiontest) {
  ASSERT_EQ(50, playing_field->Position(5, 5));
}

TEST_F(playingfieldFixture, inputoutputtest) {
  playing_field->setChar(50, 'c');
  ASSERT_EQ('c', playing_field->getChar(50));
  playing_field->setChar(50, 'y');
  ASSERT_EQ('y', playing_field->getChar(50));
}