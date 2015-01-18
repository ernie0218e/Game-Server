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
	int Update();
	void deleteChar(int);
	MainCharacter* MakeNewChar(int, string);
	int generateID();
	string getCommand(MainCharacter *);
	void setPlayerNumber(int);
	//need to be public, in order to let server R/W
	Map *mainMap;
	
private:
	
	int ***blastMap;
	int ***itemMap;
	char ***blockMap;
	MainCharacter *mainChar;
	vector<MainCharacter*> vMainChar;
	stack <int> win_id;

	int newChr_count;
	int player_number;
	bool allReady;
	bool start_game;
	bool stop_game;

	void MoveMainChar(MainCharacter*);
	void FrameDelay();
	void CheckHit(MainCharacter *);
	void CheckHitItem(MainCharacter *);
	void CheckNewItem();
	void CheckFinalWin();
	bool CheckWin();
	bool CheckReady();
	void StartCount();
	void GameCount();

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
		READY = 0x00000040,
		GAME_START = 0x00000080,
		GAME_STOP = 0x00000100,
		ALL_READY = 0x00000200,
		GET_ITEM = 0x00000400,
		NEW_ITEM = 0x00000800,
		WIN = 0x00001000,
		DUCE = 0x00002000
	};
	
	enum item_effect{
		BOMB_RANGE = 2,
		BOMB_MAX_COUNT = 3
	};
};

