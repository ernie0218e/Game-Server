#include "StdAfx.h"
#include "AI_System.h"

AI_System::AI_System(MainCharacter *mainChar, Map *map)
{
	this->map = map;
	ai = new AI();
	ai->AssignMe(mainChar);
}


AI_System::~AI_System(void)
{
}

int AI_System::getKey()
{
	return ai->getKey();
}

void AI_System::compute()
{
	string path;
	ai->Update();
	Findroad road(map->getBlockX(), map->getBlockY());
	road.setmap(map->getBlockMap());
	if(ai->MoveDone()){
		path = road.pathFind(ai->getArrX(), ai->getArrY(), 21, 13);
		switch(path[0]){
			case '0':
				ai->MoveRight();
				break;
			case '1':
				ai->MoveDown();
				break;
			case '2':
				ai->MoveLeft();
				break;
			case '3':
				ai->MoveUp();
				break;
		}
	}

	/*
	if(done == 0 && ai->MoveDone()){
		ai->MoveRight();
		done = 1;
	}else if(done == 1 && ai->MoveDone()){
		ai->MoveDown();
		done = 2;
	}else if(done == 2 && ai->MoveDone()){
		ai->MoveLeft();
		done = 3;
	}else if(done == 3 && ai->MoveDone()){
		ai->MoveUp();
		done = 0;
	}*/
}
