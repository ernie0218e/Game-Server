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

	int command_flag;
	int newChar_id;
	int delChar_id;

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
	int getCmdFlag();
	int getNewCharID();
	int getDelCharID();
	void setCmdFlag(int);
	void setCmdFlag(int, int);
	void clearNewCharID();
	void clearDelCharID();
	void clearCmdFlag();
	void IncreaseDamageCount();
	void setStatus(int);
	void setFacing(int f);
	void setGrpahCode(int);
	void setMoveSpeed(double m);
	void Hit();
	void MoveWithDisplacement(double dx, double dy);
};


