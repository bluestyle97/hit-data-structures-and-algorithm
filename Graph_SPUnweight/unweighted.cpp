//@Filename:	unweighted.cpp
//@Description:	Find the shortest paths from the origin to other vertexes(take directed graph for example)
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 19:55
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#include <queue>
#define INFINITY 10000
#define NOTAVERTEX -1

using namespace std;

//Struct:		EdgeNode
//Description:	Node of an edge
//Members:		adjvex: the adjacent vertex in this edge
//				next: the pointer of the next EdgeNode
typedef struct node
{
	int adjvex;
	node *next;
} EdgeNode;
//Struct:		VertexNode
//Description:	Node of a vertex
//Members:		data: the data stored in the vertex(such as A, B, C...)
//				known: mark whether the vertex is known
//				distance: the distance from this vertex to the origin
//				firstedge: the pointer of the first edge node
//				path: the previous vertex in the path
typedef struct
{
	char data;
	bool known;
	int distance;
	int path;
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

void CreateAdjGraph(AdjGraph *);
void Unweighted(AdjGraph *, int);
void PrintPath(AdjGraph *, int);

int main()
{
	int origin, destination;
	AdjGraph *G = new AdjGraph;
	CreateAdjGraph(G);
	cout << "请输入路径起点：";
	cin >> origin;
	Unweighted(G, origin);
	while (true)
	{
		cout << "请输入路径终点（输入-1退出）：";
		cin >> destination;
		if (destination == -1)
			break;
		cout << "从顶点" << G->vexlist[origin].data << "到顶点"
			<< G->vexlist[destination].data << "的最短路径长度为"
			<< G->vexlist[destination].distance << endl;
		cout << "最短路径为：";
		PrintPath(G, destination);
		cout << endl << endl;
	}
	return 0;
}

void CreateAdjGraph(AdjGraph * G)
{
	int head, tail;
	cout << "请输入顶点数：";
	cin >> G->vertexnum;
	cout << "请输入边数：";
	cin >> G->edgenum;
	G->vexlist = new VertexNode[G->vertexnum];
	cout << "请输入各顶点信息：";
	for (int i = 0; i < G->vertexnum; i++)
	{
		cin >> G->vexlist[i].data;
		G->vexlist[i].firstedge = NULL;
	}
	cout << "请输入各边信息（起点 终点）：" << endl;
	for (int i = 0; i < G->edgenum; i++)
	{
		cin >> head >> tail;
		EdgeNode *p = new EdgeNode;
		p->adjvex = tail;
		p->next = G->vexlist[head].firstedge;
		G->vexlist[head].firstedge = p;
	}
}
void Unweighted(AdjGraph *G, int i)
{
	queue<int> Q;
	int v;
	for (int j = 0; j < G->vertexnum; j++)
	{
		G->vexlist[j].known = false;
		G->vexlist[j].distance = INFINITY;
		G->vexlist[j].path = NOTAVERTEX;
	}
	G->vexlist[i].distance = 0;
	Q.push(i);
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		G->vexlist[v].known = true;
		EdgeNode *p = new EdgeNode;
		p = G->vexlist[v].firstedge;
		while (p != NULL)
		{
			if (G->vexlist[p->adjvex].distance == INFINITY)
			{
				G->vexlist[p->adjvex].distance = G->vexlist[v].distance + 1;
				G->vexlist[p->adjvex].path = v;
				Q.push(p->adjvex);
			}
			p = p->next;
		}
	}
}
void PrintPath(AdjGraph *G, int i)
{
	if (G->vexlist[i].path != NOTAVERTEX)
		PrintPath(G, G->vexlist[i].path);
	cout << G->vexlist[i].data;
}