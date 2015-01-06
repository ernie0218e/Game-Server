#include "MainCharacter.h"
#include <math.h>
#include "stdafx.h"
MainCharacter::MainCharacter(double x, double y, int graphCode, int id)
{
	command_flag = 0;
	newChar_id = 0;
	delChar_id = 0;
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

void MainCharacter::Hit()
{
	if (damageImmuneCount == 0)
	{
		hp -= 10;
		damageImmuneCount = 1;
	}
}

void MainCharacter::IncreaseDamageCount()
{
	static int lastTime = timeGetTime();
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

