#pragma once
#include "Object.h"
#include "stdafx.h"
class Blast :
	public Object
{
	int direction;
	int growSecond;
	int growCount;
	int arrX;
	int arrY;
	int disappearSecond;
	int id;
	bool grown;
public:
	enum{UP=0, DOWN=1, LEFT=2, RIGHT=3, STATIC=4};
	Blast();
	int getGrowSecond();
	int getGrowCount();
	int getDisappearSecond();
	int getDirection();
	int getArrX();
	int getArrY();
	int getId();
	void setId(int x);
	void setArrX(int x);
	void setArrY(int y);
	void setDirection(int direction);
	void setGrown();
	void increaseGrowCount(int t);
	bool getGrown();
	~Blast();
};

