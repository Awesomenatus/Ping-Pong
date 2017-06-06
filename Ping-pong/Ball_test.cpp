#include <gtest/gtest.h>

#include "../Ball.cpp"

TEST(BallTest, ConstructorTest)
{
	Ball ball(5,4);
	ASSERT_EQ(5, ball.getX());
	ASSERT_EQ(4, ball.getY());
}

