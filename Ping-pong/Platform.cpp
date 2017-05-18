#include "Platform.h"

void Platform::setLenght(int x)
{
	this->lenght = x;
}
void Platform::setyCoordinate(int x)
{
	this->yCoordinate = x;
}
PlatformPlayer::PlatformPlayer(int x, int y)
{
	setLenght(x);
	setyCoordinate(y);
}
void PlatformPlayer::MoveUp()
{
	if (yCoordinate > 0)
	this->yCoordinate--;
}
void PlatformPlayer::MoveDown(int xPlayingField)
{
	if (yCoordinate < xPlayingField-2)
	this->yCoordinate++;
}