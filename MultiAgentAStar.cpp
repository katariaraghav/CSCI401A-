#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <functional>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

/* A-star heuristic:
h(x, y) = |x_goal - x| + |y_goal - y|
*/

/* input format:
[#rows] [#cols]
Description of intersection, . indicates unoccupied, O indicates obstacle
[time] [k = # agents entering at this time] - repeat continuously
[start row] [start col] [goal row] [goal col] - repeat k times

*/

const int MAXTIME = 500;
int N, M; // #rows, #cols
// [4] dimension is directonal, 0 = above, 1 = right, 2 = below, 3 = left
vector<vector<char> > board[MAXTIME][4];
int currTime = 0;
bool canMoveTo(int row, int col, int time, int movDir)
{
	return board[time][(movDir+2)%4][row][col] != '.';
}
struct TimePoint {
	int row, col, time;
	TimePoint(int nrow, int ncol, int ntime)
	{
		row = nrow, col = ncol, time = ntime;
	}
	bool operator<(const TimePoint& a) const
	{
		if (this->time < a.time) return true;
		else if (this->time == a.time)
		{
			if (this->row < a.row) return true;
			else if (this->row == a.row)
			{
				return this->col < a.col;
			}
			else return false;
		}
		else return false;
	}
	TimePoint()
	{
		row = -1;
		col = -1;
		time = -1;
	}
};
typedef pair<int, TimePoint> PQElem;
void readBoard()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		vector<char> row(M);
		for (int j = 0; j < M; j++)
		{
			cin >> row[j];
		}
		for (int j = 0; j <= MAXTIME; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				board[j][k].push_back(row);
			}			
		}
	}
}

int moveType(int rowA, int colA, int rowB, int colB) //moving from a to b
{
	if (rowA == rowB && colA==colB) return -1;
	if (colB > colA)
	{
		return 2;
	}
	else if (colB < colA)
	{
		return 0;
	}
	else if (rowB > rowA) return 1;
	else return 3;
}

int h(int currRow, int currCol, int goalRow, int goalCol)
{
	return abs(goalRow - currRow) + abs(goalCol - currCol);
}

vector<TimePoint> getSuccessors(TimePoint curr)
{
	vector<TimePoint> result;
	if (curr.row>0 && board[curr.time + 1][2][curr.row-1][curr.col] == '.')
	{
		TimePoint above(curr.row - 1, curr.col, curr.time + 1);
		result.push_back(above);
	}
	if (curr.col<M-1 && board[curr.time + 1][3][curr.row][curr.col+1] == '.')
	{
		TimePoint right(curr.row, curr.col+1, curr.time + 1);
		result.push_back(right);
	}
	if (curr.row < N - 1 && board[curr.time + 1][0][curr.row+1][curr.col] == '.')
	{
		TimePoint below(curr.row + 1, curr.col, curr.time + 1);
		result.push_back(below);
	}
	if (curr.col > 0 && board[curr.time + 1][1][curr.row][curr.col-1] == '.')
	{
		TimePoint left(curr.row, curr.col-1, curr.time + 1);
		result.push_back(left);
	}
	if (board[curr.time + 1][0][curr.row][curr.col] == '.')
	{
		TimePoint stay(curr.row, curr.col, curr.time + 1);
		result.push_back(stay);
	}
	return result;
}

vector<TimePoint> reconstructPath(map<TimePoint, TimePoint> cameFrom, TimePoint end, TimePoint start)
{
	vector<TimePoint> path;
	path.push_back(end);
	TimePoint curr = end;
	while (curr.col!=start.col || curr.row!=start.row || curr.time != start.time)
	{
		curr = cameFrom[curr];
		path.push_back(curr);
	}
	reverse(path.begin(), path.end());
	return path;
}

vector<TimePoint> AStar(int startTime, int startRow, int startCol, int goalRow, int goalCol)
{
	priority_queue< PQElem, vector<PQElem >, greater<PQElem> > pq;
	set<PQElem> pqSet;
	map<TimePoint, TimePoint> cameFrom;
	TimePoint start(startRow, startCol, startTime);
	set<TimePoint> closedSet;
	pq.push(make_pair(h(startRow, startCol, goalRow, goalCol), start));
	pqSet.insert(make_pair(h(startRow, startCol, goalRow, goalCol), start));
	while (!pq.empty())
	{
		PQElem curr = pq.top();
		if (curr.second.col == goalCol && curr.second.row == goalRow)
		{
			return reconstructPath(cameFrom, curr.second, start);
		}
		pq.pop();
		closedSet.insert(curr.second);
		vector<TimePoint> successors = getSuccessors(curr.second);
		for (int i = 0; i < successors.size(); i++)
		{
			if (closedSet.find(successors[i]) != closedSet.end())
			{
				continue;
			}
			int fScore = successors[i].time - startTime + h(successors[i].row, successors[i].col, goalRow, goalCol);
			if (pqSet.find(make_pair(fScore, successors[i])) != pqSet.end())
			{
				continue;
			}
			pq.push(make_pair(fScore, successors[i]));
			pqSet.insert(make_pair(fScore, successors[i]));
			cameFrom[successors[i]] = curr.second;

		}
	}
	//FAILURE
	vector<TimePoint> dummy;
	return dummy;
}

void solveAgents()
{
	int time, numAgents;
	while (cin >> time >> numAgents)
	{
		for (int i = 0; i < numAgents; i++)
		{
			int startRow, startCol, goalRow, goalCol;
			cin >> startRow >> startCol >> goalRow >> goalCol;
			vector<TimePoint> path = AStar(time, startRow, startCol, goalRow, goalCol);
			//update board
			if (path.empty())
			{
				//ERROR
				cout << "DEADLOCK" << endl;
				return;
			}
			for (int j = 0; j < path.size(); j++)
			{
				for (int k = 0; k < 4; k++)
				{
					board[path[j].time][k][path[j].row][path[j].col] = 'A';
				}
			}
			for (int j = 1; j < path.size(); j++)
			{
				int blockDir = moveType(path[j-1].row, path[j-1].col, path[j].row, path[j].col);
				if (blockDir != -1)
				{
					board[path[j].time][blockDir][path[j - 1].row][path[j - 1].col] = 'A';
				}
			}
		}
		
	}
	return;
}

void printBoard()
{
	for (int t = 0; t < 30; t++)
	{
		cout << "TIME: " << t << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (board[t][0][i][j] == 'A'&&board[t][1][i][j] == 'A'&&board[t][2][i][j] == 'A'&&board[t][3][i][j] == 'A')
				{
					cout << 'A';
				}
				else if (board[t][0][i][j] == '0')
				{
					cout << '0';
				}
				else cout << '.';
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}
int main()
{
	readBoard();
	solveAgents();
	printBoard();
    return 0;
}
