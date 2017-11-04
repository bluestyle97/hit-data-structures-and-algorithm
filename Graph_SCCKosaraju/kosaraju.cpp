//kosaraju.cpp -- 寻找有向图的强连通分量
#include <iostream>
#include <stack>

using namespace std;

typedef struct node		//边结点
{
	int adjvex;			//终点序号
	node *next;			//下一结点
} EdgeNode;
typedef struct			//顶点结点
{
	char data;			//顶点数据
	EdgeNode *firstedge;//边
} VertexNode;
typedef struct			//图的邻接表表示
{
	VertexNode *vexlist;//顶点列表
	int vertexnum;		//顶点数
	int edgenum;		//边数
} AdjGraph;

bool *visited;			//数组visited：标识结点是否被访问
stack<int> order;		//栈order：记录每个结点的访问完成时间

void CreateAdjGraph(AdjGraph *, AdjGraph *);//函数：创建一个有向图G，同时得到将其各边反向的图Grev
void InitVisited(AdjGraph *);				//函数：初始化visited数组
void FillOrder(AdjGraph *, int);			//函数：对有向图进行深度优先搜索，得到各结点的访问序列order
void DFSGraph(AdjGraph *, int);				//函数：对有向图进行深度优先搜索，得到各强连通分量顶点序列
void PrintSC(AdjGraph *, AdjGraph *);		//函数：判断有向图是否为强连通图，若不是则输出各强连通分量顶点序列

int main()
{
	AdjGraph *G = new AdjGraph;
	AdjGraph *Grev = new AdjGraph;
	CreateAdjGraph(G, Grev);
	PrintSC(G, Grev);
	cin.get();
	cin.get();
	return 0;
}
void CreateAdjGraph(AdjGraph * G, AdjGraph *Grev)
{
	int head, tail;							//起点序号，终点序号
	cout << "请输入顶点数：";
	cin >> G->vertexnum;
	Grev->vertexnum = G->vertexnum;
	cout << "请输入边数：";
	cin >> G->edgenum;
	Grev->edgenum = G->edgenum;
	G->vexlist = new VertexNode[G->vertexnum];
	Grev->vexlist = new VertexNode[Grev->vertexnum];
	cout << "请输入各顶点信息：";
	for (int i = 0; i < G->vertexnum; i++)	//输入各结点数据（名称）
	{
		cin >> G->vexlist[i].data;
		Grev->vexlist[i].data = G->vexlist[i].data;
		G->vexlist[i].firstedge = NULL;
		Grev->vexlist[i].firstedge = NULL;
	}
	cout << "请输入各边信息（起点 终点）：" << endl;
	for (int i = 0; i < G->edgenum; i++)
	{
		cin >> head >> tail;
		EdgeNode *p = new EdgeNode;		//同时初始化G和它的转置图Grev的邻接表
		p->adjvex = tail;
		p->next = G->vexlist[head].firstedge;
		G->vexlist[head].firstedge = p;
		EdgeNode *q = new EdgeNode;
		q->adjvex = head;
		q->next = Grev->vexlist[tail].firstedge;
		Grev->vexlist[tail].firstedge = q;
	}
}
void InitVisited(AdjGraph *G)	//为visited数组分配空间并将其中所有元素初始化为false
{
	visited = new bool[G->vertexnum];
	for (int i = 0; i < G->vertexnum; i++)
		visited[i] = false;
}
void FillOrder(AdjGraph *G, int i)	//从结点i开始的深度优先搜索
{
	EdgeNode *p;
	visited[i] = true;
	p = G->vexlist[i].firstedge;
	while (p != NULL)
	{
		if (!visited[p->adjvex])
			FillOrder(G, p->adjvex);
		p = p->next;
	}
	order.push(i);	//每个结点访问完成后（回溯返回时）将其压入栈order中
}
void DFSGraph(AdjGraph *G, int i)	//从结点i开始的深度优先搜索
{
	EdgeNode *p;
	visited[i] = true;
	cout << G->vexlist[i].data << " ";	//输出结点数据
	p = G->vexlist[i].firstedge;
	while (p != NULL)
	{
		if (!visited[p->adjvex])
			DFSGraph(G, p->adjvex);
		p = p->next;
	}
}
void PrintSC(AdjGraph *G, AdjGraph *Grev)
{
	int count = 0;		//count：用于记录深度优先搜索进行的次数，若count>1则说明一次搜索不能遍历所有结点，即有向图不强连通
	InitVisited(G);		//初始化visited数组
	for (int i = 0; i < G->vertexnum; i++)		//从结点0开始对原图进行深度优先搜索，得到结点访问序列
		if (!visited[i])
			FillOrder(G, i);
	cout << "有向图中各强连通分量中的顶点如下：" << endl;
	for (int i = 0; i < G->vertexnum; i++)		//重新初始化visited数组准备进行第二次深度优先搜索
		visited[i] = false;
	while (!order.empty())		//从栈order栈顶结点开始搜索，直到栈为空
	{
		int k = order.top();
		order.pop();
		if (!visited[k])		//打印各强连通分量包含的顶点序列
		{
			DFSGraph(Grev, k);
			cout << endl;
		}
	}
}
