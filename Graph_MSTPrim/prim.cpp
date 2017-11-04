//@Filename:	prim.cpp
//@Description:	Prim algorithm of minimum spanning tree
//@Author:		Xu Jiale
//@Create Time:	2016/12/24, 19:36
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define INFINITY 10000

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

//array:		Lowcost[i] is the lowest cost from vertex i 
//				to the current minimum spanning tree
int *Lowcost;
//array:		Closest[i] is the nearest vertex from vertex i 
//				in the current minimum spanning tree
int *Closest;

//Function:		CreateMTGraph
//Description:	Create a new graph
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void CreateMTGraph(MTGraph *);
//Function:		Initialize
//Description:	Initialize the arrays Lowcost and Closest
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void Initialize(MTGraph *);
//Function:		Prim
//Description:	The procedure of prim algorithm
//Arguments:	MTGraph *: the pointer of a graph
//Return:		void
void Prim(MTGraph *);

int main()
{
	MTGraph *G = new MTGraph;
	CreateMTGraph(G);
	Initialize(G);
	Prim(G);
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
			G->edge[i][j] = INFINITY;
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
void Initialize(MTGraph *G)
{
	Lowcost = new int[G->vertexnum];
	Closest = new int[G->vertexnum];
}
void Prim(MTGraph *G)
{
	//weight:	the summary weight of the minimum spanning tree
	//k:		the vertex chosen currently
	//min:		the minimum cost currently(equal to Lowcost[k])
	int weight = 0;
	int k;
	int min;

	//Initiallize the arrays Lowcost and Closest with the oringin vertex
	for (int i = 0; i < G->vertexnum; i++)
	{
		Lowcost[i] = G->edge[0][i];
		Closest[i] = 0;
	}
	//Marks vertex 0 meaning that it has been added to the minimum spanning tree
	Lowcost[0] = 0;
	cout << "最小生成树中的边有：" << endl;
	//The outer loop is just a counter
	for (int i = 1; i < G->vertexnum; i++)
	{
		min = INFINITY;
		//The first inner loop, find the nearest vertex which is adjacent to 
		//the minimum spanning tree, while it's not in the tree
		for (int j = 0; j < G->vertexnum; j++)
			if (Lowcost [j] != 0 && Lowcost[j] < min)
			{
				min = Lowcost[j];
				k = j;
			}
		weight += Lowcost[k];
		//Print the edge which has just been added to the minimum spanning tree
		cout << G->vexlist[Closest[k]] << "--" << G->vexlist[k] << endl;
		//Mark the vertex which has just been added to the minimum spanning tree
		Lowcost[k] = 0;
		//Update the auxiliary arrays
		for (int j = 0; j < G->vertexnum; j++)
			if (Lowcost[j] != 0 && G->edge[k][j] < Lowcost[j])
			{
				Lowcost[j] = G->edge[k][j];
				Closest[j] = k;
			}
	}
	cout << "最小生成树的权值总和为：" << weight << endl;
}