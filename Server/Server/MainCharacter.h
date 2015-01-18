#pragma once
#include "Object.h"
#include <vector>
#include "stdafx.h"
#include <string>
#include "Command.h"
using namespace std;
class MainCharacter	: public Object
{
	
	double hp;
	double step;
	double moveSpeed;

	string charName;
	int lastTime;
	int id;
	int status;
	int facing;
	int graphCode;
	int damageImmuneSecond;
	int damageImmuneCount;
	int bombDropCount;
	int bombDropMax;
	int bombRange;
public:
	enum{ UP, DOWN, LEFT, RIGHT };
	MainCharacter(double, double, int , int, string);
	~MainCharacter();

	Command *cmd;

	double getMoveSpeed();
	int getBombDropCount();
	int getBombDropMax();
	int getHp();
	int getId();
	int getStatus();
	int getFacing();
	int getGraphCode();
	string getCharName();
	void IncreaseDamageCount();
	void setStatus(int);
	void setFacing(int f);
	void setGrpahCode(int);
	void setMoveSpeed(double m);
	void decreaseBombDropCount();
	void increaseBombDropCount();
	void increaseBombDropMax();
	void decreaseBombDropMax();
	void increaseBombRange();
	void decreaseBombRange();
	const int getBombRange();
	bool Hit();
	void MoveWithDisplacement(double dx, double dy);
};


