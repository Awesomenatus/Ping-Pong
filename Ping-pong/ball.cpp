#include "Ball.h"
#include <stdlib.h>  
#include <time.h> 

Ball::Ball(int x, int y)
{
	srand(time(0));
	xCoordinate = x/2;
	yCoordinate = y/2;
	(rand() % 10 + 1 < 5) ? XMove = -1 : XMove = 1;
	(rand() % 10 + 1 < 5) ? YMove = -1 : YMove = 1;
}

void Ball::xChange()
{
	XMove = -XMove;
}

void Ball::yChange()
{
	YMove = -YMove;
}

void Ball::move(char **Field)
{
	int xPotential = xCoordinate + XMove;
	int yPotential = yCoordinate + YMove;
	if (
		(Field[xPotential][yPotential] == '|') &&
		((Field[xPotential + 1][yPotential] == ' ') || (Field[xPotential - 1][yPotential] == ' '))
		)
	{
		xChange();
		yChange();
		xPotential = xCoordinate + XMove;
		yPotential = yCoordinate + YMove;
	}

	if (Field[xPotential][yPotential] == 'X')
	{
		yChange();
		yPotential = yCoordinate + YMove;
	}

	if (Field[xPotential][yPotential] == '|')
	{
		xChange();
		xPotential = xCoordinate + XMove;
	}


	xCoordinate += XMove;
	yCoordinate += YMove;

}






