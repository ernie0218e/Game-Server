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
	allReady = false;
	start_game = false;
	newChr_count = 0;
}


//之後要在此新增一個Game
bool MainGame::Init()
{
	allReady = false;
	start_game = false;
	stop_game = false;
	newChr_count = 0;
	mainMap = new Map();
	mainMap->MakeMap();

	return true;
}


int MainGame::Update()
{
	FrameDelay();
	mainMap->UpdateBombTimer();
	mainMap->CheckBombExplode(vMainChar);
	mainMap->UpdateBlastTimer();
	mainMap->CheckBlastGrow();
	for(int i = 0;i < vMainChar.size();i++){
		if(vMainChar[i] != NULL){
			if(vMainChar[i]->getHp())
				CheckHit(vMainChar[i]);
		}
		if(vMainChar[i] != NULL){
			vMainChar[i]->IncreaseDamageCount();
		}
		if(vMainChar[i] != NULL){
			if(vMainChar[i]->getHp())
				MoveMainChar(vMainChar[i]);
		}
	}
	CheckNewItem();

	if(!allReady){
		if(CheckReady()){
			allReady = true;
		}
	}

	if(allReady && ! start_game){
		StartCount();
	}

	if(start_game && !stop_game){
		GameCount();
	}

	// read
	// send
	// draw
	// delay
	if(stop_game)
		return 1;
	return 0;
}

