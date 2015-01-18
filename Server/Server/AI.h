#include "MainCharacter.h"
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <iostream>
#pragma once
using namespace std;
class AI
{
	int x;
	int y;
	int finalX;
	int finalY;
	int arrX;
	int arrY;
	int finalArrX;
	int finalArrY;
	int moveSpeed;
	vector <int> key;
	vector <int> command;
	MainCharacter *me;
	enum{
		UP = 0x00000001,
		DOWN = 0x00000002,
		LEFT = 0x00000004,
		RIGHT = 0x00000008,
		ZK = 0x00000010,
		SPACE = 0x00000020
	};

public:
	AI();
	void AssignMe(MainCharacter *);
	void Update();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void setX();
	void setY();
	void setArrX();
	void setArrY();
	int getArrX();
	int getArrY();
	void setFinalArrX();
	void setFinalArrY();
	void ProxX();
	void ProxY();
	int getKey();
	bool empty();
	bool MoveDone();
	const vector <int> & getKeyVector();
	~AI();
};

const int dir = 4;

class node
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority
public:
	node(int xp, int yp, int d, int p);
	int getxPos() const;
	int getyPos() const;
	int getLevel() const;
	int getPriority() const;

	void updatePriority(const int & xDest, const int & yDest);

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i);// i: direction

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;

	friend bool  operator<(const node & a, const node & b);
};

class Findroad
{
private:
	// list of open (not-yet-tried) nodes
	// pq index
	node* n0;
	node* m0;

	int **dir_map;
	int **map;
	int **closed_nodes_map; // map of closed (tried-out) nodes
	int **open_nodes_map; // map of open (not-yet-tried) nodes
	int n;
	int m;
public:
	Findroad(int, int);
	~Findroad();
	void	setmap(char ***loadmap);

	string pathFind(const int  &xStart, const int  &yStart, const int  &xFinish, const int  &yFinish);
	int getmap(int x,int y);
};