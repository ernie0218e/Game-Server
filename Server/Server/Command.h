#pragma once
#include <stack>
using namespace std;
class Command
{
	int command_flag;
	int newChar_id;
	int delChar_id;
	int ready;
	stack<int> bomb_x;
	stack<int> bomb_y;
	stack<int> bomb_range;
	stack<int> hit_id;
	stack<int> ready_id;
	stack<int> win_id;
public:
	Command(void);
	~Command(void);
	int getCmdFlag();
	int getNewCharID();
	int getDelCharID();
	int getReady();
	stack<int>& getBombX();
	stack<int>& getBombY();
	stack<int>& getHitID();
	stack<int>& getReadyID();
	stack<int>& getBombRange();
	stack<int>& getWinID();
	void setCmdFlag(int);
	void setCmdFlag(int, int);
	void setBomb(int, int, int);
	void setHitID(int);
	void setReadyID(int);
	void setWinID(int);
	void setReady();
	void clearNewCharID();
	void clearDelCharID();
	void clearCmdFlag();
};

