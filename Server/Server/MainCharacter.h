#pragma once
#include "Object.h"
#include <vector>
#include "stdafx.h"
#include <string>
using namespace std;
class MainCharacter	: public Object
{
	
	double hp;
	double step;
	double moveSpeed;

	int command_flag;
	int newChar_id;
	int delChar_id;
	int bomb_x;
	int bomb_y;
	int hit_id;

	string charName;
	int lastTime;
	int id;
	int status;
	int facing;
	int graphCode;
	int damageImmuneSecond;
	int damageImmuneCount;
public:
	enum{ UP, DOWN, LEFT, RIGHT };
	MainCharacter(double, double, int , int, string);
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
	int getBombX();
	int getBombY();
	int getHitID();
	string getCharName();
	void setCmdFlag(int);
	void setCmdFlag(int, int);
	void setBomb(int, int);
	void setHitID(int);
	void clearNewCharID();
	void clearDelCharID();
	void clearCmdFlag();
	void clearBomb();
	void IncreaseDamageCount();
	void setStatus(int);
	void setFacing(int f);
	void setGrpahCode(int);
	void setMoveSpeed(double m);
	bool Hit();
	void MoveWithDisplacement(double dx, double dy);
};


