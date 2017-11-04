//@Filename:	criticalpath.cpp
//@Description:	Find the critical path in an AOE graph
//@Author:		Xu Jiale
//@Create Time:	2016/12/24, 14:19
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#include <queue>
#define NOEDGE -1

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

//array:		the indegrees of vertexes
int *Indegree;
//array:		the outdegrees of vertexes
int *Outdegree;
//array:		the earliest beginning time of each vertex
int *VertexEarlyTime;
//array:		the latest beginning time of each vertex
int *VertexLateTime;
//matrix:		the time of an activity represented by an edge
int **ActivityTime;

//Function:		CreateMTGraph
//Description:	Create a new graph
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void CreateMTGraph(MTGraph *);
//Function:		Initialize
//Description:	Initialize global arrays and matrixes
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void Initialize(MTGraph *);
//Function:		Free
//Description:	Free the space of global arrays and matrixes
//Arguments:	void
//Return:		void
void Free(void);
//Function:		CriticalPath
//Description:	The procedure of this algorithm
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void CriticalPath(MTGraph *);
//Function:		Foward
//Description:	Invoked by CriticalPath
//				The first-time topsort that calculates the earliest time of each vertex
//Arguments;	MTGraph *: the pointer of a graph
//Return:		void
void Forward(MTGraph *);
//Function:		Backward
//Description:	Invoked by CriticalPath
//				The second-time topsort that calculates the latest time of each vertex
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void Backward(MTGraph *);
//Function:		ModifyACT
//Description:	Invoked by CriticalPath
//				Modify the matrix ActivityTime
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void ModifyACT(MTGraph *);
//Function:		PrintPath
//Description:	Print the edges in the critical path
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void PrintPath(MTGraph *);

int main()
{
	MTGraph *G = new MTGraph;
	CreateMTGraph(G);
	Initialize(G);
	CriticalPath(G);
	PrintPath(G);
	Free();
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
	Indegree = new int[G->vertexnum];
	Outdegree = new int[G->vertexnum];
	G->vexlist = new char[G->vertexnum];
	G->edge = new int*[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
	{
		G->edge[i] = new int[G->vertexnum];
		Indegree[i] = 0;
		Outdegree[i] = 0;
	}
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
			G->edge[i][j] = NOEDGE;
	cout << "请输入各顶点名称：";
	for (int i = 0; i < G->vertexnum; i++)
		cin >> G->vexlist[i];
	cout << "请输入各活动信息（起点 终点 时长）：" << endl;
	for (int k = 0; k < G->edgenum; k++)
	{
		cin >> i >> j >> w;
		G->edge[i][j] = w;
		++Indegree[j];
		++Outdegree[i];
	}
}
void Initialize(MTGraph *G)
{
	VertexEarlyTime = new int[G->vertexnum];
	VertexLateTime = new int[G->vertexnum];
	ActivityTime = new int*[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		ActivityTime[i] = new int[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
			ActivityTime[i][j] = G->edge[i][j];
}
void Free(void)
{
	delete[] Indegree;
	delete[] VertexEarlyTime;
	delete[] VertexLateTime;
	delete[] ActivityTime;
}
void CriticalPath(MTGraph *G)
{
	Forward(G);
	Backward(G);
	ModifyACT(G);
}
void Forward(MTGraph *G)
{
	int v;
	queue<int> Q;
	for (int i = 0; i < G->vertexnum; i++)
		if (Indegree[i] == 0)
			Q.push(i);
	for (int i = 0; i < G->vertexnum; i++)
		VertexEarlyTime[i] = 0;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		for (int i = 0; i < G->vertexnum; i++)
			if (G->edge[i][v] != NOEDGE && VertexEarlyTime[v] < VertexEarlyTime[i] + ActivityTime[i][v])
				VertexEarlyTime[v] = VertexEarlyTime[i] + ActivityTime[i][v];
		for (int j = 0; j < G->vertexnum; j++)
			if (G->edge[v][j] != NOEDGE && --Indegree[j] == 0)
				Q.push(j);
	}
}
void Backward(MTGraph *G)
{
	int v;
	queue<int> Q;
	for (int i = 0; i < G->vertexnum; i++)
		if (Outdegree[i] == 0)
		{
			Q.push(i);
			cout << "关键路径的长度为：" << VertexEarlyTime[i] << endl;
		}
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		VertexLateTime[v] = VertexEarlyTime[v];
		for (int i = 0; i < G->vertexnum; i++)
			if (G->edge[v][i] != NOEDGE && VertexLateTime[v] < VertexLateTime[i] - ActivityTime[v][i])
				VertexLateTime[v] = VertexLateTime[i] - ActivityTime[v][i];
		for (int j = 0; j < G->vertexnum; j++)
			if (G->edge[j][v] != NOEDGE && --Outdegree[j] == 0)
				Q.push(j);
	}
}
void ModifyACT(MTGraph *G)
{
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
			if (ActivityTime[i][j] >= 0)
				ActivityTime[i][j] = VertexLateTime[j] - ActivityTime[i][j] - VertexEarlyTime[i];
}
void PrintPath(MTGraph *G)
{
	cout << "关键路径上的边有：" << endl;
	for (int i = 0; i < G->vertexnum; i++)
		for (int j = 0; j < G->vertexnum; j++)
			if (ActivityTime[i][j] == 0)
				cout << G->vexlist[i] << "--" << G->vexlist[j] << endl;
}