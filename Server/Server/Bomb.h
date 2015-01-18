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
	int id;
	bool exploded;
	int bombRange;
public:
	void setID(int id);
	void setArrY(int y);
	void setArrX(int x);
	void setExploded();
	bool getExploded();
	int getID();
	int getArrY();
	int getArrX();
	int getBombRange();
	void setBombRange(int range);
	void increaseExplodeCount(int t);
	void increaseBlastCount(int t);
	int getExplodeCount();
	int getExplodeSecond();
	int getBlastCount();
	int getBlastSecond();
	Bomb();
	~Bomb();
};

