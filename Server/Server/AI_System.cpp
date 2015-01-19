#include "StdAfx.h"
#include "AI_System.h"

AI_System::AI_System(MainCharacter *mainChar, Map *map, MainGame *game)
{
	this->map = map;
	ai = new AI();
	ai->AssignMe(mainChar);
	this->game = game;
	nopeMap = new char*[map->getBlockX()];
	for(int i=0 ; i<map->getBlockY() ; i++)
	{
		nopeMap[i] = new char [map->getBlockY()];
	}
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
	int arrX, arrY;
	int destX=0, destY=0;
	ai->Update();

	//if(CheckDie())
	if(CheckDie()||
		(DieTest(ai->getArrX()+1, ai->getArrY()))||
		(DieTest(ai->getArrX(), ai->getArrY()+1))||
		(DieTest(ai->getArrX()-1, ai->getArrY()))||
		(DieTest(ai->getArrX(), ai->getArrY()-1)))
	{
	//	if(!ai->getEvading())
		{
			ai->setEvading();
			ai->OverRide();
			FindSafe(destX, destY);
			ai->setFinalArrX(destX);
			ai->setFinalArrY(destY);
		}
		MoveEvade(destX, destY);
	}
	else if(ai->getEvading()&&!CheckDie()){
		ai->clearEvading();
		FindEnemy(destX, destY);
		MoveNorm(destX, destY);
	}
	else
	{
		FindEnemy(destX, destY);
		MoveNorm(destX, destY);
		switch (ai->myPath[1])
		{
		case '0':
			arrX = ai->getArrX()+1;
			arrY = ai->getArrY();
			//ai->MoveRight();
			break;
		case '1':
			arrX = ai->getArrX();
			arrY = ai->getArrY()+1;
			//ai->MoveDown();
			break;
		case '2':
			arrX = ai->getArrX()-1;
			arrY = ai->getArrY();
			//ai->MoveLeft();
			break;
		case '3':
			arrX = ai->getArrX();
			arrY = ai->getArrY()-1;
			//ai->MoveUp();
			break;

		}
		if( (*map->getBlockMap())[arrY][arrX] == 11 && ai->getMe()->getBombDropCount()<1) 
		{
			ai->DropBomb();
			if(!rand()%3){
				if(ai->MoveDone())
				{
					switch(rand()%4 + '0'){
					case '0':
						if(DieTest(ai->getArrX()+1, ai->getArrY()))
						break;
						ai->MoveRight();
						break;
					case '1':
						if(DieTest(ai->getArrX(), ai->getArrY()+1))
							break;
						ai->MoveDown();
						break;
					case '2':
						if(DieTest(ai->getArrX()-1, ai->getArrY()))
							break;
						ai->MoveLeft();
						break;
					case '3':
						if(DieTest(ai->getArrX(), ai->getArrY()-1))
							break;
						ai->MoveUp();
						break;
					}
				}
			}

		}
		else if(game->vMainChar.size()>1)
		{
			int target=0;
			MainCharacter *tempC;
			for(int i=0 ; i<game->vMainChar.size() ; i++)
			{
				tempC = game->vMainChar[i];
				if(tempC == ai->getMe())
					continue;
				else
				{
					target = i;
					break;
				}

			}
			if(game->vMainChar[target]!=NULL &&
					game->vMainChar[target]!=ai->getMe()){
						string path;
						Findroad road(map->getBlockX(), map->getBlockY());
						setNopeMap();
						nopeMap[ai->getArrY()][ai->getArrX()] = 0;
						road.setmap(&nopeMap);
						path = road.pathFind(ai->getArrX(), ai->getArrY(), 
							game->vMainChar[target]->getX()/map->getBlockSize(),
							game->vMainChar[target]->getY()/map->getBlockSize());
						if(path!="" && path.size()<ai->getMe()->getBombRange())
							ai->DropBomb();
			}

		}
	}

	
}
void AI_System::FindSafe(int &destX, int &destY)
{

/*
	Findroad road(map->getBlockX(), map->getBlockY());
	road.setmap(&nopeMap);
	path = road.pathFind(ai->getArrX(), ai->getArrY(), pt_x.top(), pt_y.top());
	string path;
	stack <int>pt_x;
	stack <int>pt_y;
	stack <int>min;
	min.push((abs(ai->getArrX()) + abs(ai->getArrY())));
	pt_x.push(ai->getArrX());
	pt_y.push(ai->getArrY());
	for(int i = 0;i < map->getBlockX();i++){
		for(int j = 0;j < map->getBlockY();j++){
			if(nopeMap[j][i] == 0){
				if((abs(ai->getArrX() - i) + abs(ai->getArrY() - j)) <= min.top()){
					min.push((abs(ai->getArrX() - i) + abs(ai->getArrY() - j)));
					pt_x.push(i);
					pt_y.push(j);
				}
			}
		}
	}
	path = road.pathFind(ai->getArrX(), ai->getArrY(), pt_x.top(), pt_y.top());
	while(path == "" && !min.empty() && !pt_x.empty() && !pt_y.empty()){
		min.pop();
		pt_x.pop();
		pt_y.pop();
		path = road.pathFind(ai->getArrX(), ai->getArrY(), pt_x.top(), pt_y.top());
	}
	if(min.empty()){
		destX = ai->getArrX();
		destY = ai->getArrY();
	}

	if(path != ""){
		destX = pt_x.top();
		destY = pt_y.top();
	}else{
		destX = ai->getArrX();
		destY = ai->getArrY();
	}*/
	//nopeMap[ai->getArrY()][ai->getArrX()]
	//up, down, left, right
	string path;
	Findroad road(map->getBlockX(), map->getBlockY());
	setNopeMap();
	nopeMap[ai->getArrY()][ai->getArrX()] = 0;
	road.setmap(&nopeMap);


	const int dirCount = 80;
	int hor[80] ={-1,0,1,1,1,0,-1,-1,-2,-1,0,1,2,2,2,2,2,1,0,-1,-2,-2,-2,-2,-3,-2,-1,0,1,2,3,3,3,3,3,3,3,2,1,0,-1,-2,-3,-3,-3,-3,-3,-3,-4,-3,-2,-1,0,1,2,3,4,4,4,4,4,4,4,4,4,3,2,1,0,-1,-2,-3,-4,-4,-4,-4,-4,-4,-4,-4};
	int ver[80] = {-1,-1,-1,0,1,1,1,0,-2,-2,-2,-2,-2,-1,0,1,2,2,2,2,2,1,0,-1,-3,-3,-3,-3,-3,-3,-3,-2,-1,0,1,2,3,3,3,3,3,3,3,2,1,0,-1,-2,-4,-4,-4,-4,-4,-4,-4,-4,-4,-3,-2,-1,0,1,2,3,4,4,4,4,4,4,4,4,4,3,2,1,0,-1,-2,-3};
	for(int i=0 ; i<dirCount ; i++)
	{
		destX = ai->getArrX()+hor[i];
		destY = ai->getArrY()+ver[i];
		if(destX<0 || destY <0 || destX>=map->getBlockX() || destY>=map->getBlockY())
			continue;
		if(nopeMap[ai->getArrY()+ver[i]][ai->getArrX()+hor[i]] == 0)
		{
			path = road.pathFind(ai->getArrX(), ai->getArrY(), destX,destY);
			if(path!="")
				break;
		}
	}
}

