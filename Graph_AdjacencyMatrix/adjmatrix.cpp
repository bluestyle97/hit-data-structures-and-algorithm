//@Filename:	adjmatrix.cpp
//@Description:	Adjacency matrix representation of graph and its search
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 16:49
//Copyright (C) 2016 HIT. All rights reserved
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//Struct:		MTGraph
//Description:	Define a graph represented by an adjacency matrix
//Members:		vexlist: the list of vertexes
//				edge: the adjacency matrix
//				vertexnum: the amount of vertexes
//				edgenum:the amount of edges
typedef struct
{
	char *vexlist;
	int **edge;
	int vertexnum;
	int edgenum;
} MTGraph;

//array:		Judge whether the current vertex has been visited
bool * visited;

//Function:		CreateMTGraph
//Description:	Create a new graph
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void CreateMTGraph(MTGraph *);
//Funtion:		InitVisited
//Description:	Initialize the array "visited"
//Arguments:	MTGraph *; the pointer of a graph
//Return:		void
void InitVisited(MTGraph *);
//Function:		DFSGraph1
//Description:	Depth-first search of the graph(recursive)
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void DFSGraph1(MTGraph *, int);
//Function:		DFSGraph2
//Description:	Depth-first search of the graph(non-recursive)
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void DFSGraph2(MTGraph *, int);
//Function:		BFSGraph
//Description:	Breadth-first search of the graph(non-recursive)
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void BFSGraph(MTGraph *, int);

int main()
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       欢迎使用图的搜索系统！           |" << endl;
	cout << " ---------------------------------------- " << endl;
	MTGraph *G = new MTGraph;
	char choice = ' ';
	while (choice != '5')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|       请按数字键选择相应功能：           |" << endl;
		cout << "|       1.初始化图（使用其他功能前必选）   |" << endl;
		cout << "|       2.深度优先搜索（递归）             |" << endl;
		cout << "|       3.深度优先搜索（非递归）           |" << endl;
		cout << "|       4.广度优先搜索                     |" << endl;
		cout << "|       5.退出程序                         |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "        请输入您的选择：";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':
			CreateMTGraph(G);
			break;
		case '2':
			InitVisited(G);
			DFSGraph1(G, 0);
			break;
		case '3':
			InitVisited(G);
			DFSGraph2(G, 0);
			break;
		case '4':
			InitVisited(G);
			BFSGraph(G, 0);
			break;
		case '5':
			cout << " ------------------------------------------ " << endl;
			cout << "|       感谢使用图的搜索系统               |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       您的输入有误，请重新输入！         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	system("pause");
	return 0;
}
void CreateMTGraph(MTGraph *G)
{
	int i, j, w;
	cout << "请输入顶点数：";
	cin >> G->vertexnum;
	cout << "请输入边数：";
	cin >> G->edgenum;
	G->vexlist = new char[G->vertexnum];
	G->edge = new int*[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		G->edge[i] = new int[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
			G->edge[i][j] = 0;
	cout << "请输入各顶点信息：";
	for (int i = 0; i < G->vertexnum; i++)
		cin >> G->vexlist[i];
	cout << "请输入各边信息（起点 终点 权重）：" << endl;
	for (int k = 0; k < G->edgenum; k++)
	{
		cin >> i >> j >> w;
		G->edge[i][j] = w;
		G->edge[j][i] = w;
	}
}
void InitVisited(MTGraph *G)
{
	visited = new bool[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		visited[i] = false;
}
void DFSGraph1(MTGraph *G, int i)
{
	cout << G->vexlist[i];
	visited[i] = true;
	for (int j = 0; j < G->vertexnum; j++)
		if (G->edge[i][j] > 0 && !visited[j])
			DFSGraph1(G, j);
}
void DFSGraph2(MTGraph *G, int i)
{
	int k;
	stack <int> S;
	visited[i] = true;
	S.push(i);
	while (!S.empty())
	{
		k = S.top();
		S.pop();
		cout << G->vexlist[k];
		for (int j = 0; j < G->vertexnum; j++)
			if (G->edge[k][j] > 0 && !visited[j])
			{
				visited[j] = true;
				S.push(j);
			}
	}
}
void BFSGraph(MTGraph *G, int i)
{
	int k;
	queue <int> Q;
	visited[i] = true;
	Q.push(i);
	while (!Q.empty())
	{
		k = Q.front();
		Q.pop();
		cout << G->vexlist[k];
		for (int j = 0; j < G->vertexnum; j++)
			if (G->edge[k][j] > 0 && !visited[j])
			{
				visited[j] = true;
				Q.push(j);
			}
	}
}