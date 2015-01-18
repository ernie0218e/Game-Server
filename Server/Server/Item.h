#pragma once
#include "object.h"
class Item :
	public Object
{
	int arrX;
	int arrY;
	int type;
	bool loaded;

public:
	enum ItemList{ BOOT = 1, RANGEPLUS = 2};
	void setArrX(int x);
	void setArrY(int y);
	void setLoaded();
	void setType(int t);
	int getType();
	int getArrX();
	int getArrY();
	int getLoaded();

	static int randItemType();
	Item();
	~Item();
};
