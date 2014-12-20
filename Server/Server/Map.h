#pragma once
#include "Block.h"
#include "Bomb.h"
#include "Blast.h"
#include <vector>
#include "stdafx.h"
class Map 
{
	const int blockX;
	const int blockY;
	const int blockSize;
	char **blockMap; 
	char **bombMap;
	int **blastMap;
	Bomb bomb;
	Blast blast;
	Blast mblast;
	vector <Block *> vBlock;
	vector <Bomb *> vBomb;
	vector <Blast *> vBlast;
public:
	Map();
	~Map();
	char ***getBlockMap();
	int ***getBlastMap();
	vector <Block *> &getBlockVector();
	vector <Bomb *> &getBombVector();
	vector <Blast *> &getBlastVector();
	void MakeMap();
	int getBlockX();
	int getBlockY();
	int getBlockSize();
	Bomb *getBomb();
	Blast *getBlast();
	Blast *getmBlast();
	bool DropBomb(double x, double y);
	void ClearBomb(int );
	void UpdateBombTimer();
	void CheckBombExplode();
	void MakeBlast(int arrX, int arrY);
	void UpdateBlastTimer();
	void CheckBlastGrow();
};

