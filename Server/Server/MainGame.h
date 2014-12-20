#pragma once
#include <windows.h>
#include "MainCharacter.h"
#include "Map.h"
#include "stdafx.h"
class MainGame
{
public:
	MainGame();
	MainGame(HINSTANCE hInstance);
	~MainGame();

	bool Init();
	void Update();
	//need to be public, in order to let server R/W
	Map *mainMap;
	MainCharacter *mainChar;

private:

	int ***blastMap;
	char ***blockMap;
	void MoveMainChar(MainCharacter *mainChar);
	void FrameDelay();
	void CheckHit(MainCharacter *mainChar);

	//press key info
	enum{
		UP = 0x00000001,
		DOWN = 0x00000002,
		LEFT = 0x00000004,
		RIGHT = 0x00000008,
		ZK = 0x00000010
	}; 
};