MainGame::~MainGame()
{
	
}

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
				(*blockMap)[(int)(mainTopMidY - 1) / blockSize][(int)mainTopMidX / blockSize] == 0 &&
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
				(*blockMap)[(int)(mainTopMidY - 1) / blockSize][(int)mainTopMidX / blockSize] == 0 &&
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
		if ((status&ZK) && start_game && !stop_game)
		{
			int _x, _y, _r, _id;
			_x = mainChar->getX();
			_y = mainChar->getY();
			_r = mainChar->getBombRange();
			_id= mainChar->getId();
			if(mainChar->getBombDropCount()<mainChar->getBombDropMax())
			{
				if(mainMap->DropBomb(_x, _y, _r, _id)){
					for(int i = 0;i < vMainChar.size();i++){
						if(vMainChar[i] != NULL){
							vMainChar[i]->cmd->setCmdFlag(NEW_BOMB);
							vMainChar[i]->cmd->setBomb(_x, _y, _r);
						}
					}
					mainChar->increaseBombDropCount();
				}
			}

		}
		if(status&SPACE){
			mainChar->cmd->setReady();
			for(int i = 0;i < vMainChar.size();i++){
				if(vMainChar[i] != NULL){
					vMainChar[i]->cmd->setCmdFlag(READY);
					vMainChar[i]->cmd->setReadyID(mainChar->getId());
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

	itemMap = mainMap->getItemMap();

	if ((*(itemMap))[(int)mainY/blockSize][(int)mainX/blockSize] != 0)
	{
		switch((*(itemMap))[(int)mainY/blockSize][(int)mainX/blockSize]){
		case BOMB_RANGE:
			mainMap->GetItem(mainX/blockSize, mainY/blockSize, BOMB_RANGE);
			mainChar->increaseBombDropMax();
			break;
		case BOMB_MAX_COUNT:
			mainMap->GetItem(mainX/blockSize, mainY/blockSize, BOMB_MAX_COUNT);
			mainChar->increaseBombRange();
			break;
		}

		for(int i = 0;i < vMainChar.size();i++){
			if(vMainChar[i] != NULL){
				vMainChar[i]->cmd->setCmdFlag(GET_ITEM);
			}
		}
	}

}

void MainGame::deleteChar(int d_id)
{
	newChr_count--;
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

MainCharacter* MainGame::MakeNewChar(int id, string name)
{
	newChr_count++;
	MainCharacter *mainChar;
	int graphCode = 0;
	int x, y;
	
	switch(newChr_count % 4){
		case 1:
			x = 45 + 22;
			y = 45 + 22;
			break;
		case 2:
			x = 23*45 + 22;
			y = 45 + 22;
			break;
		case 3:
			x = 23*45 + 22;
			y = 15*45 + 22;
			break;
		case 0:
			x = 45 + 22;
			y = 15*45 + 22;
			break;
	}

	mainChar = new MainCharacter(x , y, graphCode, id, name);
	//graphCode = (++graphCode)%2;
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
					"," + ConvertToString(vMainChar[i]->getY()) + "," + ConvertToString(vMainChar[i]->getGraphCode()) + 
					ConvertToString(vMainChar[i]->getFacing()) +")";
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
			while(!mainChar->cmd->getBombX().empty() && !mainChar->cmd->getBombY().empty() && !mainChar->cmd->getBombRange().empty()){
				com += "dpb" + ConvertToString(mainChar->cmd->getBombX().top()) + "," +ConvertToString(mainChar->cmd->getBombY().top())
					+ "," + ConvertToString(mainChar->cmd->getBombRange().top()) + ")";
				mainChar->cmd->getBombX().pop();
				mainChar->cmd->getBombY().pop();
				mainChar->cmd->getBombRange().pop();
			}
		}
		if(flag & GET_HIT){
			while(!mainChar->cmd->getHitID().empty()){
				com += "hit" + ConvertToString(mainChar->cmd->getHitID().top())+")";
				mainChar->cmd->getHitID().pop();
			}
		}
		if(flag & READY){
			while(!mainChar->cmd->getReadyID().empty()){
				com += "rdy" + ConvertToString(mainChar->cmd->getReadyID().top()) + ")";
				mainChar->cmd->getReadyID().pop();
			}
		}
		if(flag & ALL_READY){
			com += "ready";
		}
		if(flag & GAME_START){
			com += "start";
		}
		if(flag & GAME_STOP){
			com += "stop";
		}
		if(flag & NEW_ITEM){
			while((!mainMap->getNewItem_x().empty()) && (!mainMap->getNewItem_y().empty())&& (!mainMap->getNewItemType().empty())){
				com += "nit" + ConvertToString(mainMap->getNewItem_x().top()) + "," + ConvertToString(mainMap->getNewItem_y().top())
					+"," + ConvertToString(mainMap->getNewItemType().top()) + ")";
				mainMap->getNewItem_x().pop();
				mainMap->getNewItem_y().pop();
				mainMap->getNewItemType().pop();
			}
		}
		if(flag & GET_ITEM){
			while((!mainMap->getGetItem_x().empty()) && (!mainMap->getGetItem_y().empty())&& (!mainMap->getGetItem_type().empty())){
				com += "git" + ConvertToString(mainMap->getGetItem_x().top()) + "," + ConvertToString(mainMap->getGetItem_y().top())
					+"," + ConvertToString(mainMap->getGetItem_type().top()) + ")";
				mainMap->getGetItem_x().pop();
				mainMap->getGetItem_y().pop();
				mainMap->getGetItem_type().pop();
			}
		}
	}

	mainChar->cmd->clearCmdFlag();
	return com;
}

bool MainGame::CheckReady()
{
	int tmp = 0;

	if(vMainChar.size() == 0)
		return false;

	for(int i = 0;i < vMainChar.size();i++){
		if(vMainChar[i] != NULL){
			if(!vMainChar[i]->cmd->getReady()){
				return false;
			}
		}else{
			tmp++;
		}
	}
	
	if(vMainChar.size() == tmp){
		return false;
	}

	for(int i = 0;i < vMainChar.size();i++){
		if(vMainChar[i] != NULL){
			vMainChar[i]->cmd->setCmdFlag(ALL_READY);
		}
	}
	
	return true;
}

void MainGame::StartCount()
{
	static int sTime = timeGetTime();
	if(timeGetTime() - sTime >= 10000){
		for(int i = 0;i < vMainChar.size();i++){
			if(vMainChar[i] != NULL){
				vMainChar[i]->cmd->setCmdFlag(GAME_START);
			}
		}
		start_game = true;
	}
}

void MainGame::GameCount()
{
	static long stat_Time = timeGetTime();
	if(timeGetTime() - stat_Time >= 300000){
		for(int i = 0;i < vMainChar.size();i++){
			if(vMainChar[i] != NULL){
				vMainChar[i]->cmd->setCmdFlag(GAME_STOP);
			}
		}
		stop_game = true;
	}
}

void MainGame::CheckHitItem(MainCharacter *)
{
	itemMap = mainMap->getItemMap();
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

	if ((*(itemMap))[(int)mainY/blockSize][(int)mainX/blockSize] != 0)
	{
			switch((*(itemMap))[(int)mainY/blockSize][(int)mainX/blockSize]){
				case BOMB_RANGE:
					mainMap->GetItem(mainX/blockSize, mainY/blockSize, BOMB_RANGE);
					mainChar->increaseBombDropMax();
					break;
				case BOMB_MAX_COUNT:
					mainMap->GetItem(mainX/blockSize, mainY/blockSize, BOMB_MAX_COUNT);
					//mainChar->increaseBombRange();
					break;
			}
			
			for(int i = 0;i < vMainChar.size();i++){
				if(vMainChar[i] != NULL){
					vMainChar[i]->cmd->setCmdFlag(GET_ITEM);
				}
			}
	}
}

void MainGame::CheckNewItem()
{
	if((!mainMap->getNewItem_x().empty()) && (!mainMap->getNewItem_y().empty()) && (!mainMap->getNewItemType().empty())){
		for(int i = 0;i < vMainChar.size();i++){
			if(vMainChar[i] != NULL){
				vMainChar[i]->cmd->setCmdFlag(NEW_ITEM);
			}
		}
	}
}
