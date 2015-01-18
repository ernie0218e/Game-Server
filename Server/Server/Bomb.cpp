#include "Bomb.h"
#include "stdafx.h"

Bomb::Bomb()
{
	exploded = false;
	explodeSecond = 2000;
	explodeCount = 0;
	blastSecond = 100;
	blastCount = 0;
}


Bomb::~Bomb()
{
}

void Bomb::increaseExplodeCount(int t)
{
	this->explodeCount += t;
}

int Bomb::getExplodeCount()
{
	return explodeCount;
}

int Bomb::getExplodeSecond()
{
	return explodeSecond;
}

void Bomb::setArrY(int y)
{
	arrY = y;
}

void Bomb::setArrX(int x)
{
	arrX = x;
}

int Bomb::getArrY()
{
	return arrY;
}

int Bomb::getArrX()
{
	return arrX;
}

void Bomb::increaseBlastCount(int t)
{
	blastCount += t;
}

int Bomb::getBlastCount()
{
	return blastCount;
}

int Bomb::getBlastSecond()
{
	return blastSecond;
}

void Bomb::setExploded()
{
	exploded = true;
}

bool Bomb::getExploded()
{
	return exploded;
}

int Bomb::getBombRange()
{
	return bombRange;
}

void Bomb::setBombRange(int range)
{
	bombRange = range;
}

void Bomb::setID(int id)
{
	this->id = id;
}

int Bomb::getID()
{
	return id;
}
