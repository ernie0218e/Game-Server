#include "MainCharacter.h"
#include <math.h>
#include "stdafx.h"
#include <string>
MainCharacter::MainCharacter(double x, double y, int graphCode, int id, string name)
{
	command_flag = 0;
	newChar_id = 0;
	delChar_id = 0;
	
	charName = name;
	lastTime = timeGetTime();
	this->id = id;
	this->graphCode = graphCode;
	damageImmuneCount = 0;
	damageImmuneSecond = 700;
	this->x = x;
	this->y = y;
	hp = 100;
	moveSpeed = 3;
	facing = DOWN;
}


MainCharacter::~MainCharacter()
{

}


void MainCharacter::MoveWithDisplacement(double dx, double dy)
{
	const int blockSize = 50;
	x += dx;
	y += dy;

}

void MainCharacter::setMoveSpeed(double m)
{
	moveSpeed = m;
}

double MainCharacter::getMoveSpeed()
{
	return moveSpeed;
}

void MainCharacter::setFacing(int f)
{
	facing = f;
}

bool MainCharacter::Hit()
{
	if (damageImmuneCount == 0)
	{
		hp -= 10;
		damageImmuneCount = 1;
		return true;
	}
	return false;
}

void MainCharacter::IncreaseDamageCount()
{
	
	static int currentTime;
	currentTime = timeGetTime();
	int DTime = currentTime - lastTime;

	if (damageImmuneCount > 0)
	{
		this->damageImmuneCount += DTime;
	}
	lastTime = currentTime;

	if (damageImmuneCount >= damageImmuneSecond)
		damageImmuneCount = 0;
}

int MainCharacter::getHp()
{
	return hp;
}



void MainCharacter::setGrpahCode(int c)
{
	graphCode = c;
}

int MainCharacter::getGraphCode()
{
	return graphCode;
}

int MainCharacter::getFacing()
{
	return facing;
}

int MainCharacter::getId()
{
	return id;
}

int MainCharacter::getStatus()
{
	return status;
}

void MainCharacter::setStatus(int s)
{
	status = s;
}

void MainCharacter::setCmdFlag(int f)
{
	command_flag |= f;
}

void MainCharacter::setCmdFlag(int f, int _id)
{
	command_flag |= f;
	if(f == 0x00000002)
		newChar_id = _id;
	else if(f == 0x00000008)
		delChar_id = _id;
}

int MainCharacter::getCmdFlag()
{
	return command_flag;
}

void MainCharacter::clearCmdFlag()
{
	command_flag &= 0x00000000;
}


int MainCharacter::getNewCharID()
{
	return newChar_id;
}

void MainCharacter::clearNewCharID()
{
	newChar_id = 0;
}

int MainCharacter::getDelCharID()
{
	return delChar_id;
}

void MainCharacter::clearDelCharID()
{
	delChar_id = 0;
}

std::string MainCharacter::getCharName()
{
	return charName;
}

int MainCharacter::getBombX()
{
	return bomb_x;
}

int MainCharacter::getBombY()
{
	return bomb_y;
}

void MainCharacter::setBomb(int x, int y)
{
	bomb_x = x;
	bomb_y = y;
}

void MainCharacter::clearBomb()
{
	bomb_x = bomb_y = 0;
}

void MainCharacter::setHitID(int _id)
{
	hit_id = _id;
}

int MainCharacter::getHitID()
{
	return hit_id;
}

