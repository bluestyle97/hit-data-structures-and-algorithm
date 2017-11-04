//@Filename:	level.cpp
//@Description:	Levelorder travesal and print each node's level number;
//@Author:		Xu Jiale
//@Create Time:	2017/01/03, 11:05
//Copyright (C) 2017 HIT. All rights reserved

#include <iostream>
#include <queue>

using namespace std;

//Struct:		BtreeNode
//Description:	Node of binary tree
//Members:		data: the data stored in the node
//				lchild: the left child node
//				rchild: the right child node
struct BtreeNode
{
	char data;
	BtreeNode * lchild;
	BtreeNode * rchild;
};
//Btree:		the root of a binary tree
typedef BtreeNode * Btree;

//Function:		CreateBtree
//Description:	Create a binary tree and return its root
//Arguments:	void
//Return:		Btree: the root of the created binary tree
Btree CreateBtree(void);
//Function:		Level
//Description:	Levelorder travesal and print each node's level number,
//				meanwhile calculate the binary tree's height
//Arguments:	Btree: the root of a binary tree
//Return:		void
void Level(Btree);

int main()
{
	cout << "请按先序输入二叉树各结点数据：";
	Btree t = CreateBtree();
	Level(t);
	system("pause");
	return 0;
}

Btree CreateBtree(void)			//函数：根据先序序列创建一棵二叉树
{
	Btree t;
	char ch;
	cin >> ch;
	if (ch == '#')				//输入“#”时证明该结点处为空
		return NULL;
	else
	{
		t = new BtreeNode;
		t->data = ch;
		t->lchild = CreateBtree();
		t->rchild = CreateBtree();
	}
	return t;
}

void Level(Btree t)
{
	if (t == NULL)
	{
		cout << "二叉树高度为0！" << endl;
		return;
	}
	typedef struct
	{
		Btree node;
		int level;
	} Record;
	queue<Record> Q;
	int height = 1;
	Q.push({ t, 1 });
	while (!Q.empty())
	{
		Btree p = Q.front().node;
		int lev = Q.front().level;
		if (lev > height)
			height = lev;
		cout << p->data << "--" << lev << endl;
		if (p->lchild != NULL)
			Q.push({ p->lchild, lev + 1 });
		if (p->rchild != NULL)
			Q.push({ p->rchild, lev + 1 });
		Q.pop();
	}
	cout << "二叉树的高度为" << height << endl;
}