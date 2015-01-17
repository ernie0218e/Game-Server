#pragma once
#include <stack>
using namespace std;
class Command
{
	int command_flag;
	int newChar_id;
	int delChar_id;
	stack<int> bomb_x;
	stack<int> bomb_y;
	stack<int> hit_id;
public:
	Command(void);
	~Command(void);
	int getCmdFlag();
	int getNewCharID();
	int getDelCharID();
	stack<int>& getBombX();
	stack<int>& getBombY();
	stack<int>& getHitID();
	void setCmdFlag(int);
	void setCmdFlag(int, int);
	void setBomb(int, int);
	void setHitID(int);
	void clearNewCharID();
	void clearDelCharID();
	void clearCmdFlag();
};

