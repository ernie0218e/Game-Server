#include "AI.h"
#include "Map.h"
#include <string>
#pragma once
using namespace std;
class AI_System
{
	AI *ai;
	Map *map;
public:
	AI_System(MainCharacter *, Map *);
	~AI_System(void);
	int getKey();
	void compute();
};

