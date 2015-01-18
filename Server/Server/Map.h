#pragma once
#include "Block.h"
#include "Bomb.h"
#include "Blast.h"
#include <vector>
#include <stack>
#include "stdafx.h"
#include "Item.h"
#include "MainCharacter.h"
class Map 
{
	const int blockX;
	const int blockY;
	const int blockSize;
	char **blockMap;
	int **itemMap;
	char **bombMap;
	int **blastMap;
	Bomb bomb;
	Blast blast;
	Blast mblast;
	vector <Block *> vBlock;
	vector <Bomb *> vBomb;
	vector <Blast *> vBlast;
	vector <Item *> vItem;
	stack <int> newItem_x;
	stack <int> newItem_y;
	stack <int> newItem_type;
	stack <int> getItem_x;
	stack <int> getItem_y;
	stack <int> getItem_type;
public:
	Map();
	~Map();
	char ***getBlockMap();
	int ***getBlastMap();
	int ***getItemMap();
	vector <Block *> &getBlockVector();
	vector <Bomb *> &getBombVector();
	vector <Blast *> &getBlastVector();
	vector <Item *> &getItemVector();
	stack <int> &getNewItem_x();
	stack <int> &getNewItem_y();
	stack <int> &getNewItemType();
	stack <int> &getGetItem_x();
	stack <int> &getGetItem_y();
	stack <int> &getGetItem_type();
	void MakeMap();
	int getBlockX();
	int getBlockY();
	int getBlockSize();
	Bomb *getBomb();
	Blast *getBlast();
	Blast *getmBlast();
	void GetItem(int, int, int);
	bool DropBomb(double x, double y, int range, int id);
	void DropItem(int x, int y);
	void ClearBomb(int );
	void UpdateBombTimer();
	void CheckBombExplode(vector <MainCharacter *> &vMainChar);
	void MakeBlast(int arrX, int arrY, int range);
	void UpdateBlastTimer();
	void CheckBlastGrow();
};

