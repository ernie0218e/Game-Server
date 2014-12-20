#include "Block.h"
#include "stdafx.h"
Block::Block()
{
	//	this->sprite = new Sprite(DirectX::SimpleMath::Vector2(x, y));
}


Block::Block(double x, double y, char id, int ax, int ay)
{
	this->x = x;
	this->y = y;
	this->blockID = id;
	this->aCoordX = ax;
	this->aCoordY = ay;
	if (id >= 100)
		destructible = false;
	else
		destructible = true;
}


Block::~Block()
{
	
}


char Block::getBlockID()
{
	return blockID;
}

int Block::getCoordX()
{
	return aCoordX;
}

int Block::getCoordY()
{
	return aCoordY;
}

bool Block::getDestructible()
{
	return destructible;
}

