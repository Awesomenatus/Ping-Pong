#include <iostream>
#include "Platform.h"
#include "Ball.h"

using namespace std;
int main()
{
	int xPlayingField=0, yPlayingField=0, PlatformLenght;
	cin >> xPlayingField;
	cin >> yPlayingField;
	cin >> PlatformLenght;
	char **PlayingField = new char*[xPlayingField];
	for (int count = 0; count < xPlayingField; count++)
		PlayingField[count] = new char[yPlayingField];
	PlatformPlayer frst(PlatformLenght, 2);
	PlatformPlayer scnd(PlatformLenght, 
						yPlayingField - 3);
						
	Ball ball(xPlayingField, yPlayingField);
	for (int x = 0; x < xPlayingField; x++)
	{
		for (int y = 0; y < yPlayingField; y++)
		{
			PlayingField[x][y] = ' ';
		};
	};
	for (int count = 0; count < xPlayingField; count++)
	{
		PlayingField[count][0] = 'X';
		PlayingField[count][yPlayingField - 1] = 'X';
	};
	for (int count = 0; count < yPlayingField; count++)
	{
		PlayingField[0][count] = 'X';
		PlayingField[xPlayingField-1][count] = 'X';
	};
	for (int i = ((xPlayingField - PlatformLenght)/2); i != (((xPlayingField - PlatformLenght) / 2)+PlatformLenght); i++)
	{
		int y1 = frst.getyCoordinate();
		int y2 = scnd.getyCoordinate();
		PlayingField[i][y1] = '|';
		PlayingField[i][y2] = '|';
	};
	PlayingField[ball.getX()][ball.getY()] = 'o';
	for (int x = 0; x < xPlayingField; x++)
	{
		for (int y = 0; y < yPlayingField; y++)
			{
				cout << PlayingField[x][y];
			};
		cout << endl;
	};
	system("pause");
	while (true)
	{

	}
	return 0;
}