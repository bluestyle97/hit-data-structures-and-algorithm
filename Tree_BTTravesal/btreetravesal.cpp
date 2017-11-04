//@Filename:	btreeTravesal.cpp
//@Description:	Traversal of binary tree
//@Author:		Xu Jiale
//@Create Time:	2016/11/29, 11:20
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
//Btree:		the root of a binary tree
typedef BtreeNode * Btree;

//Function:		CreateBtree
//Description:	Create a binary tree and return its root
//Arguments:	void
//Return:		Btree: the root of the created binary tree
Btree CreateBtree(void);
//Function:		PreOrderRec
//Description:	Preorder travesal of binary tree(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PreOrderRec(Btree);
//Function:		InOrderRec
//Description:	Inorder travesal of binary tree(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void InOrderRec(Btree);
//Function:		PostOrderRec
//Description:	Postorder travesal of binary tree(recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PostOrderRec(Btree);
//Function:		PreOrder
//Description:	Preorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PreOrder(Btree);
//Function:		InOrder
//Description:	Inorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void InOrder(Btree);
//Function:		PostOrder
//Description:	Postorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void PostOrder(Btree);
//Function:		LevelOrder
//Description:	Levelorder travesal of binary tree(non-recursive)
//Arguments:	Btree: the root of a binary tree
//Return:		void
void LevelOrder(Btree);

int main()
{
	Btree t = NULL;
	bool flag = true;
	while (flag)
	{
		char choice;
		cout << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << "|              二叉树基本操作如下              |" << endl;
		cout << "|              0.创建二叉树                    |" << endl;
		cout << "|              1.递归先序遍历                  |" << endl;
		cout << "|              2.递归中序遍历                  |" << endl;
		cout << "|              3.递归后序遍历                  |" << endl;
		cout << "|              4.非递归先序遍历                |" << endl;
		cout << "|              5.非递归中序遍历                |" << endl;
		cout << "|              6.非递归后序遍历                |" << endl;
		cout << "|              7.层序遍历                      |" << endl;
		cout << "|              8.退出程序                      |" << endl;
		cout << " ---------------------------------------------- " << endl;
		cout << "               请选择功能：";
		cin >> choice;
		switch (choice)
		{
		case '0':
			cout << "请按先序输入各结点数据（若为空则输入#）：" << endl;
			t = CreateBtree();
			break;
		case '1':
			cout << "递归先序遍历的结果为：";
			PreOrderRec(t);
			break;
		case '2':
			cout << "递归中序遍历的结果为：";
			InOrderRec(t);
			break;
		case '3':
			cout << "递归后序遍历的结果为：";
			PostOrderRec(t);
			break;
		case '4':
			cout << "非递归先序遍历的结果为：";
			PreOrder(t);
			break;
		case '5':
			cout << "非递归中序遍历的结果为：";
			InOrder(t);
			break;
		case '6':
			cout << "非递归后序遍历的结果为：";
			PostOrder(t);
			break;
		case '7':
			cout << "层序遍历的结果为：";
			LevelOrder(t);
			break;
		case '8':
			flag = false;
			cout << "程序运行结束！";
			break;
		default:
			cout << "您的输入有误，请重新输入！";
		}
	}
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

void PreOrderRec(Btree t)		//函数：先序遍历二叉树的递归实现
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrderRec(t->lchild);
		PreOrderRec(t->rchild);
	}
}

void InOrderRec(Btree t)		//函数：中序遍历二叉树的递归实现
{
	if (t != NULL)
	{
		InOrderRec(t->lchild);
		cout << t->data;
		InOrderRec(t->rchild);
	}
}

void PostOrderRec(Btree t)		//函数：后续遍历二叉树的递归实现
{
	if (t != NULL)
	{
		PostOrderRec(t->lchild);
		PostOrderRec(t->rchild);
		cout << t->data;
	}
}

void PreOrder(Btree t)			//函数：先序遍历二叉树的非递归实现
{
	if (t == NULL)
		return;
	Btree p = t;
	stack<Btree> S;
	while (p != NULL || !S.empty())
	{
		while (p != NULL)
		{
			cout << p->data;
			S.push(p);
			p = p->lchild;
		}
		if (!S.empty())		//遍历右子树
		{
			p = S.top();
			S.pop();
			p = p->rchild;
		}
	}
}

void InOrder(Btree t)			//函数：中序遍历二叉树的非递归实现
{
	if (t == NULL)
		return;
	Btree p = t;
	stack<Btree> S;
	while (p != NULL || !S.empty())
	{
		while (p != NULL)
		{
			S.push(p);		//左子树入栈
			p = p->lchild;
		}
		if (!S.empty())		//遍历右子树
		{
			p = S.top();
			S.pop();
			cout << p->data;
			p = p->rchild;
		}
	}
}

void PostOrder(Btree t)			//函数：后序遍历二叉树的非递归实现
{
	Btree p = t;
	Btree pre = NULL;
	stack<Btree> S;
	while (p != NULL || !S.empty())
	{
		while (p != NULL)
		{
			S.push(p);		//左子树入栈
			p = p->lchild;
		}
		p = S.top();
		if (p->rchild == NULL || p->rchild == pre)
		{
			cout << p->data;
			pre = p;
			S.pop();
			p = NULL;
		}
		else					//遍历右子树
			p = p->rchild;
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