bool AI_System::CheckDie()
{
	setNopeMap();
	if(nopeMap[ai->getArrY()][ai->getArrX()] == 1)
		return 1;
	return 0;
}

void AI_System::setNopeMap()
{
	for(int i=0 ; i<map->getBlockY() ; i++)
		for(int r=0 ; r<map->getBlockX() ; r++)
			nopeMap[i][r] = 0;
	for(int i=0 ; i<map->getBlockY() ; i++)
	{
		for(int r=0 ; r<map->getBlockX() ; r++)
		{
			if((*map->getBlastMap())[i][r]!=99999)
				nopeMap[i][r]=1;
		}
	}
	for(int i=0 ; i<map->getBlockY() ; i++)
	{
		for(int r=0 ; r<map->getBlockX() ; r++)
		{
			if((*map->getBlockMap())[i][r]!=0)
				nopeMap[i][r]=2;
		}
	}

/*
	for(int i=0 ; i<map->getBombVector().size() ; i++)
	{
		for(int r=0 ; r<map->getBlockY() ; r++)
		{
			nopeMap[r][map->getBombVector()[i]->getArrX()] = 1;
		}
		for(int r=0 ; r<map->getBlockX() ; r++)
		{
			nopeMap[map->getBombVector()[i]->getArrY()][r] = 1;
		}
	}*/

	for(int i=0 ; i<map->getBombVector().size() ; i++)
	{
		if(ai->getArrX()==map->getBombVector()[i]->getArrX() && 
			ai->getArrY()==map->getBombVector()[i]->getArrY())
			nopeMap[ai->getArrY()][ai->getArrX()] = 1;
		if(map->getBombVector()[i]->getExplodeSecond() -
			map->getBombVector()[i]->getExplodeCount()
				> map->getBombVector()[i]->getBombRange() * map->getBlockSize()*8/ (ai->getMoveSpeed()))
				continue;
		bombMap(map->getBombVector()[i]->getArrX(),
				map->getBombVector()[i]->getArrY(),
				map->getBombVector()[i]->getBombRange());
		nopeMap[map->getBombVector()[i]->getArrY()][map->getBombVector()[i]->getArrX()] = 1;
	}
	for(int i=0 ; i<map->getBlastVector().size() ; i++)
	{
		if(ai->getArrX()==map->getBlastVector()[i]->getArrX() && 
			ai->getArrY()==map->getBlastVector()[i]->getArrY())
			nopeMap[ai->getArrY()][ai->getArrX()] = 1;
		if(map->getBlastVector()[i]->getDirection()==Blast::STATIC)
		bombMap(map->getBlastVector()[i]->getArrX(),
			map->getBlastVector()[i]->getArrY(),
			map->getBlastVector()[i]->getBombRange()+1);
		//	nopeMap[map->getBombVector()[i]->getArrY()][map->getBombVector()[i]->getArrX()] = 1;
	}
}
void AI_System::bombMap(int x,int y,int z)
{
	int i,j;
	for(i=0;(i<=z)&&(y+i<map->getBlockY());i++)
	{
		nopeMap[y+i][x]=1;
	}
	for(i=0;(i<=z)&&(x+i<map->getBlockX());i++)
	{
		nopeMap[y][x+i]=1;
	}
	for(i=0;(i<=z)&&(y-i>=0);i++)
	{
		nopeMap[y-i][x]=1;
	}
	for(i=0;(i<=z)&&(x-i>=0);i++)
	{
		nopeMap[y][x-i]=1;
	}
}

