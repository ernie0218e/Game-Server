#include "MainCharacter.h"
#include <math.h>
#include "stdafx.h"
#include <string>
MainCharacter::MainCharacter(double x, double y, int graphCode, int id, string name)
{
	try{
		cmd = new Command();
	}catch(bad_alloc &b){
		throw b.what();
	}
	charName = name;
	lastTime = timeGetTime();
	this->id = id;
	this->graphCode = graphCode;
	damageImmuneCount = 0;
	damageImmuneSecond = 700;
	bombDropCount = 0;
	bombDropMax = 3;
	this->x = x;
	this->y = y;
	hp = 5;
	moveSpeed = 3;
	facing = DOWN;
	bombRange = 1;
}


MainCharacter::~MainCharacter()
{
	delete cmd;
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
		hp --;
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


std::string MainCharacter::getCharName()
{
	return charName;
}

int MainCharacter::getBombRange()
{
	return bombRange;
}

int MainCharacter::getBombDropCount()
{
	return bombDropCount;
}

int MainCharacter::getBombDropMax()
{
	return bombDropMax;
}

void MainCharacter::decreaseBombDropCount()
{
	bombDropCount--;
}

void MainCharacter::increaseBombDropCount()
{
	bombDropCount++;
}

void MainCharacter::increaseBombDropMax()
{
	bombDropMax++;
}

void MainCharacter::decreaseBombDropMax()
{
	bombDropMax--;
}








