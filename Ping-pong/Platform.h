#pragma once

#ifndef H_PLATFORM
#define H_PLATFORM

class Platform
{
public:
	int getLenght() const { return lenght; };
	void setLenght(int x);
	int getyCoordinate() const { return yCoordinate; };
	void setyCoordinate(int x);
protected:
	int lenght;
	int yCoordinate;
};

class PlatformPlayer : public Platform
{
public:
	PlatformPlayer(int Lenght, int yCoordinate);
	void MoveUp();
	void MoveDown(int xPlayingField);
};

#endif