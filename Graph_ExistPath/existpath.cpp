//@Filename:	existpath.cpp
//@Description:	Judge whether there's a path between two vertexes
//@Author:		Xu Jiale
//@Create Time:	2017/01/03, 10:22
//Copyright (C) 2017 HIT. All rights reserved

#include <iostream>

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

//array:		Judge whether the current vertex has been visited
bool *visited;

void CreateAdjGraph(AdjGraph *);
bool ExistPath(AdjGraph *, int, int);

int main()
{
	AdjGraph *G = new AdjGraph;
	CreateAdjGraph(G);
	visited = new bool[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		visited[i] = false;
	int bgn, end;
	cout << "请输入您想查找的两个顶点：";
	cin >> bgn >> end;
	bool result = ExistPath(G, bgn, end);
	if (result)
		cout << "存在从顶点" << G->vexlist[bgn].data << "到顶点" << G->vexlist[end].data << "的路径！" << endl;
	else
		cout << "不存在从顶点" << G->vexlist[bgn].data << "到顶点" << G->vexlist[end].data << "的路径！" << endl;
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
	cout << "请输入各顶点信息：";
	for (int i = 0; i < G->vertexnum; i++)
	{
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
		EdgeNode *q = new EdgeNode;
		q->adjvex = head;
		q->weight = cost;
		q->next = G->vexlist[tail].firstedge;
		G->vexlist[tail].firstedge = q;
	}
}
bool ExistPath(AdjGraph *G, int bgn, int end)
{
	if (bgn == end)
		return true;
	visited[bgn] = true;
	EdgeNode *p = G->vexlist[bgn].firstedge;
	while (p != NULL)
	{
		if (!visited[p->adjvex])
			return ExistPath(G, p->adjvex, end);
		p = p->next;
	}
	return false;
}