#include "Map.h"
#include "MainGame.h"
#include "Blast.h"
#include <Mmsystem.h>
#include "stdafx.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#pragma comment(lib, "Winmm.lib")
const int item_p = 10;
Map::Map() : blockX(25), blockY(17), blockSize(45)
{
	int i;
	int r;
	const int MAPCOUNT = 2;
	char chr;
	static char *fileName = new char[100];
	srand(timeGetTime());
	sprintf(fileName, ".//map//%d.map", rand()%MAPCOUNT+1);
	ifstream infile(fileName);
	blockMap = new char*[blockX];
	bombMap = new char*[blockX];
	blastMap = new int*[blockX];
	itemMap = new int*[blockX];

	for (i = 0; i < blockX; i++)
	{
		blockMap[i] = new char[blockY];
		bombMap[i] = new char[blockY];
		blastMap[i] = new int[blockY];
		itemMap[i] = new int[blockY];
	}

	for (i = 0 ; i < blockY ; i++)
		for (r = 0; r < blockX; r++)
		{		
			infile>>chr;
			switch(chr)
			{
			case '0':
				blockMap[i][r] = 0;
				break;
			case '1':
				blockMap[i][r] = 100;
				break;
			}
			bombMap[i][r] = 0;
			blastMap[i][r] = 99999;
			itemMap[i][r] = 0;
		}
		infile.close();
	
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
	srand(timeGetTime());
	const double scale = 1.0;
	for (i = 0; i < blockY; i++){
		for (r = 0; r < blockX; r++)
		{
			if(blockMap[i][r]==100)
				continue;

			if (r == 0 || i == 0 || i == blockY - 1 || r == blockX - 1)
				blockMap[i][r] = 100;
			else if ( (i==blockY-2||i==blockY-3||i==1||i==2)&&(r==1||r==2||r==blockX-2||r==blockX-3) )
				blockMap[i][r] = 0;
			else 
			{
				switch (rand()%3)
				{
				case 0:
					//blockMap[i][r] = 100;
					blockMap[i][r] = 11;
					break;
				case 1:
					blockMap[i][r] = 0;
					break;
				case 2:
					blockMap[i][r] = 11;
					break;
				}

			}
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
void Map::DropItem(int x, int y)
{
	x = x * blockSize + 0.5*blockSize;
	y = y * blockSize + 0.5*blockSize;
	newItem_x.push(x);
	newItem_y.push(y);
	Item *tempI = new Item;
	tempI->setX(x);
	tempI->setY(y);
	tempI->setArrX((int)x / blockSize);
	tempI->setArrY((int)y / blockSize);
	tempI->setType(Item::randItemType());
	itemMap[(int)y / blockSize][(int)x / blockSize] = tempI->getType();
	newItem_type.push(tempI->getType());
	vItem.push_back(tempI);
}

bool Map::DropBomb(double x, double y, int range, int id)
{
	if (bombMap[(int)y / blockSize][(int)x / blockSize] == 0)
	{
		Bomb *tempB = new Bomb;
		tempB->setX(x);
		tempB->setY(y);
		tempB->setArrX((int)x / blockSize);
		tempB->setArrY((int)y / blockSize);
		tempB->setID(id);
		tempB->setBombRange(range);
		//tempB->setBombRange(2);
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

void Map::CheckBombExplode(vector <MainCharacter *> &vMainChar)
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
			for(int r=0 ; r<vMainChar.size() ; r++)
			{
				if(vMainChar[r]!=nullptr && tempB->getID() == vMainChar[r]->getId())
				{
					vMainChar[r]->decreaseBombDropCount();
					break;
				}
			}
			MakeBlast(tempB->getArrX(), tempB->getArrY(), tempB->getBombRange());
			bombMap[tempB->getArrY()][tempB->getArrX()] = 0;
			delete tempB;
			vBomb.erase(vBomb.begin() + i);
			i--;
			max--;
		}
	}

	

}

void Map::MakeBlast(int arrX, int arrY, int range)
{

	Blast *tempB;
	tempB = new Blast;
	tempB->setDirection(Blast::STATIC);
	tempB->setArrX(arrX);
	tempB->setArrY(arrY);
	tempB->setBombRange(range);
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
		tempB->setBombRange(range);
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY - 1)*blockX + arrX]->getDestructible())
	{
		delete vBlock[(arrY - 1)*blockX + arrX];
		vBlock[(arrY - 1)*blockX + arrX] = nullptr;
		blockMap[arrY - 1][arrX] = 0;
		if(!(rand() % item_p)){
			DropItem(arrX, arrY - 1);
		}
	}
	if (arrY + 1 <= blockY-1 && blockMap[arrY + 1][arrX] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::DOWN);
		tempB->setArrX(arrX);
		tempB->setArrY(arrY + 1);
		tempB->setId(vBlast.size());
		tempB->setBombRange(range);
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY + 1)*blockX + arrX]->getDestructible())
	{
		delete vBlock[(arrY + 1)*blockX + arrX];
		vBlock[(arrY + 1)*blockX + arrX] = nullptr;
		blockMap[arrY + 1][arrX] = 0;

		if(!(rand() % item_p)){
			DropItem(arrX, arrY + 1);
		}

	}
	if (arrX + 1 <= blockX-1 && blockMap[arrY][arrX+1] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::RIGHT);
		tempB->setArrX(arrX + 1);
		tempB->setArrY(arrY);
		tempB->setId(vBlast.size());
		tempB->setBombRange(range);
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY)*blockX + arrX+1]->getDestructible())
	{
		delete vBlock[(arrY)*blockX + arrX+1];
		vBlock[(arrY)*blockX + arrX+1] = nullptr;
		blockMap[arrY][arrX+1] = 0;

		if(!(rand() % item_p)){
			DropItem(arrX + 1, arrY);
		}

	}
	if (arrX - 1 >= 0 && blockMap[arrY][arrX-1] == 0)
	{
		tempB = new Blast;
		tempB->setDirection(Blast::LEFT);
		tempB->setArrX(arrX - 1);
		tempB->setArrY(arrY);
		tempB->setId(vBlast.size());
		tempB->setBombRange(range);
		blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
		vBlast.push_back(tempB);
	}
	else if (vBlock[(arrY)*blockX + arrX - 1]->getDestructible())
	{
		delete vBlock[(arrY)*blockX + arrX - 1];
		vBlock[(arrY)*blockX + arrX - 1] = nullptr;
		blockMap[arrY][arrX - 1] = 0;
		
		if(!(rand() % item_p)){
			DropItem(arrX - 1, arrY);
		}

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
	int arrY, arrX, range;
	currentTime = timeGetTime();
	Blast *xtempB;
	Blast *tempB;

	int DTime = currentTime - lastTime;
	for (int i = 0; i < max; i++)
	{
		xtempB = vBlast[i];
		arrY = xtempB->getArrY();
		arrX = xtempB->getArrX();
		range = xtempB->getBombRange()-1;
		if (!xtempB->getGrown())
		{
			if(xtempB->getBombRange() <= 1)
			{
				xtempB->setGrown();
			}
			else if (xtempB->getGrowCount() >= xtempB->getGrowSecond())
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
						tempB->setBombRange(range);
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY - 1)*blockX + arrX]->getDestructible())
					{
						delete vBlock[(arrY - 1)*blockX + arrX];
						vBlock[(arrY - 1)*blockX + arrX] = nullptr;
						blockMap[arrY - 1][arrX] = 0;
						//append to the info stream

						if(!(rand() % item_p)){
							DropItem(arrX, arrY - 1);
						}

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
						tempB->setBombRange(range);
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY + 1)*blockX + arrX]->getDestructible())
					{
						delete vBlock[(arrY + 1)*blockX + arrX];
						vBlock[(arrY + 1)*blockX + arrX] = nullptr;
						blockMap[arrY + 1][arrX] = 0;
						//append to the info stream

						if(!(rand() % item_p)){
							DropItem(arrX, arrY + 1);
						}

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
						tempB->setBombRange(range);
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY)*blockX + arrX + 1]->getDestructible())
					{
						delete vBlock[(arrY)*blockX + arrX + 1];
						vBlock[(arrY)*blockX + arrX + 1] = nullptr;
						blockMap[arrY][arrX + 1] = 0;
						//append to the info stream

						if(!(rand() % item_p)){
							DropItem(arrX + 1, arrY);
						}

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
						tempB->setBombRange(range);
						blastMap[tempB->getArrY()][tempB->getArrX()] = vBlast.size();
						vBlast.push_back(tempB);
					}
					else if (vBlock[(arrY)*blockX + arrX - 1]->getDestructible())
					{
						delete vBlock[(arrY)*blockX + arrX - 1];
						vBlock[(arrY)*blockX + arrX - 1] = nullptr;
						blockMap[arrY][arrX - 1] = 0;
						//append to the info stream

						if(!(rand() % item_p)){
							DropItem(arrX - 1, arrY);
						}

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

vector <Item *> & Map::getItemVector()
{
	return vItem;
}

stack <int> & Map::getNewItem_x()
{
	return newItem_x;
}

stack <int> & Map::getNewItem_y()
{
	return newItem_y;
}

int *** Map::getItemMap()
{
	return &itemMap;
}

void Map::GetItem(int x, int y, int type)
{
	for(int i = 0;i < vItem.size();i++){
		if(vItem[i]->getArrX() == x && vItem[i]->getArrY() == y){
			getItem_x.push(x * blockSize + 0.5*blockSize);
			getItem_y.push(y * blockSize + 0.5*blockSize);
			getItem_type.push(vItem[i]->getType());
			delete vItem[i];
			vItem.erase(vItem.begin() + i);
			itemMap[y][x] = 0;
			break;
		}
	}
}

stack <int> & Map::getNewItemType()
{
	return newItem_type;
}

stack <int> & Map::getGetItem_x()
{
	return getItem_x;
}

stack <int> & Map::getGetItem_y()
{
	return getItem_y;
}

stack <int> & Map::getGetItem_type()
{
	return getItem_type;
}


