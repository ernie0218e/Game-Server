#pragma once
#include "AI.h"
#include "Map.h"
#include "MainGame.h"
#include <string>

using namespace std;
class AI_System
{
	AI *ai;
	Map *map;
	char **nopeMap;
	MainGame *game;
public:
	AI_System(MainCharacter *, Map *, MainGame *);
	~AI_System(void);
	int getKey();
	void compute();
	bool CheckDie();
	bool DieTest(int arrX, int arrY);
	void setNopeMap();
	void MoveEvade(int x, int y);
	void MoveNorm(int x, int y);
	void FindSafe(int &destX, int &destY);
	void FindEnemy(int &destX, int &destY);
	void bombMap(int x,int y,int z);
};

