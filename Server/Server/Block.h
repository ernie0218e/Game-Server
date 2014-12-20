#pragma once
#include "Object.h"
#include "stdafx.h"
class Block :
	public Object
{
	char blockID;
	int aCoordX;
	int aCoordY;
	bool destructible;
public:
	Block();
	Block(double x, double y, char id, int ax, int ay);
	int getCoordX();
	int getCoordY();
	bool getDestructible();
	~Block();

	char getBlockID();
};

