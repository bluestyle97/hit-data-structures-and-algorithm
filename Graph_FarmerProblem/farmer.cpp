//@Filename:	farmer.cpp
//@Description:	Farmer cross river problem
//@Author:		Xu Jiale
//@Create Time:	2016/12/26, 19:10

#include <iostream>
#include <queue>
#include <stack>
#define STATENUM		16
#define FINISHED		15

#define	FARMER_BIT		8
#define WOLF_BIT		4
#define COAT_BIT		2
#define CABBAGE_BIT		1

using namespace std;

int path[STATENUM];
bool visited[STATENUM];
bool matrix[STATENUM][STATENUM] = { false };

void InitializeMatrix(void);
bool JudgeSafeState(int);
void BFSearchPath(void);
void DFSearchPath(void);
void PrintResult(int);
void DescribeState(int);

int main()
{
	InitializeMatrix();
	cout << "-----------------------------------------------------------------" << endl;
	BFSearchPath();
	PrintResult(FINISHED);
	cout << "-----------------------------------------------------------------" << endl;
	DFSearchPath();
	PrintResult(FINISHED);
	cout << "-----------------------------------------------------------------" << endl;
	system("pause");
	return 0;
}

void InitializeMatrix()
{
	for (int i = 0; i < 8; i++)
	{
		if (JudgeSafeState(i))
		{
			int state = i | FARMER_BIT;
			matrix[i][state] = matrix[state][i] = true;
			if (JudgeSafeState(state | WOLF_BIT))
				matrix[i][state | WOLF_BIT] = matrix[state | WOLF_BIT][i] = true;
			if (JudgeSafeState(state | COAT_BIT))
				matrix[i][state | COAT_BIT] = matrix[state | COAT_BIT][i] = true;
			if (JudgeSafeState(state | CABBAGE_BIT))
				matrix[i][state | CABBAGE_BIT] = matrix[state | CABBAGE_BIT][i] = true;
		}
	}
}
bool JudgeSafeState(int state)
{
	if (state == 3 || (15 - state) == 3)
		return false;
	if (state == 6 || (15 - state) == 6)
		return false;
	if (state == 7 || (15 - state) == 7)
		return false;
	return true;
}
void BFSearchPath()
{
	bool finish = false;
	queue<int> Queue;
	for (int i = 0; i < STATENUM; i++)
	{
		path[i] = -1;
		visited[i] = false;
	}
	visited[0] = true;
	Queue.push(0);
	while (!Queue.empty() && !finish)
	{
		int state = Queue.front();
		Queue.pop();
		for (int i = 0; i < STATENUM; i++)
			if (!visited[i] && matrix[state][i])
			{
				visited[i] = true;
				path[i] = state;
				Queue.push(i);
				if (i == FINISHED)
					finish = true;
			}
	}
}
void DFSearchPath()
{
	bool finish = false;
	stack<int> Stack;
	for (int i = 0; i < STATENUM; i++)
	{
		path[i] = -1;
		visited[i] = false;
	}
	visited[0] = true;
	Stack.push(0);
	while (!Stack.empty() && !finish)
	{
		int state = Stack.top();
		Stack.pop();
		for (int i = 0; i < STATENUM; i++)
			if (!visited[i] && matrix[state][i])
			{
				visited[i] = true;
				path[i] = state;
				Stack.push(i);
				if (i == FINISHED)
					finish = true;
			}
	}
}
void PrintResult(int state)
{
	if (state != -1)
	{
		PrintResult(path[state]);
		DescribeState(state);
	}
}
void DescribeState(int state)
{
	if (state == 0)	      cout << "farmer wolf coat cabbage *****river*****" << endl;
	else if (state == 1)  cout << "        farmer wolf coat *****river***** cabbage" << endl;
	else if (state == 2)  cout << "     farmer wolf cabbage *****river***** coat" << endl;
	else if (state == 3)  cout << "             farmer wolf *****river***** coat cabbage" << endl;
	else if (state == 4)  cout << "     farmer coat cabbage *****river***** wolf" << endl;
	else if (state == 5)  cout << "             farmer coat *****river***** wolf cabbage" << endl;
	else if (state == 6)  cout << "          farmer cabbage *****river***** wolf coat" << endl;
	else if (state == 7)  cout << "                  farmer *****river***** wolf coat cabbage" << endl;
	else if (state == 8)  cout << "       wolf coat cabbage *****river***** farmer" << endl;
	else if (state == 9)  cout << "               wolf coat *****river***** farmer cabbage" << endl;
	else if (state == 10) cout << "            wolf cabbage *****river***** farmer coat" << endl;
	else if (state == 11) cout << "                    wolf *****river***** farmer coat cabbage" << endl;
	else if (state == 12) cout << "            coat cabbage *****river***** farmer wolf" << endl;
	else if (state == 13) cout << "                    coat *****river***** farmer wolf cabbage" << endl;
	else if (state == 14) cout << "                 cabbage *****river***** farmer wolf coat" << endl;
	else                  cout << "                         *****river***** farmer wolf coat cabbage" << endl;
}