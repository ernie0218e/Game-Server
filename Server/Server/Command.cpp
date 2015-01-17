#include "StdAfx.h"
#include "Command.h"


Command::Command(void)
{
	command_flag = 0;
	delChar_id = 0;
	newChar_id = 0;
}


Command::~Command(void)
{
	while(!bomb_x.empty()){
		bomb_x.pop();
	}
	while(!bomb_y.empty()){
		bomb_y.pop();
	}
	while(!hit_id.empty()){
		hit_id.pop();
	}
}

void Command::setCmdFlag(int f)
{
	command_flag |= f;
}

void Command::setCmdFlag(int f, int _id)
{
	command_flag |= f;
	if(f == 0x00000002)
		newChar_id = _id;
	else if(f == 0x00000008)
		delChar_id = _id;
}

int Command::getCmdFlag()
{
	return command_flag;
}

void Command::clearCmdFlag()
{
	command_flag &= 0x00000000;
}


int Command::getNewCharID()
{
	return newChar_id;
}

void Command::clearNewCharID()
{
	newChar_id = 0;
}

int Command::getDelCharID()
{
	return delChar_id;
}

void Command::clearDelCharID()
{
	delChar_id = 0;
}

stack<int>& Command::getBombX()
{
	return bomb_x;
}

stack<int>& Command::getBombY()
{
	return bomb_y;
}

stack<int>& Command::getHitID()
{
	return hit_id;
}

void Command::setBomb(int x, int y)
{
	bomb_x.push(x);
	bomb_y.push(y);
}

void Command::setHitID(int _id)
{
	hit_id.push(_id);
}
