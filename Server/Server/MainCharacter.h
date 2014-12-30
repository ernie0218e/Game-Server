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

	int id;
	int status;
	int facing;
	int graphCode;
	int damageImmuneSecond;
	int damageImmuneCount;
public:
	enum{ UP, DOWN, LEFT, RIGHT };
	MainCharacter(double, double, int , int);
	~MainCharacter();

	double getMoveSpeed();
	int getHp();
	int getId();
	int getStatus();
	int getFacing();
	int getGraphCode();
	void IncreaseDamageCount();
	void setStatus(int);
	void setFacing(int f);
	void setGrpahCode(int);
	void setMoveSpeed(double m);
	void Hit();
	void MoveWithDisplacement(double dx, double dy);
};


