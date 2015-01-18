#include "Blast.h"
#include "stdafx.h"

Blast::Blast()
{
	disappearSecond = 600;
	growSecond = 0;
	growCount = 0;
	grown = false;
}


Blast::~Blast()
{
}

void Blast::setDirection(int direction)
{
	this->direction = direction;
	switch (direction)
	{
	case UP:
		break;
	case DOWN:
		break;
	case LEFT:
		break;
	case RIGHT:
		break;
	case STATIC:
		grown = true;
		break;
	}
}

void Blast::increaseGrowCount(int t)
{
	growCount += t;
}

bool Blast::getGrown()
{
	return grown;
}

int Blast::getGrowSecond()
{
	return growSecond;
}

int Blast::getGrowCount()
{
	return growCount;
}

int Blast::getDisappearSecond()
{
	return disappearSecond;
}

int Blast::getDirection()
{
	return direction;
}

void Blast::setArrX(int x)
{
	arrX = x;
}

void Blast::setArrY(int y)
{
	arrY = y;
}

int Blast::getArrX()
{
	return arrX;
}

int Blast::getArrY()
{
	return arrY;
}

void Blast::setGrown()
{
	grown = true;
}

int Blast::getId()
{
	return id;
}

void Blast::setId(int x)
{
	id = x;
}

int Blast::getBombRange()
{
	return bombRange;
}

void Blast::setBombRange(int range)
{
	bombRange = range;
}
