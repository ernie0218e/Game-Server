#pragma once
#include <windows.h>
#include "stdafx.h"
class Object
{
protected:
	double x;
	double y;
	double winX;
	double winY;
public:
	Object();
	Object(double, double);
	~Object();
	void setWinX(double x);
	void setWinY(double y);
	void setX(double x);
	void setY(double y);

	double getWinX();
	double getWinY();
	double getX();
	double getY();
};


