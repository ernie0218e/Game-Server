#pragma once
#include "Block.h"
#include "Bomb.h"
#include "Blast.h"
#include <vector>
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
public:
	Map();
	~Map();
	char ***getBlockMap();
	int ***getBlastMap();
	vector <Block *> &getBlockVector();
	vector <Bomb *> &getBombVector();
	vector <Blast *> &getBlastVector();
	vector <Item *> &getItemVector();
	void MakeMap();
	int getBlockX();
	int getBlockY();
	int getBlockSize();
	Bomb *getBomb();
	Blast *getBlast();
	Blast *getmBlast();
	bool DropBomb(double x, double y, int range, int id);
	void DropItem(int x, int y);
	void ClearBomb(int );
	void UpdateBombTimer();
	void CheckBombExplode(vector <MainCharacter *> &vMainChar);
	void MakeBlast(int arrX, int arrY, int range);
	void UpdateBlastTimer();
	void CheckBlastGrow();
};

