#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	loaded = false;
}


Item::~Item()
{
}

void Item::setArrX(int x)
{
	arrX = x;
}

void Item::setArrY(int y)
{
	arrY = y;
}

int Item::getArrX()
{
	return arrX;
}

int Item::getArrY()
{
	return arrY;
}

int Item::randItemType()
{
	return rand() % 2 + 1;
}

void Item::setLoaded()
{
	loaded = true;
}

int Item::getLoaded()
{
	return loaded;
}

void Item::setType(int t)
{
	type = t;
}

int Item::getType()
{
	return type;
}
