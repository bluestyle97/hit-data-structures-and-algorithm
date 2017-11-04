//@Filename:	btreealgorithm.cpp
//@Description:	Some algorithm of binary tree
//@Author:		Xu Jiale
//@Create Time:	2016/12/25, 20:08
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#include <stack>
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
typedef BtreeNode * Btree;

//Function:		CreateBtree
//Description:	Create a binary tree and return its root
//Arguments:	void
//Return:		Btree: the root of the created binary tree
Btree CreateBtree(void);
//Function:		Count
//Description:	Calculate the number of a binary tree's nodes
//Arguments:	Btree: the root of a binary tree
//Return:		int: the result
int Count(Btree);
//Function:		Height
//Description:	Calculate the height of a binary tree
//Arguments:	Btree: the root of a binary tree
//Return:		int: the result
int Height(Btree);
//Function:		Destroy
//Description:	Destroy a binary tree
//Arguments:	Btree: the root of a binary tree
//Return:		void
void Destroy(Btree);
//Function:		ExchangeRec
//Description:	Exchange the left child tree and the right child tree of every node(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void ExchangeRec(Btree);
//Function:		Exchange
//Description:	Exchange the left child tree and the right child tree of every node(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void Exchange(Btree);
//Function:		LevelOrder
//Description:	Levelorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void LevelOrder(Btree);

int main()
{
	Btree T = NULL;
	bool flag = true;
	while (flag)
	{
		char choice;
		cout << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << "|              二叉树基本操作如下              |" << endl;
		cout << "|              0.创建二叉树                    |" << endl;
		cout << "|              1.计算节点总数                  |" << endl;
		cout << "|              2.计算高度                      |" << endl;
		cout << "|              3.递归左右翻转                  |" << endl;
		cout << "|              4.非递归左右翻转                |" << endl;
		cout << "|              5.层序遍历                      |" << endl;
		cout << "|              6.退出程序                      |" << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << "               请选择功能：";
		cin >> choice;
		switch (choice)
		{
		case '0':
			cout << "请按先序输入各结点数据（若为空则输入#）：" << endl;
			T = CreateBtree();
			break;
		case '1':
			int count;
			count = Count(T);
			cout << "二叉树的节点总数为：" << count << endl;
			break;
		case '2':
			int height;
			height = Height(T);
			cout << "二叉树的高度为：" << height << endl;
			break;
		case '3':
			ExchangeRec(T);
			cout << "二叉树左右翻转完成！" << endl;
			break;
		case '4':
			Exchange(T);
			cout << "二叉树左右翻转完成！" << endl;
			break;
		case '5':
			cout << "二叉树层序遍历的结果为：";
			LevelOrder(T);
			break;
		case '6':
			Destroy(T);
			flag = false;
			cout << "程序运行结束！" << endl;
			break;
		default:
			cout << "您的输入有误，请重新输入！";
		}
	}
	system("pause");
	return 0;
}

Btree CreateBtree(void)
{
	Btree T;
	char ch;
	cin >> ch;
	if (ch == '#')				//输入“#”时证明该结点处为空
		return NULL;
	else
	{
		T = new BtreeNode;
		T->data = ch;
		T->lchild = CreateBtree();
		T->rchild = CreateBtree();
	}
	return T;
}
int Count(Btree T)
{
	if (T == NULL)
		return 0;
	return 1 + Count(T->lchild) + Count(T->rchild);
}
int Height(Btree T)
{
	int m, n;
	if (T == NULL)
		return 0;
	m = Height(T->lchild);
	n = Height(T->rchild);
	return (m > n) ? (m + 1) : (n + 1);
}
void Destroy(Btree T)
{
	if (T != NULL)
	{
		Destroy(T->lchild);
		Destroy(T->rchild);
		delete T;
	}
}
void ExchangeRec(Btree T)
{
	Btree p = T;
	Btree temp = NULL;
	if (p != NULL)
	{
		temp = p->lchild;
		p->lchild = p->rchild;
		p->rchild = temp;
		ExchangeRec(p->lchild);
		ExchangeRec(p->rchild);
	}
}
void Exchange(Btree T)
{
	Btree p = NULL;
	Btree temp = NULL;
	stack<Btree> S;
	if (T != NULL)
	{
		S.push(T);
		while (!S.empty())
		{
			p = S.top();
			S.pop();
			temp = p->lchild;
			p->lchild = p->rchild;
			p->rchild = temp;
			if (p->lchild != NULL)
				S.push(p->lchild);
			if (p->rchild != NULL)
				S.push(p->rchild);
		}
	}
}
void LevelOrder(Btree t)		//函数：层序遍历二叉树
{
	queue<Btree> Q;
	if (t == NULL)
		return;
	Q.push(t);
	while (!Q.empty())		//层序遍历
	{
		cout << Q.front()->data;
		if (Q.front()->lchild != NULL)
			Q.push(Q.front()->lchild);		//左子树入队
		if (Q.front()->rchild != NULL)
			Q.push(Q.front()->rchild);		//右子树入队
		Q.pop();
	}
}