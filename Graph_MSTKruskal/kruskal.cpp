//@Filename:	kruskal.cpp
//@Description:	Kruskal algorithm of minimum spanning tree
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 18:12
//Copyright (C) 2016 HIT. All rights reserved

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
//Struct:		Edge
//Description:	An edge
//Members:		bgn: the origin of the edge
//				end: the destination of the edge
//				wet: the weight of the edge
typedef struct
{
	int bgn;
	int end;
	int wet;
} Edge;

//array:		list of all edges in the graph
Edge *edges;

//Function:		CreateAdjGraph
//Description:	Create a new graph
//Arguments:	AdjGraph *: the pointer of a graph
//Return:		void
void CreateAdjGraph(AdjGraph *);
//Function:		Sort
//Description:	Sort the edges by their weights in ascending order
//Arguments:	AdjGraph *: the pointer of a graph
//Return:		void
void Sort(AdjGraph *, Edge *);
//Function:		Kruskal
//Descriptin:	The procedure of kruskal algorithm
//Arguments:	AdjGraph *: the pointer of a graph
//				Edge *: the list of all edges
//Return:		void
void Kruskal(AdjGraph *, Edge *);
//Function:		Find
//Description:	Find the father of a vertex in order to judge whether it belongs
//				to a different connected component
//Arguments:	int[]: the list of each vertex's father
//				int: the vertex to be judged
//Return:		the father of the vertex
int Find(int[], int);

int main()
{
	AdjGraph *G = new AdjGraph;
	CreateAdjGraph(G);
	Sort(G, edges);
	Kruskal(G, edges);
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
	edges = new Edge[G->edgenum];
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
		p->adjvex = head;
		p->weight = cost;
		p->next = G->vexlist[tail].firstedge;
		G->vexlist[tail].firstedge = p;
		EdgeNode *q = new EdgeNode;
		q->adjvex = tail;
		q->weight = cost;
		q->next = G->vexlist[head].firstedge;
		G->vexlist[head].firstedge = q;
		edges[i].bgn = head;
		edges[i].end = tail;
		edges[i].wet = cost;
	}
}
void Sort(AdjGraph *G, Edge *edges)
{
	int tmp;
	for (int i = 0; i < G->edgenum - 1; i++)
		for (int j = i + 1; j < G->edgenum; j++)
			if (edges[i].wet > edges[j].wet)
			{
				tmp = edges[i].bgn;
				edges[i].bgn = edges[j].bgn;
				edges[j].bgn = tmp;
				tmp = edges[i].end;
				edges[i].end = edges[j].end;
				edges[j].end = tmp;
				tmp = edges[i].wet;
				edges[i].wet = edges[j].wet;
				edges[j].wet = tmp;
			}
}
void Kruskal(AdjGraph *G, Edge *edges)
{
	int bnf, edf;
	int count = 0, weight = 0;
	int *father = new int[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		father[i] = -1;
	cout << "最小生成树中的边有：" << endl;
	for (int i = 0; i < G->edgenum; i++)
	{
		bnf = Find(father, edges[i].bgn);
		edf = Find(father, edges[i].end);
		if (bnf != edf)
		{
			father[edf] = bnf;
			cout << G->vexlist[edges[i].bgn].data << "--" << G->vexlist[edges[i].end].data << endl;
			count++;
			weight += edges[i].wet;
		}
		if (count == G->vertexnum - 1)
		{
			delete father;
			cout << "最小生成树的权值总和为：" << weight << endl;
			return;
		}
	}
}
int Find(int father[], int v)
{
	int f = v;
	while (father[f] >= 0)
		f = father[f];
	return f;
}