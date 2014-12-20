#include "Object.h"
#include <windows.h>
#include <math.h>
#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN

Object::Object(double x, double y)
{
	winX = x;
	winY = y;
}

Object::Object()
{
	
}


Object::~Object()
{
}


void Object::setWinX(double x)
{
	winX = x;
}

void Object::setWinY(double y)
{
	winY = y;
}

void Object::setX(double x)
{
	winX = x;
}

void Object::setY(double y)
{
	winY = y;
}

double Object::getWinX()
{
	return winX;
}

double Object::getWinY()
{
	return winY;
}

double Object::getX()
{
	return x;
}

double Object::getY()
{
	return y;
}