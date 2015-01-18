#include "StdAfx.h"
#include "AI.h"
#define blocksize 45
AI::AI()
{
	me = nullptr;
}


AI::~AI(void)
{
}

void AI::MoveRight()
{
	ProxY();
	int dx = ( (arrX+1)*blocksize + 0.5*blocksize) - x;
	for (int i = 0; i < dx / moveSpeed; i++)
	{
		key.push_back(RIGHT);
	}
}

void AI::MoveLeft()
{
	ProxY();
	int dx = x - ((arrX - 1)*blocksize + 0.5*blocksize);
	for (int i = 0; i < dx / moveSpeed; i++)
	{
		key.push_back(LEFT);
	}
}

void AI::MoveUp()
{
	ProxX();
	int dy = y - ((arrY - 1)*blocksize + 0.5*blocksize);
	for (int i = 0; i < dy / moveSpeed; i++)
	{
		key.push_back(UP);
	}
}

void AI::MoveDown()
{
	ProxX();
	int dy = ((arrY + 1)*blocksize + 0.5*blocksize) - y;
	for (int i = 0; i < dy / moveSpeed; i++)
	{
		key.push_back(DOWN);
	}
}

void AI::AssignMe(MainCharacter *mch)
{
	me = mch;
}

void AI::Update()
{
	if (me != nullptr)
	{
		x = me->getX();
		y = me->getY();
		arrX = x / blocksize;
		arrY = y / blocksize;
		moveSpeed = me->getMoveSpeed();
	}
}

int AI::getKey()
{
	int retKey = 0;
	if (!key.empty())
	{
		retKey = key[0];
		key.erase(key.begin());
	}
	return retKey;
}

bool AI::empty()
{
	if (me == nullptr)
		return 1;
	return 0;
}

void AI::ProxX()
{
	int dx = x - ((arrX)*blocksize + 0.5*blocksize);
	if (dx>0)
		for (int i = 0; i < dx / moveSpeed; i++)
		{
			key.push_back(LEFT);
		}
	else 
		for (int i = 0; i < -dx / moveSpeed; i++)
		{
			key.push_back(RIGHT);
		}
}
void AI::ProxY()
{
	int dy = y - ((arrY)*blocksize + 0.5*blocksize);
	if (dy>0)
		for (int i = 0; i < dy / moveSpeed; i++)
		{
			key.push_back(UP);
		}
	else
		for (int i = 0; i < -dy / moveSpeed; i++)
		{
			key.push_back(DOWN);
		}
}

bool AI::MoveDone()
{
	return key.empty();
}

void AI::setX()
{

}

void AI::setY()
{

}

void AI::setArrX()
{

}

void AI::setArrY()
{

}

void AI::setFinalArrX()
{

}

void AI::setFinalArrY()
{

}

const vector <int> & AI::getKeyVector()
{

	return key;
}

int AI::getArrX()
{
	return arrX;
}

int AI::getArrY()
{
	return arrY;
}

node::node(int xp, int yp, int d, int p)
{
	xPos = xp; yPos = yp; level = d; priority = p;
}

int node ::getxPos() const
{
	return xPos;
}
int node::getyPos() const
{
	return yPos;
}
int node::getLevel() const
{
	return level;
}
int  node::getPriority() const
{
	return priority;
}
void node::updatePriority(const int & xDest, const int & yDest)
{
	priority = level + estimate(xDest, yDest) * 10;
}
void node::nextLevel(const int & i)
{
	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}
const int & node::estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	d = static_cast<int>(sqrt((double)(xd*xd + yd*yd)));

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return(d);
}
bool  operator<(const node & a, const node & b)
{
	return a.priority > b.priority;
}
Findroad::Findroad(int n, int m)
{
	int x, y;
	this->n = n;
	this->m = m;
	dir_map = new int*[n];
	map = new int*[n];
	closed_nodes_map = new int*[n];
	open_nodes_map = new int*[n];
	for (y = 0; y<n; y++)
	{
		dir_map[y] = new int[m];
		map[y] = new int[m];
		closed_nodes_map[y] = new int[m];
		open_nodes_map[y] = new int[m];
	}

	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}
	for (int y = 0; y<m; y++)
	{
		for (int x = 0; x<n; x++) map[x][y] = 0;
	}
	// create the start node and push into list of open nodes
	//n0=new node(xStart, yStart, 0, 0);
	// n0->updatePriority(xFinish, yFinish);
	//pq[pqi].push(*n0);
	// open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map
}
Findroad::~Findroad()
{
	int y;
	for (y = 0; y<n; y++)
	{
		delete[] dir_map[y];
		delete[] map[y];
		delete[] closed_nodes_map[y];
		delete[] open_nodes_map[y];
	}
	delete[] dir_map;
	delete[] map;
	delete[] closed_nodes_map;
	delete[] open_nodes_map;
}
int Findroad::getmap(int x, int y)
{
	return map[x][y];
}
void Findroad::setmap(char ***loadmap)
{
	int x, y;
	int i, j,r;
	
	for (int y = 0; y<m; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if ( (*loadmap)[y][x] == 0 ) 
				map[x][y] = 0;
			else
				map[x][y] = 1;
		}
				
	}
	////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	/*
	for (i = 0; i < 17; i++)
	{
		map[0][i]=1;
	}
	for (i = 0; i < 17; i++)
	{
		map[24][i]=1;
	}
	for (i = 0; i < 25; i++)
	{
		map[i][0]=1;
	}
	for (i = 0; i < 25; i++)
	{
		map[i][14]=1;
	}
	for (i = 2; i < 25; i = i + 2)
	{
		for (j = 2; j < 17; j = j + 2)
		{
			map[i][j]=1;
		}
	}
	*/
}
string Findroad::pathFind(const int  &xStart, const int  &yStart, const int  &xFinish, const int  &yFinish)
{
	static priority_queue<node> pq[2];
	static int pqi = 0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	static int dx[4] = { 1, 0, -1, 0 };
	static int dy[4] = { 0, 1, 0, -1 };

	// create the start node and push into list of open nodes
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map


	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

					// empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found


}