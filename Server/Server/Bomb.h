#pragma once
#include "Object.h"
#include "stdafx.h"
class Bomb :
	public Object
{
	int explodeSecond;
	int explodeCount;
	int blastSecond;
	int blastCount;
	int arrX;
	int arrY;
	bool exploded;
public:

	void setArrY(int y);
	void setArrX(int x);
	void setExploded();
	bool getExploded();
	int getArrY();
	int getArrX();
	void increaseExplodeCount(int t);
	void increaseBlastCount(int t);
	int getExplodeCount();
	int getExplodeSecond();
	int getBlastCount();
	int getBlastSecond();
	Bomb();
	~Bomb();
};

