//@Filename:	floyd.cpp
//@Description:	Use floyd algorithm to find the shortest path(take directed graph for example)
//@Author:		Xu Jiale
//@Create Time:	2016/12/23, 19:36
//Copyroght (C) 2016 HIT. All rights reserved

#include <iostream>
#define INFINITY 10000
#define NOTAVERTEX -1

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

//matrix: Store the distance of every pair of vertexes in the graph
int **Distance;
//matrix: Store the last vertex of the path from vertex i to vertex j
int **Path;

//Function:		CreateMTGraph
//Description:	Create a new graph
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void CreateMTGraph(MTGraph *);
//Function:		InitMatrix
//Description:	Initialize the matrixes Distance and Path
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void InitMatrix(MTGraph *);
//Function:		Floyd
//Description:	The procedure of floyd algorithm
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void Floyd(MTGraph *);
//Function:		PrintPath
//Description:	Print the path from one vertex to another
//Arguments:	MTGraph *: the pointer of a graph
//				int: the original vertex
//				int: the terminal vertex
//Return:		void
void PrintPath(MTGraph *, int, int);

int main()
{
	int origin, destination;
	MTGraph *G = new MTGraph;
	CreateMTGraph(G);
	InitMatrix(G);
	Floyd(G);
	while (true)
	{
		cout << "请输入路径起点：";
		cin >> origin;
		if (origin == -1)
			break;
		cout << "请输入路径终点：";
		cin >> destination;
		if (destination == -1)
			break;
		if (Distance[origin][destination] < INFINITY)
		{
			cout << "从顶点" << G->vexlist[origin] << "到顶点"
				<< G->vexlist[destination] << "的最短路径长度为"
				<< Distance[origin][destination] << endl;
			cout << "最短路径为：";
			cout << G->vexlist[origin];
			PrintPath(G, origin, destination);
			cout << G->vexlist[destination];
		}
		else
			cout << "从顶点" << G->vexlist[origin] << "到顶点"
			<< G->vexlist[destination] << "无路径！";
		cout << endl << endl;
	}
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
			if (i == j)
				G->edge[i][j] = 0;
			else
				G->edge[i][j] = INFINITY;
	cout << "请输入各顶点信息：";
	for (int i = 0; i < G->vertexnum; i++)
		cin >> G->vexlist[i];
	cout << "请输入各边信息（起点 终点 权重）：" << endl;
	for (int k = 0; k < G->edgenum; k++)
	{
		cin >> i >> j >> w;
		G->edge[i][j] = w;
	}
}
void InitMatrix(MTGraph *G)
{
	Distance = new int*[G->vertexnum];
	Path = new int*[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
	{
		Distance[i] = new int[G->vertexnum];
		Path[i] = new int[G->vertexnum];
	}
}
void Floyd(MTGraph *G)
{
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
		{
			Distance[i][j] = G->edge[i][j];
			Path[i][j] = NOTAVERTEX;
		}
	for (int k = 0; k < G->vertexnum; k++)
		for (int i = 0; i < G->vertexnum; i++)
			for (int j = 0; j < G->vertexnum; j++)
				if (Distance[i][k] + Distance[k][j] < Distance[i][j])
				{
					Distance[i][j] = Distance[i][k] + Distance[k][j];
					Path[i][j] = k;
				}
}
void PrintPath(MTGraph *G, int i, int j)
{
	int k = Path[i][j];
	if (k != NOTAVERTEX)
	{
		PrintPath(G, i, k);
		cout << G->vexlist[k];
		PrintPath(G, k, j);
	}
}