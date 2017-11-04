//@Filename:	bstree.cpp
//@Description: binary search tree
//@Author:		Xu Jiale
//@Create Time: 2016/12/14, 17:33
//Copyright (C) 2016 HIT. All rights reserved
#include <iostream>

using namespace std;

//Struct:		records
//Description:	A record
//Members:		key: the key of the records
//				number: the number of the same key
struct records
{
	int key;
	int number;
};
//Struct:		BSTNode
//Description:	The node of a binary search tree
//Members:		data: the record stored in the node
//				lchild: the left child of the node
//				rchild: the right child of the node
struct BSTNode
{
	records data;
	BSTNode * lchild;
	BSTNode * rchild;
};
typedef BSTNode * BST;

//FUnction:		CreateBST
//Description:	Create a new binary search tree
//Arguments:	void
//Return:		BST: the root of the created binary search tree
BST CreateBST(void);
//Function:		SearchBST
//Description:	Search a record in the binary search tree
//Arguments:	int: the key of the record to be searched
//				BST: the root of the binary search tree
//Return:		BST: the search result
BST SearchBST(int, BST);
//Function:		InsertBST
//Description:	Insert a new record to the binary search tree
//Arguments:	int: the key of the record to be inserted
//				BST &: the root of the binary search tree
//Return:		void
void InsertBST(int, BST &);
//Function:		DeleteBST
//Description:	Delete a record from a bianry search tree
//Arguments:	int: the key of the record to be deleted
//				BST &: the root of the binary search tree
//Return:		void
void DeleteBST(int, BST &);
//Function:		DeleteMin
//Description:	Delete the minimum node from the binary search tree and return the record inside it
//Arguments:	BST &: the root of a binary search tree
//Return:		records: the record stored in the deleted node
records DeleteMin(BST &);
//Funtion:		InOrder
//Description:	Traverse the binary search tree in inorder
//Arguments:	BST: the root of the binary search tree
//Return:		void
void InOrder(BST);

int main()
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       欢迎使用二叉查找树系统！         |" << endl;
	cout << " ---------------------------------------- " << endl;
	char choice = ' ';
	int key;
	BST T = new BSTNode;
	while (choice != '6')
	{
		cout << endl;
		cout << " ---------------------------------------- " << endl;
		cout << "|       请按数字键选择相应功能：         |" << endl;
		cout << "|       1.创建二叉查找树                 |" << endl;
		cout << "|       2.中序遍历二叉查找树             |" << endl;
		cout << "|       3.查找记录                       |" << endl;
		cout << "|       4.插入记录                       |" << endl;
		cout << "|       5.删除记录                       |" << endl;
		cout << "|       6.退出程序                       |" << endl;
		cout << " ---------------------------------------- " << endl;
		cout << "        请输入您的选择：";
		cin >> choice;
		cout << " ---------------------------------------- " << endl;
		switch (choice)
		{
		case '1':
			cout << "请输入二叉查找树元素：";
			T = CreateBST();
			cout << "二叉查找树创建成功！" << endl;
			break;
		case '2':
			cout << "二叉查找树的中序遍历结果为：";
			InOrder(T);
			cout << endl;
			break;
		case '3':
			BST pointer;
			cout << "请输入您想查找记录的关键字：";
			cin >> key;
			pointer = SearchBST(key, T);
			if (pointer != NULL)
				cout << "查找成功！二叉查找树中共有" << pointer->data.number << "个记录关键字为" << key << endl;
			else
				cout << "查找失败！二叉查找树中没有记录关键字为" << key << endl;
			break;
		case '4':
			cout << "请输入您想插入记录的关键字：";
			cin >> key;
			InsertBST(key, T);
			cout << "记录已插入！" << endl;
			break;
		case '5':
			cout << "请输入您想删除记录的关键字：";
			cin >> key;
			DeleteBST(key, T);
			cout << "记录已删除！" << endl;
			break;
		case '6':
			cout << " ------------------------------------------ " << endl;
			cout << "|       感谢使用二叉查找树系统             |" << endl;
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

BST CreateBST(void)
{
	BST T = NULL;
	int key;
	while (cin >> key)
		InsertBST(key, T);
	cin.clear();
	return T;
}
void InOrder(BST T)
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		for (int i = 0; i < T->data.number; i++)
			cout << T->data.key << " ";
		InOrder(T->rchild);
	}
}
BST SearchBST(int k, BST T)
{
	if (T == NULL || k == T->data.key)
		return T;
	else if (k < T->data.key)
		return SearchBST(k, T->lchild);
	else
		return SearchBST(k, T->rchild);
}
void InsertBST(int k, BST &T)
{
	if (T == NULL)
	{
		T = new BSTNode;
		T->data.key = k;
		T->data.number = 1;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else if (k < T->data.key)
		InsertBST(k, T->lchild);
	else if (k > T->data.key)
		InsertBST(k, T->rchild);
	else
		T->data.number++;
}
void DeleteBST(int k, BST &T)
{
	if (T != NULL)
	{
		if (k < T->data.key)
			DeleteBST(k, T->lchild);
		else if (k > T->data.key)
			DeleteBST(k, T->rchild);
		else
		{
			if (T->data.number > 1)
				--T->data.number;
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
	}
}
records DeleteMin(BST &T)
{
	records tmp;
	BST p;
	if (T->lchild == NULL)
	{
		p = T;
		tmp = T->data;
		T = T->rchild;
		delete p;
		return tmp;
	}
	else
		return DeleteMin(T->lchild);
}
