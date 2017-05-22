#include "Ball.h"
#include <stdlib.h>  
#include <time.h> 

Ball::Ball(int x, int y)
{
	srand(time(0));
	xCoordinate = x/2;
	yCoordinate = y/2;
	(rand() % 10 + 1 < 5) ? XMove = -1 : XMove = 1; // случайное изначальное направление движения
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
		((Field[xPotential -XMove][yPotential] == ' '))
		)
	{
		xChange();
		yChange();
		xPotential = xCoordinate + XMove;
		yPotential = yCoordinate + YMove;
	}

	if (Field[xPotential][yPotential] == 'X')
	{
		xChange();
		xPotential = xCoordinate + XMove;
	}

	if (Field[xPotential][yPotential] == '|')
	{
		yChange();
		yPotential = yCoordinate + YMove;
	}


	xCoordinate += XMove;
	yCoordinate += YMove;

}