void AI_System::MoveEvade(int x, int y)
{
	setNopeMap();
	Findroad road(map->getBlockX(), map->getBlockY());
	nopeMap[ai->getArrY()][ai->getArrX()] = 0;
	road.setmap(&nopeMap);
	if(ai->MoveDone())
	{
		ai->myPath = road.pathFind(ai->getArrX(), ai->getArrY(), x, y);
		switch(ai->myPath[0]){
		case '0':
			if(DieTest(ai->getArrX()+1, ai->getArrY()))
				break;
			ai->MoveRight();
			break;
		case '1':
			if(DieTest(ai->getArrX(), ai->getArrY()+1))
				break;
			ai->MoveDown();
			break;
		case '2':
			if(DieTest(ai->getArrX()-1, ai->getArrY()))
				break;
			ai->MoveLeft();
			break;
		case '3':
			if(DieTest(ai->getArrX(), ai->getArrY()-1))
				break;
			ai->MoveUp();
			break;
		}
	}
}
void AI_System::MoveNorm(int x, int y)
{
	Findroad road(map->getBlockX(), map->getBlockY());
	road.setMoveMap(map->getBlockMap());
	if(ai->MoveDone())
	{
		ai->myPath = road.pathFind(ai->getArrX(), ai->getArrY(), x, y);
		switch(ai->myPath[0]){
		case '0':
			if(DieTest(ai->getArrX()+1, ai->getArrY()))
				break;
			ai->MoveRight();
			break;
		case '1':
			if(DieTest(ai->getArrX(), ai->getArrY()+1))
				break;
			ai->MoveDown();
			break;
		case '2':
			if(DieTest(ai->getArrX()-1, ai->getArrY()))
				break;
			ai->MoveLeft();
			break;
		case '3':
			if(DieTest(ai->getArrX(), ai->getArrY()-1))
				break;
			ai->MoveUp();
			break;
		}
	}
}
void AI_System::FindEnemy(int &destX, int &destY)
{
	MainCharacter *tempC;
	int dx, dy;
	for(int i=0 ; i<game->vMainChar.size() ; i++)
	{
		tempC = game->vMainChar[i];
		if(tempC == ai->getMe())
			continue;
		else if(tempC != NULL)
		{
			destX = tempC->getX()/map->getBlockSize();
			destY = tempC->getY()/map->getBlockSize();
			break;
		}

	}
}

bool AI_System::DieTest(int arrX, int arrY)
{
	setNopeMap();
	if(nopeMap[arrY][arrX] == 1)
		return 1;
	return 0;
}



