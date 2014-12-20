#include "MainGame.h"
#include <windows.h>
#include <Mmsystem.h>
#include <memory>
#include <vector>
#include "stdafx.h"
#pragma comment(lib, "Winmm.lib")


MainGame::MainGame()
{

}


//之後要在此新增一個Game，以及新增Character
bool MainGame::Init()
{
	
	mainMap = new Map();
	//mainChar = new MainCharacter(m_ClientWidth / 2, m_ClientHeight / 2, 0);
	mainMap->MakeMap();

	return true;
}


void MainGame::Update()
{

	FrameDelay();
	mainMap->UpdateBombTimer();
	mainMap->CheckBombExplode();
	mainMap->UpdateBlastTimer();
	mainMap->CheckBlastGrow();
	CheckHit(mainChar);
	mainChar->IncreaseDamageCount();
	MoveMainChar(mainChar);

	// read
	// send
	// draw
	// delay
}

MainGame::~MainGame()
{

}

//修改成多人版本
void MainGame::MoveMainChar(MainCharacter* mainChar)
{
	blockMap = mainMap->getBlockMap();
	const double blockScale = 2.5;
	const double scalex = 1.0;
	const double scaley = 1.0;
	const double margin = 1.0;
	const int blockSize = mainMap->getBlockSize();
	int maxX = blockSize*mainMap->getBlockX();
	int maxY = blockSize*mainMap->getBlockY();
	double mainX, mainY, mainMoveSpeed;
	mainX = mainChar->getX();
	mainY = mainChar->getY();
	mainMoveSpeed = mainChar->getMoveSpeed();
	double mainTopMidX = mainX - margin;
	double mainTopMidY = mainY - scaley*blockSize / 2 + margin;
	double mainTopLeftX = mainX - scalex*blockSize / 2 + margin;
	double mainTopRightX = mainX + scalex*blockSize / 2 - margin;
	double mainTopLeftY = mainY - scaley*blockSize / 2 + margin;
	double mainTopRightY = mainY - scaley*blockSize / 2 + margin;
	double mainBottomLeftX = mainX - scalex*blockSize / 2 + margin;
	double mainBottomLeftY = mainY + scaley*blockSize / 2 - margin;
	double mainBottomRightX = mainX + scalex*blockSize / 2 - margin;
	double mainBottomRightY = mainY + scaley*blockSize / 2 - margin;
	double mainBottomMidX = mainX - margin;
	double mainBottomMidY = mainY + scaley*blockSize / 2 - margin;
	double mainMidLeftX = mainX - scalex*blockSize / 2 + margin;
	double mainMidLeftY = mainY - margin;
	double mainMidRightX = mainX + scalex*blockSize / 2 + margin;
	double mainMidRightY = mainY - margin;
	int status;
	/*修改ui的部分
	if (ui->ReadKey())
	{
		status = ui->getStatus();
		if (status&UI::UP)
		{
			int step = 0;
			
			while (step < mainMoveSpeed && (mainTopLeftY - 1)>0&&
				(*blockMap)[(int)(mainTopLeftY - 1) / blockSize][(int)mainTopLeftX / blockSize] == 0 &&
				(*blockMap)[(int)(mainTopRightY - 1) / blockSize][(int)mainTopRightX / blockSize] == 0 &&
				(*blockMap)[(int)(mainTopMidY - 1) / blockSize][(int)mainTopMidX / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, -1);
			}
			while (step < mainMoveSpeed &&!(status&UI::RIGHT) &&
				(*blockMap)[(int)(mainTopLeftY - 1) / blockSize][(int)mainTopLeftX / blockSize] == 0 &&
				(*blockMap)[(int)(mainTopRightY - 1) / blockSize][(int)mainTopRightX / blockSize] !=0)
			{
				step++;
				mainChar->MoveWithDisplacement(-1, 0);
			}
			while (step < mainMoveSpeed &&!(status&UI::LEFT) &&
				(*blockMap)[(int)(mainTopLeftY - 1) / blockSize][(int)mainTopLeftX / blockSize] != 0 &&
				(*blockMap)[(int)(mainTopRightY - 1) / blockSize][(int)mainTopRightX / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(1, 0);
			}
			mainChar->setFacing(MainCharacter::UP);
			
		}
		else if (status&UI::DOWN)
		{
			int step = 0;
			
			while (step < mainMoveSpeed && (mainBottomLeftY + 2)<maxY&&
				(*blockMap)[(int)(mainBottomLeftY + 2) / blockSize][(int)mainBottomLeftX / blockSize] == 0 &&
				(*blockMap)[(int)(mainBottomRightY + 2) / blockSize][(int)mainBottomRightX / blockSize] == 0 &&
				(*blockMap)[(int)(mainBottomMidY + 2) / blockSize][(int)mainBottomMidX / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, 1);
			}
			while (step < mainMoveSpeed &&!(status&UI::RIGHT)&&
				(*blockMap)[(int)(mainBottomLeftY + 2) / blockSize][(int)mainBottomLeftX / blockSize] == 0 &&
				(*blockMap)[(int)(mainBottomRightY + 2) / blockSize][(int)mainBottomRightX / blockSize] != 0)
			{
				step++;
				mainChar->MoveWithDisplacement(-1, 0);
			}
			while (step < mainMoveSpeed &&!(status&UI::LEFT) &&
				(*blockMap)[(int)(mainBottomLeftY + 2) / blockSize][(int)mainBottomLeftX / blockSize] != 0 &&
				(*blockMap)[(int)(mainBottomRightY + 2) / blockSize][(int)mainBottomRightX / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(1, 0);
			}
			mainChar->setFacing(MainCharacter::DOWN);
		}

		else if (status&UI::LEFT)
		{
			int step = 0;
			while (step<mainMoveSpeed && (mainTopLeftX - 2)>0 &&
				   (*blockMap)[(int)mainTopLeftY / blockSize][(int)(mainTopLeftX - 2) / blockSize]==0&&
				   (*blockMap)[(int)mainBottomLeftY / blockSize][(int)(mainBottomLeftX - 2) / blockSize]==0&&
				   (*blockMap)[(int)mainMidLeftY / blockSize][(int)(mainMidLeftX - 2) / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(-1, 0);
			}
			while (step < mainMoveSpeed &&!(status&UI::DOWN) &&
				(*blockMap)[(int)mainTopLeftY / blockSize][(int)(mainTopLeftX - 2) / blockSize] == 0 &&
				(*blockMap)[(int)mainBottomLeftY / blockSize][(int)(mainBottomLeftX - 2) / blockSize] != 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, -1);
			}
			while (step < mainMoveSpeed &&!(status&UI::UP) &&
				(*blockMap)[(int)mainTopLeftY / blockSize][(int)(mainTopLeftX - 2) / blockSize] != 0 &&
				(*blockMap)[(int)mainBottomLeftY / blockSize][(int)(mainBottomLeftX - 2) / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, 1);
			}
			mainChar->setFacing(MainCharacter::LEFT);
		}
		else if (status&UI::RIGHT)
		{
			int step = 0;
		
			while (step < mainMoveSpeed && (mainTopRightX + 2)<maxX &&
				(*blockMap)[(int)mainTopRightY / blockSize][(int)(mainTopRightX + 2) / blockSize] == 0 &&
				(*blockMap)[(int)mainBottomRightY / blockSize][(int)(mainBottomRightX + 2) / blockSize]==0&&
				(*blockMap)[(int)mainMidRightY / blockSize][(int)(mainMidRightX + 2) / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(1, 0);
			}
			while (step < mainMoveSpeed &&!(status&UI::DOWN) &&
				(*blockMap)[(int)mainTopRightY / blockSize][(int)(mainTopRightX + 2) / blockSize] == 0 &&
				(*blockMap)[(int)mainBottomRightY / blockSize][(int)(mainBottomRightX + 2) / blockSize] != 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, -1);
			}
			while (step < mainMoveSpeed &&!(status&UI::UP) &&
				(*blockMap)[(int)mainTopRightY / blockSize][(int)(mainTopRightX + 2) / blockSize] != 0 &&
				(*blockMap)[(int)mainBottomRightY / blockSize][(int)(mainBottomRightX + 2) / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, 1);
			}

			mainChar->setFacing(MainCharacter::RIGHT);
		}
		if (status&UI::ZK)
		{
			mainMap->DropBomb(mainChar->getX(), mainChar->getY());
		}

	}*/
}


