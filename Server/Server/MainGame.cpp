#include "MainGame.h"
#include <windows.h>
#include <Mmsystem.h>
#include <memory>
#include <vector>
#include <string>
#include "stdafx.h"
#pragma comment(lib, "Winmm.lib")


MainGame::MainGame()
{

}


//之後要在此新增一個Game
bool MainGame::Init()
{
	newChr_count = 0;
	mainMap = new Map();
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
	for(int i = 0;i < vMainChar.size();i++){
		if(vMainChar[i] != NULL){
			CheckHit(vMainChar[i]);
		}
		if(vMainChar[i] != NULL){
			vMainChar[i]->IncreaseDamageCount();
		}
		if(vMainChar[i] != NULL){
			MoveMainChar(vMainChar[i]);
		}
	}
	
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
	
	int status = mainChar->getStatus();

	mainChar->cmd->setCmdFlag(MOVE_CHAR);
	if (status != 0)
	{
		
		if (status&UP)
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
			while (step < mainMoveSpeed &&!(status&RIGHT) &&
				(*blockMap)[(int)(mainTopLeftY - 1) / blockSize][(int)mainTopLeftX / blockSize] == 0 &&
				(*blockMap)[(int)(mainTopRightY - 1) / blockSize][(int)mainTopRightX / blockSize] !=0)
			{
				step++;
				mainChar->MoveWithDisplacement(-1, 0);
			}
			while (step < mainMoveSpeed &&!(status&LEFT) &&
				(*blockMap)[(int)(mainTopLeftY - 1) / blockSize][(int)mainTopLeftX / blockSize] != 0 &&
				(*blockMap)[(int)(mainTopRightY - 1) / blockSize][(int)mainTopRightX / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(1, 0);
			}
			mainChar->setFacing(MainCharacter::UP);
			
		}
		else if (status&DOWN)
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
			while (step < mainMoveSpeed &&!(status&RIGHT)&&
				(*blockMap)[(int)(mainBottomLeftY + 2) / blockSize][(int)mainBottomLeftX / blockSize] == 0 &&
				(*blockMap)[(int)(mainBottomRightY + 2) / blockSize][(int)mainBottomRightX / blockSize] != 0)
			{
				step++;
				mainChar->MoveWithDisplacement(-1, 0);
			}
			while (step < mainMoveSpeed &&!(status&LEFT) &&
				(*blockMap)[(int)(mainBottomLeftY + 2) / blockSize][(int)mainBottomLeftX / blockSize] != 0 &&
				(*blockMap)[(int)(mainBottomRightY + 2) / blockSize][(int)mainBottomRightX / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(1, 0);
			}
			mainChar->setFacing(MainCharacter::DOWN);
		}

		else if (status&LEFT)
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
			while (step < mainMoveSpeed &&!(status&DOWN) &&
				(*blockMap)[(int)mainTopLeftY / blockSize][(int)(mainTopLeftX - 2) / blockSize] == 0 &&
				(*blockMap)[(int)mainBottomLeftY / blockSize][(int)(mainBottomLeftX - 2) / blockSize] != 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, -1);
			}
			while (step < mainMoveSpeed &&!(status&UP) &&
				(*blockMap)[(int)mainTopLeftY / blockSize][(int)(mainTopLeftX - 2) / blockSize] != 0 &&
				(*blockMap)[(int)mainBottomLeftY / blockSize][(int)(mainBottomLeftX - 2) / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, 1);
			}
			mainChar->setFacing(MainCharacter::LEFT);
		}
		else if (status&RIGHT)
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
			while (step < mainMoveSpeed &&!(status&DOWN) &&
				(*blockMap)[(int)mainTopRightY / blockSize][(int)(mainTopRightX + 2) / blockSize] == 0 &&
				(*blockMap)[(int)mainBottomRightY / blockSize][(int)(mainBottomRightX + 2) / blockSize] != 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, -1);
			}
			while (step < mainMoveSpeed &&!(status&UP) &&
				(*blockMap)[(int)mainTopRightY / blockSize][(int)(mainTopRightX + 2) / blockSize] != 0 &&
				(*blockMap)[(int)mainBottomRightY / blockSize][(int)(mainBottomRightX + 2) / blockSize] == 0)
			{
				step++;
				mainChar->MoveWithDisplacement(0, 1);
			}

			mainChar->setFacing(MainCharacter::RIGHT);
		}
		if (status&ZK)
		{
			int _x, _y;
			_x = mainChar->getX();
			_y = mainChar->getY();
			if(mainMap->DropBomb(_x, _y)){
				for(int i = 0;i < vMainChar.size();i++){
					if(vMainChar[i] != NULL){
						vMainChar[i]->cmd->setCmdFlag(NEW_BOMB);
						vMainChar[i]->cmd->setBomb(_x, _y);
					}
				}
			}
		}

	}
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
		if(mainChar->Hit()){
			for(int i = 0;i < vMainChar.size();i++){
				if(vMainChar[i] != NULL){
					vMainChar[i]->cmd->setCmdFlag(GET_HIT);
					vMainChar[i]->cmd->setHitID(mainChar->getId());
				}
			}
		}
	}

}

