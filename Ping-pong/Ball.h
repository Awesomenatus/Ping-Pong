#ifndef H_BALL
#define H_BALL

class Ball
{
protected:
	int xCoordinate;
	int yCoordinate;
	int XMove;
	int YMove;
public:
	Ball(int x, int y);
	void xChange();
	void yChange();
	void move(char **Field);
	int getX() const { return xCoordinate; };
	int getY() const { return yCoordinate; };
};

#endif
