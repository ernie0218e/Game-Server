#include "Map.h"
#include "MainGame.h"
#include "Blast.h"
#include <Mmsystem.h>
#include "stdafx.h"
#include <vector>
#pragma comment(lib, "Winmm.lib")

Map::Map() : blockX(25), blockY(17), blockSize(45)
{
	int i;
	int r;
	
	blockMap = new char*[blockX];
	bombMap = new char*[blockX];
	blastMap = new int*[blockX];

	for (i = 0; i < blockX; i++)
	{
		blockMap[i] = new char[blockY];
		bombMap[i] = new char[blockY];
		blastMap[i] = new int[blockY];
	}

	for (i = 0 ; i < blockY ; i++)
		for (r = 0; r < blockX; r++)
		{		
			bombMap[i][r] = 0;
			blastMap[i][r] = 99999;
		}
	
}

int Map::getBlockSize()
{
	return blockSize;
}


Map::~Map()
{
	for (int i = 0; i < blockX; i++)
		delete[] blockMap[i];
	delete[] blockMap;
}


void Map::MakeMap()
{
	//10~19 炸彈
	//100~200 方塊
	//200~250 道具
	int i, r;

	const double scale = 1.0;
	for (i = 0; i < blockY; i++){
		for (r = 0; r < blockX; r++)
		{

			if (r == 0 || i == 0 || i == blockY - 1 || r == blockX - 1)
				blockMap[i][r] = 100;
			else if (r % 2 == 0 && i % 2 == 0)
				blockMap[i][r] = 100;
			else 
				blockMap[i][r] = 0;
			
		}
	}
	for (i = 0; i < blockY; i++){
		for (r = 0; r < blockX; r++){
			Block *b = new Block(scale*blockSize*r + 0.5*blockSize, scale*blockSize*i + 0.5*blockSize, blockMap[i][r], r, i);
			vBlock.push_back(b);
		}
	}
}

char *** Map::getBlockMap()
{
	return &blockMap;
}

vector <Block *> & Map::getBlockVector()
{
	return this->vBlock;
}

int Map::getBlockY()
{
	return blockY;
}

int Map::getBlockX()
{
	return blockX;
}

bool Map::DropBomb(double x, double y)
{
	if (bombMap[(int)y / blockSize][(int)x / blockSize] == 0)
	{
		Bomb *tempB = new Bomb;
		tempB->setX(x);
		tempB->setY(y);
		tempB->setArrX((int)x / blockSize);
		tempB->setArrY((int)y / blockSize);
		vBomb.push_back(tempB);

		bombMap[(int)y / blockSize][(int)x / blockSize] = 1;
		
		return true;
	}
	return false;
}

Bomb *Map::getBomb()
{
	return &bomb;
}

vector <Blast *> & Map::getBlastVector()
{
	return this->vBlast;
}

vector <Bomb *> & Map::getBombVector()
{
	return this->vBomb;
}

void Map::UpdateBombTimer()
{
	static int lastTime = timeGetTime();
	static int currentTime;
	int max = vBomb.size();
	currentTime = timeGetTime();
	Bomb *tempB;

	int DTime = currentTime - lastTime;
	for (int i = 0; i < max; i++)
	{
		tempB = vBomb[i];
		if (!tempB->getExploded())
			tempB->increaseExplodeCount(DTime);
		else
			tempB->increaseBlastCount(DTime);
	}

	lastTime = currentTime;
}

void Map::CheckBombExplode()
{

	Bomb *tempB;
	int max = vBomb.size();
	for (int i = 0; i < max; i++)
	{
		tempB = vBomb[i];


		if (!tempB->getExploded())
		{
			if (tempB->getExplodeCount() >= tempB->getExplodeSecond())
			{
				tempB->setExploded();
				///implement explosion here////////////////////////

			}
		}
		else if (tempB->getBlastCount() >= tempB->getBlastSecond())
		{

			MakeBlast(tempB->getArrX(), tempB->getArrY());
			bombMap[tempB->getArrY()][tempB->getArrX()] = 0;
			delete tempB;
			vBomb.erase(vBomb.begin() + i);
			i--;
			max--;
		}
	}

	

}

void Map::MakeBlast(int arrX, int arrY)
{

	Blast *tempB;

	tempB = new Blast;
	tempB->setDirection(Blast::STATIC);
	tempB->setArrX(arrX);
	tempB->setArrY(arrY);
	tempB->setId(vBlast.size());
	blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
	vBlast.push_back(tempB);

	if (arrY - 1 >= 0 && blockMap[arrY - 1][arrX] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::UP);
		tempB->setArrX(arrX);
		tempB->setArrY(arrY-1);
		tempB->setId(vBlast.size());
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY - 1)*blockX + arrX]->getDestructible())
	{
		delete vBlock[(arrY - 1)*blockX + arrX];
		vBlock[(arrY - 1)*blockX + arrX] = nullptr;
		blockMap[arrY - 1][arrX] = 0;
	}
	if (arrY + 1 <= blockY-1 && blockMap[arrY + 1][arrX] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::DOWN);
		tempB->setArrX(arrX);
		tempB->setArrY(arrY + 1);
		tempB->setId(vBlast.size());
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY + 1)*blockX + arrX]->getDestructible())
	{
		delete vBlock[(arrY + 1)*blockX + arrX];
		vBlock[(arrY + 1)*blockX + arrX] = nullptr;
		blockMap[arrY + 1][arrX] = 0;
	}
	if (arrX + 1 <= blockX-1 && blockMap[arrY][arrX+1] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::RIGHT);
		tempB->setArrX(arrX + 1);
		tempB->setArrY(arrY);
		tempB->setId(vBlast.size());
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY)*blockX + arrX+1]->getDestructible())
	{
		delete vBlock[(arrY)*blockX + arrX+1];
		vBlock[(arrY)*blockX + arrX+1] = nullptr;
		blockMap[arrY][arrX+1] = 0;
	}
	if (arrX - 1 >= 0 && blockMap[arrY][arrX-1] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::LEFT);
		tempB->setArrX(arrX - 1);
		tempB->setArrY(arrY);
		tempB->setId(vBlast.size());
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY)*blockX + arrX - 1]->getDestructible())
	{
		delete vBlock[(arrY)*blockX + arrX - 1];
		vBlock[(arrY)*blockX + arrX - 1] = nullptr;
		blockMap[arrY][arrX - 1] = 0;
	}
}