void MainGame::deleteChar(int d_id)
{
	for(int i = 0;i < vMainChar.size();i++){
		if(vMainChar[i] != NULL){
			if(vMainChar[i]->getId() == d_id){
				delete vMainChar[i];
				vMainChar[i] = NULL;
			}else{
				vMainChar[i]->cmd->setCmdFlag(DEL_CHAR, d_id);
			}
		}
	}
}

MainCharacter* MainGame::MakeNewChar(double x,double y, int id, string name)
{
	MainCharacter *mainChar;
	mainChar = new MainCharacter(x , y, 0, id, name);
	vMainChar.push_back(mainChar);
	
	mainChar->cmd->setCmdFlag(NEW_ALL_CHAR);
	for(int i = 0;i < vMainChar.size();i++){
		if(vMainChar[i] != NULL){
			if(vMainChar[i] != mainChar)
				vMainChar[i]->cmd->setCmdFlag(NEW_CHAR, mainChar->getId());
		}
	}

	return mainChar;
}

int MainGame::generateID()
{
	return vMainChar.size()+1;
}


std::string MainGame::ConvertToString(int t) {
	char buff[2048];
	sprintf(buff,"%d",t);
	string data = buff;
	return data;
}


string MainGame::getCommand(MainCharacter *mainChar){
	string com = "";
	int i, flag;
	flag = mainChar->cmd->getCmdFlag();
	if(flag != 0){
		if(flag & MOVE_CHAR){
			for(i = 0;i < vMainChar.size();i++){
				if(vMainChar[i] != NULL){
					com += "mch" + ConvertToString(vMainChar[i]->getId()) + "," + ConvertToString(vMainChar[i]->getX())+
					"," + ConvertToString(vMainChar[i]->getY()) + "," + ConvertToString(vMainChar[i]->getGraphCode()) + ")";
				}
			}
		}
		if(flag & NEW_CHAR){
			for(i = 0;i < vMainChar.size();i++){
				if(vMainChar[i] != NULL){
					if(vMainChar[i]->getId() == mainChar->cmd->getNewCharID()){
						com += "nch" + ConvertToString(vMainChar[i]->getId()) + "," + ConvertToString(vMainChar[i]->getX())+
						"," + ConvertToString(vMainChar[i]->getY()) + "," + ConvertToString(vMainChar[i]->getGraphCode()) + ","
						+ vMainChar[i]->getCharName() + ")";
						mainChar->cmd->clearNewCharID();
						break;
					}
				}
			}
		}
		if(flag & NEW_ALL_CHAR){
			for(i = 0;i < vMainChar.size();i++){
				if(vMainChar[i] != NULL){
					com += "nch" + ConvertToString(vMainChar[i]->getId()) + "," + ConvertToString(vMainChar[i]->getX())+
					"," + ConvertToString(vMainChar[i]->getY()) + "," + ConvertToString(vMainChar[i]->getGraphCode()) + "," +
					vMainChar[i]->getCharName() + ")";
				}
			}
		}
		if(flag & DEL_CHAR){
			com += "del" + ConvertToString(mainChar->cmd->getDelCharID())+ ")";
			mainChar->cmd->clearDelCharID();
		}
		if(flag & NEW_BOMB){
			while(!mainChar->cmd->getBombX().empty() && !mainChar->cmd->getBombY().empty()){
				com += "dpb" + ConvertToString(mainChar->cmd->getBombX().top()) + "," +ConvertToString(mainChar->cmd->getBombY().top())+")";
				mainChar->cmd->getBombX().pop();
				mainChar->cmd->getBombY().pop();
			}
		}
		if(flag & GET_HIT){
			while(!mainChar->cmd->getHitID().empty()){
				com += "hit" + ConvertToString(mainChar->cmd->getHitID().top())+")";
				mainChar->cmd->getHitID().pop();
			}
		}
	}

	mainChar->cmd->clearCmdFlag();
	return com;
}