void MainGame::FrameDelay()
{
	const double frameRate = 60;
	static int lastTime = timeGetTime();
	static int currentTime;
	static int delayTime;
	currentTime = timeGetTime();


	delayTime = 1000 / frameRate - (currentTime - lastTime);


	if (delayTime>0)
		Sleep(delayTime);
	lastTime = currentTime;
}


void MainGame::CheckHit(MainCharacter *mainChar)
{
	blastMap = mainMap->getBlastMap();
	const int blockSize = mainMap->getBlockSize();
	const double blockScale = 2.5;
	const double scalex = 0.5;
	const double scaley = 0.5;
	const double margin = 1.0;
	double mainX, mainY;
	mainX = mainChar->getX();
	mainY = mainChar->getY();
	int mainTopMidX = mainX - margin;
	int mainTopMidY = (mainY - scaley*blockSize / 2 + margin)/blockSize;
	int mainTopLeftX = (mainX - scalex*blockSize / 2 + margin) / blockSize;
	int mainTopRightX = (mainX + scalex*blockSize / 2 - margin) / blockSize;
	int mainTopLeftY = (mainY - scaley*blockSize / 2 + margin) / blockSize;
	int mainTopRightY = (mainY - scaley*blockSize / 2 + margin) / blockSize;
	int mainBottomLeftX = (mainX - scalex*blockSize / 2 + margin) / blockSize;
	int mainBottomLeftY = (mainY + scaley*blockSize / 2 - margin) / blockSize;
	int mainBottomRightX = (mainX + scalex*blockSize / 2 - margin) / blockSize;
	int mainBottomRightY = (mainY + scaley*blockSize / 2 - margin) / blockSize;
	int mainBottomMidX = (mainX - margin) / blockSize;
	int mainBottomMidY = (mainY + scaley*blockSize / 2 - margin) / blockSize;
	int mainMidLeftX = (mainX - scalex*blockSize / 2 + margin) / blockSize;
	int mainMidLeftY = (mainY - margin) / blockSize;
	int mainMidRightX = (mainX + scalex*blockSize / 2 + margin) / blockSize;
	int mainMidRightY = (mainY - margin) / blockSize;

	if ((*(blastMap))[mainTopRightY][mainTopRightX] != 99999 ||
		(*(blastMap))[mainTopLeftY][mainTopLeftX] != 99999 ||
		(*(blastMap))[mainBottomLeftY][mainBottomLeftX] != 99999 ||
		(*(blastMap))[mainBottomRightY][mainBottomRightX] != 99999)
	{
		mainChar->Hit();
	}

}

