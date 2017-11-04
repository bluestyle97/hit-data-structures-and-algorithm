//@Filename:	topsort.cpp
//@Description:	Topsort algorithm
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 18:31
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#include <queue>

using namespace std;

//Struct:		EdgeNode
//Description:	Node of an edge
//Members:		adjvex: the adjacent vertex in this edge
//				weight: the weight of this egde
//				next: the pointer of the next EdgeNode
typedef struct node
{
	int adjvex;
	int weight;
	node *next;
} EdgeNode;
//Struct:		VertexNode
//Description:	Node of a vertex
//Members:		data: the data stored in the vertex(such as A, B, C...)
//				firstedge: the pointer of the first edge node
typedef struct
{
	char data;
	EdgeNode *firstedge;
} VertexNode;
//Struct:		AdjGraph
//Description:	Define a graph represented by an adjacency list
//Members:		vexlist: the list of vertexes
//				vertexnum: the amount of vertexes
//				edgenum: the amount of edges
typedef struct
{
	VertexNode *vexlist;
	int vertexnum;
	int edgenum;
} AdjGraph;

//array:		the list of each vertex's indegree
int *indegree;
//array:		the list of each vertex's topsort number
int *topnum;

//Function:		CreateAdjGraph
//Description:	Create a new graph
//Arguments:	AdjGraph *: the pointer of a graph
//Return:		void
void CreateAdjGraph(AdjGraph *);
//Function:		TopSort
//Description:	The procedure of topsort algorithm
//Arguments:	AdjGraph *: the pointer of a graph
//Return:		void
void TopSort(AdjGraph *);

int main()
{
	AdjGraph *G = new AdjGraph;
	CreateAdjGraph(G);
	TopSort(G);
	system("pause");
	return 0;
}
void CreateAdjGraph(AdjGraph * G)
{
	int head, tail, cost;
	cout << "请输入顶点数：";
	cin >> G->vertexnum;
	cout << "请输入边数：";
	cin >> G->edgenum;
	G->vexlist = new VertexNode[G->vertexnum];
	indegree = new int[G->vertexnum];
	cout << "请输入各顶点信息：";
	for (int i = 0; i < G->vertexnum; i++)
	{
		indegree[i] = 0;
		cin >> G->vexlist[i].data;
		G->vexlist[i].firstedge = NULL;
	}
	cout << "请输入各边信息（起点 终点 权重）：" << endl;
	for (int i = 0; i < G->edgenum; i++)
	{
		cin >> head >> tail >> cost;
		EdgeNode *p = new EdgeNode;
		p->adjvex = tail;
		p->weight = cost;
		p->next = G->vexlist[head].firstedge;
		G->vexlist[head].firstedge = p;
		indegree[tail]++;
	}
}
void TopSort(AdjGraph *G)
{
	int v, count = 0;
	EdgeNode *p;
	topnum = new int[G->vertexnum];
	queue<int> Q;
	for (int i = 0; i < G->vertexnum; i++)
		if (indegree[i] == 0)
			Q.push(i);
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		topnum[v] = ++count;
		cout << G->vexlist[v].data;
		p = G->vexlist[v].firstedge;
		while (p != NULL)
		{
			if (--indegree[p->adjvex] == 0)
				Q.push(p->adjvex);
			p = p->next;
		}
	}
	if (count < G->vertexnum)
		cout << "该有向图中有环路！" << endl;
}