Blast * Map::getBlast()
{
	return &blast;
}

void Map::UpdateBlastTimer()
{
	static int lastTime = timeGetTime();
	static int currentTime;
	int max = vBlast.size();
	currentTime = timeGetTime();

	int DTime = currentTime - lastTime;
	for (int i = 0; i < max; i++)
	{
		vBlast[i]->increaseGrowCount(DTime);
	}

	lastTime = currentTime;
}

void Map::CheckBlastGrow()
{
	static int lastTime = timeGetTime();
	static int currentTime;
	int max = vBlast.size();
	int arrY, arrX;
	currentTime = timeGetTime();
	Blast *xtempB;
	Blast *tempB;

	int DTime = currentTime - lastTime;
	for (int i = 0; i < max; i++)
	{
		xtempB = vBlast[i];
		arrY = xtempB->getArrY();
		arrX = xtempB->getArrX();
		if (!xtempB->getGrown())
		{
			if (xtempB->getGrowCount() >= xtempB->getGrowSecond())
			{
				switch (xtempB->getDirection())
				{
				case Blast::UP:
					if (arrY - 1 >= 0 && blockMap[arrY - 1][arrX] == 0)
					{
						tempB = new Blast;
						tempB->setDirection(Blast::UP);
						tempB->setArrX(arrX);
						tempB->setArrY(arrY - 1);
						tempB->setId(vBlast.size());
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY - 1)*blockX + arrX]->getDestructible())
					{
						delete vBlock[(arrY - 1)*blockX + arrX];
						vBlock[(arrY - 1)*blockX + arrX] = nullptr;
						blockMap[arrY - 1][arrX] = 0;
						//append to the info stream
					}
					break;
				case Blast::DOWN:
					if (arrY + 1 <= blockY - 1 && blockMap[arrY + 1][arrX] == 0)
					{
						tempB = new Blast;
						tempB->setDirection(Blast::DOWN);
						tempB->setArrX(arrX);
						tempB->setArrY(arrY + 1);
						tempB->setId(vBlast.size());
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY + 1)*blockX + arrX]->getDestructible())
					{
						delete vBlock[(arrY + 1)*blockX + arrX];
						vBlock[(arrY + 1)*blockX + arrX] = nullptr;
						blockMap[arrY + 1][arrX] = 0;
						//append to the info stream
					}
					break;
				case Blast::RIGHT:
					if (arrX + 1 <= blockX-1 && blockMap[arrY][arrX + 1] == 0)
					{
						tempB = new Blast;
						tempB->setDirection(Blast::RIGHT);
						tempB->setArrX(arrX + 1);
						tempB->setArrY(arrY);
						tempB->setId(vBlast.size());
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY)*blockX + arrX + 1]->getDestructible())
					{
						delete vBlock[(arrY)*blockX + arrX + 1];
						vBlock[(arrY)*blockX + arrX + 1] = nullptr;
						blockMap[arrY][arrX + 1] = 0;
						//append to the info stream
					}
					break;
				case Blast::LEFT:
					if (arrX - 1 >=0 && blockMap[arrY][arrX - 1] == 0)
					{
						tempB = new Blast;
						tempB->setDirection(Blast::LEFT);
						tempB->setArrX(arrX - 1);
						tempB->setArrY(arrY);
						tempB->setId(vBlast.size());
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY)*blockX + arrX - 1]->getDestructible())
					{
						delete vBlock[(arrY)*blockX + arrX - 1];
						vBlock[(arrY)*blockX + arrX - 1] = nullptr;
						blockMap[arrY][arrX - 1] = 0;
						//append to the info stream
					}
					break;
				}
				xtempB->setGrown();
			}
			
		}
		else if (xtempB->getGrowCount() >= xtempB->getDisappearSecond())
		{
			if (blastMap[xtempB->getArrY()][xtempB->getArrX()] == xtempB->getId())
				blastMap[xtempB->getArrY()][xtempB->getArrX()] = 99999;
			delete xtempB;
			vBlast.erase(vBlast.begin() + i);
			i--;
			max--;
		}

	}


	lastTime = currentTime;
}

Blast * Map::getmBlast()
{
	return &mblast;
}

int *** Map::getBlastMap()
{
	return &blastMap;
}
