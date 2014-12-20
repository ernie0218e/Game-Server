#pragma once
#include "Object.h"
#include <vector>
#include "stdafx.h"
using namespace std;
class MainCharacter	: public Object
{
	
	double hp;
	double step;
	double moveSpeed;

	int facing;
	int graphCode;
	int damageImmuneSecond;
	int damageImmuneCount;
public:
	enum{ UP, DOWN, LEFT, RIGHT };
	MainCharacter(double, double, int);
	~MainCharacter();

	double getMoveSpeed();
	int getHp();
	int getFacing();
	int getGraphCode();
	void IncreaseDamageCount();
	void setFacing(int f);
	void setGrpahCode(int);
	void setMoveSpeed(double m);
	void Hit();
	void MoveWithDisplacement(double dx, double dy);
};


