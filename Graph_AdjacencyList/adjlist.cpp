//@Filename:	adjmatrix.cpp
//@Description:	Adjacency matrix representation of graph and its search(take undirected graph for example)
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 17:25
//Copyright (C) 2016 HIT. All rights reserved
#include <iostream>
#include <stack>
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

//array:		Judge whether the current vertex has been visited
bool *visited;
//array:		Numbers of depth-first search
int *dfn;

//Function:		CreateAdjGraph
//Description:	Create a new graph
//Arguments:	AdjGraph *: the pointer of a graph
//Return:		void
void CreateAdjGraph(AdjGraph *);
//Funtion:		InitVisited
//Description:	Initialize the array "visited"
//Arguments:	MTGraph *; the pointer of a graph
//Return:		void
void InitVisited(AdjGraph *);
//Function:		InitDfn
//Description:	Initialize the array "dfn"
//Arguments:	MTGraph *; the pointer of a graph
//Return:		void
void InitDfn(AdjGraph *);
//Function:		DFSGraph1
//Description:	Depth-first search of the graph(recursive)
//Arguments:	AdjGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void DFSGraph1(AdjGraph *, int);
//Function:		DFSGraph2
//Description:	Depth-first search of the graph(non-recursive)
//Arguments:	AdjGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void DFSGraph2(AdjGraph *, int);
//Function:		BFSGraph
//Description:	Breadth-first search of the graph(non-recursive)
//Arguments:	AdjGraph *: the pointer of a graph
//				int: the original vertex of search
//Return:		void
void BFSGraph(AdjGraph *, int);

int main()
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       欢迎使用图的搜索系统！           |" << endl;
	cout << " ---------------------------------------- " << endl;
	AdjGraph *G = new AdjGraph;
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
			CreateAdjGraph(G);
			break;
		case '2':
			InitVisited(G);
			InitDfn(G);
			DFSGraph1(G, 0);
			break;
		case '3':
			InitVisited(G);
			InitDfn(G);
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
void InitVisited(AdjGraph *G)
{
	visited = new bool[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		visited[i] = false;
}
void InitDfn(AdjGraph *G)
{
	dfn = new int[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		dfn[i] = 0;
}
void DFSGraph1(AdjGraph *G, int i)
{
	int count = 0;
	EdgeNode *p;
	cout << G->vexlist[i].data;
	visited[i] = true;
	dfn[i] = count++;
	p = G->vexlist[i].firstedge;
	while (p != NULL)
	{
		if (!visited[p->adjvex])
			DFSGraph1(G, p->adjvex);
		p = p->next;
	}
}
void DFSGraph2(AdjGraph *G, int i)
{
	int k, count = 0;
	EdgeNode *p;
	stack <int> S;
	visited[i] = true;
	S.push(i);
	while (!S.empty())
	{
		k = S.top();
		S.pop();
		cout << G->vexlist[k].data;
		dfn[k] = count++;
		p = G->vexlist[k].firstedge;
		while (p != NULL)
		{
			if (!visited[p->adjvex])
			{
				visited[p->adjvex] = true;
				S.push(p->adjvex);
			}
			p = p->next;
		}
	}
}
void BFSGraph(AdjGraph *G, int i)
{
	int k;
	EdgeNode *p;
	queue <int> Q;
	visited[i] = true;
	Q.push(i);
	while (!Q.empty())
	{
		k = Q.front();
		Q.pop();
		cout << G->vexlist[k].data;
		p = G->vexlist[k].firstedge;
		while (p != NULL)
		{
			if (!visited[p->adjvex])
			{
				visited[p->adjvex] = true;
				Q.push(p->adjvex);
			}
			p = p->next;
		}
	}
}