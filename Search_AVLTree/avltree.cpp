//@Filename:	avltree.cpp
//@Description: Avltree
//@Author:		Xu Jiale
//@Create Time: 2016/12/19, 22:04
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>

using namespace std;

struct records
{
	int key;
	int number;
};
struct AVLNode
{
	int data;
	AVLNode * lchild;
	AVLNode * rchild;
	int height;
};
typedef AVLNode * Position;
typedef AVLNode * AVLTree;

AVLTree Create(void);
AVLTree MakeEmpty(AVLTree);
AVLTree Insert(int, AVLTree);
AVLTree Delete(int, AVLTree);
Position Search(int, AVLTree);
Position FindMin(AVLTree);
Position FindMax(AVLTree);
Position SingleRotateWithLeft(Position);
Position DoubleRotateWithLeft(Position);
Position SingleRotateWithRight(Position);
Position DoubleRotateWithRight(Position);
int DeleteMin(AVLTree);
int Retrieve(Position);
int GetHeight(Position);
int Max(int, int);
void InOrder(AVLTree);

int main()
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       欢迎使用AVL树系统！              |" << endl;
	cout << " ---------------------------------------- " << endl;
	char choice = ' ';
	int key;
	AVLTree T = NULL;
	Position pointer = NULL;
	while (choice != '6')
	{
		cout << endl;
		cout << " ---------------------------------------- " << endl;
		cout << "|       请按数字键选择相应功能：         |" << endl;
		cout << "|       1.创建AVL树                      |" << endl;
		cout << "|       2.中序遍历AVL树                  |" << endl;
		cout << "|       3.查找结点                       |" << endl;
		cout << "|       4.插入结点                       |" << endl;
		cout << "|       5.删除结点                       |" << endl;
		cout << "|       6.退出程序                       |" << endl;
		cout << " ---------------------------------------- " << endl;
		cout << "        请输入您的选择：";
		cin >> choice;
		cout << " ---------------------------------------- " << endl;
		switch (choice)
		{
		case '1':
			cout << "请输入AVL树元素：";
			T = Create();
			cout << "AVL树创建成功！" << endl;
			break;
		case '2':
			cout << "AVL树的中序遍历结果为：";
			InOrder(T);
			cout << endl;
			break;
		case '3':
			cout << "请输入您想查找的结点数据：";
			cin >> key;
			pointer = Search(key, T);
			if (pointer != NULL)
				cout << "查找成功！" << endl;
			else
				cout << "查找失败！AVL树中没有该元素！" << endl;
			break;
		case '4':
			cout << "请输入您想插入的结点数据：";
			cin >> key;
			T = Insert(key, T);
			cout << "结点已插入！" << endl;
			break;
		case '5':
			cout << "请输入您想删除的结点数据：";
			cin >> key;
			T = Delete(key, T);
			cout << "结点已删除！" << endl;
			break;
		case '6':
			cout << " ------------------------------------------ " << endl;
			cout << "|       感谢使用AVL树系统                  |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       您的输入有误，请重新输入！         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	return 0;
}

AVLTree Create(void)
{
	AVLTree T = NULL;
	int key;
	while (cin >> key)
		T = Insert(key, T);
	cin.clear();
	return T;
}
AVLTree MakeEmpty(AVLTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->lchild);
		MakeEmpty(T->rchild);
		delete T;
	}
	return NULL;
}
AVLTree Insert(int x, AVLTree T)
{
	if (T == NULL)
	{
		T = new AVLNode;
		if (T == NULL)
			cout << "Out of space!" << endl;
		else
		{
			T->data = x;
			T->lchild = T->rchild = NULL;
		}
	}
	else if (x < T->data)
	{
		T->lchild = Insert(x, T->lchild);
		if (GetHeight(T->lchild) - GetHeight(T->rchild) == 2)
		{
			if (x < T->lchild->data)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (x > T->data)
	{
		T->rchild = Insert(x, T->rchild);
		if (GetHeight(T->rchild) - GetHeight(T->lchild) == 2)
		{
			if (x > T->rchild->data)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}
	T->height = Max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;
	return T;
}
AVLTree Delete(int x, AVLTree T)
{
	if (T != NULL)
	{
		if (x < T->data)
			T->lchild = Delete(x, T->lchild);
		else if (x > T->data)
			T->rchild = Delete(x, T->rchild);
		else
		{
			if (T->lchild == NULL)
				T = T->rchild;
			else if (T->rchild == NULL)
				T = T->lchild;
			else
				T->data = DeleteMin(T->rchild);
		}
	}
	return T;
}
Position Search(int x, AVLTree T)
{
	if (T == NULL)
		return NULL;
	else if (x == T->data)
		return T;
	else if (x < T->data)
		return Search(x, T->lchild);
	else
		return Search(x, T->rchild);
}
Position FindMin(AVLTree T)
{
	Position P = T;
	if (T == NULL)
		return NULL;
	while (P->lchild != NULL)
		P = P->lchild;
	return P;
}
Position FindMax(AVLTree T)
{
	Position P = T;
	if (T == NULL)
		return NULL;
	while (P->rchild != NULL)
		P = P->rchild;
	return P;
}
Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->lchild;
	K2->lchild = K1->rchild;
	K1->rchild = K2;
	K2->height = Max(GetHeight(K2->lchild), GetHeight(K2->rchild)) + 1;
	K1->height = Max(GetHeight(K1->lchild), K2->height) + 1;
	return K1;
}
Position DoubleRotateWithLeft(Position K3)
{
	K3->lchild = SingleRotateWithRight(K3->lchild);
	return SingleRotateWithLeft(K3);
}
Position SingleRotateWithRight(Position K2)
{
	Position K1;

	K1 = K2->rchild;
	K2->rchild = K1->lchild;
	K1->lchild = K2;
	K2->height = Max(GetHeight(K2->lchild), GetHeight(K2->rchild)) + 1;
	K1->height = Max(GetHeight(K1->rchild), K2->height) + 1;
	return K1;
}
Position DoubleRotateWithRight(Position K3)
{
	K3->rchild = SingleRotateWithLeft(K3->rchild);
	return SingleRotateWithRight(K3);
}
int DeleteMin(AVLTree T)
{
	int temp;
	Position Ptemp;
	Position P = T;
	while (P->lchild != NULL)
		P = P->lchild;
	temp = P->data;
	Ptemp = P;
	P = P->rchild;
	delete Ptemp;
	return temp;
}
int Retrieve(Position P)
{
	if (P == NULL)
		return -1;
	return P->data;
}
int GetHeight(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->height;
}
int Max(int a, int b)
{
	return (a > b) ? a : b;
}
void InOrder(AVLTree T)
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		cout << T->data << " ";
		InOrder(T->rchild);
	}
}