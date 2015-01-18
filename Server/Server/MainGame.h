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
	MainCharacter* MakeNewChar(double ,double, int, string);
	int generateID();
	string getCommand(MainCharacter *);
	//need to be public, in order to let server R/W
	Map *mainMap;
	
private:
	
	int ***blastMap;
	char ***blockMap;
	MainCharacter *mainChar;
	vector<MainCharacter*> vMainChar;
	
	int newChr_count;
	bool allReady;

	void MoveMainChar(MainCharacter*);
	void FrameDelay();
	void CheckHit(MainCharacter *);
	bool CheckReady();

	string ConvertToString(int );
	//press key info
	enum{
		UP = 0x00000001,
		DOWN = 0x00000002,
		LEFT = 0x00000004,
		RIGHT = 0x00000008,
		ZK = 0x00000010,
		SPACE = 0x00000020
	};

	enum char_command_flags{
		MOVE_CHAR = 0x00000001,
		NEW_CHAR = 0x00000002,
		NEW_ALL_CHAR = 0x00000004,
		DEL_CHAR = 0x00000008,
		NEW_BOMB = 0x00000010,
		GET_HIT = 0x00000020,
		READY = 0x00000040
	};
};

