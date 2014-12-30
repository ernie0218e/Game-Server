#pragma once
#include <windows.h>
#include "MainCharacter.h"
#include "Map.h"
#include "stdafx.h"
#include <string>
class MainGame
{
public:
	MainGame();
	MainGame(HINSTANCE hInstance);
	~MainGame();

	bool Init();
	void Update();
	void deleteChar(int);
	MainCharacter* MakeNewChar(double ,double , int );
	int getMainChar_size();
	string sGame_info;
	string newGame_info;
	//need to be public, in order to let server R/W
	Map *mainMap;
	
private:
	
	int ***blastMap;
	char ***blockMap;
	MainCharacter *mainChar;
	vector<MainCharacter*> vMainChar;
	string game_info;
	
	int newChr_count;

	void MoveMainChar(MainCharacter*);
	void FrameDelay();
	void CheckHit(MainCharacter *);
	void CheckNewChr();
	void setGame_info(MainCharacter *);
	void clearGame_info();
	void setNewGame_info(MainCharacter *);
	void clearNewGame_info(int );

	string ConvertToString(int );
	//press key info
	enum{
		UP = 0x00000001,
		DOWN = 0x00000002,
		LEFT = 0x00000004,
		RIGHT = 0x00000008,
		ZK = 0x00000010
	}; 
};

