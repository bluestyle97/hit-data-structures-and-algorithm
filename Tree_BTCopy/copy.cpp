//@Filename:	copy.cpp
//@Description:	Copy a binary tree
//@Author:		Xu Jiale
//@Create Time:	2017/01/01, 12:54
//Copyright (C) 2017 HIT. All rights reserved

#include <iostream>

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
//Function:		Equal
//Description:	Judge whether a binary tree is equal to another
//Arguments:	Btree: the first binary tree
//				Btree: the second binary tree
//Return:		bool: judge result
bool Equal(Btree, Btree);
//Function:		Copy
//Description:	Copy a binary tree
//Arguments:	Btree: the binary to be copied
//Return:		Btree: the copied binary tree
Btree Copy(Btree);

int main()
{
	return 0;
}

bool Equal(Btree firstbt, Btree secondbt)
{
	bool result = false;
	if (firstbt == NULL && secondbt == NULL)
		return true;
	else if (firstbt != NULL && secondbt != NULL)
		if (firstbt->data == secondbt->data)
			if (Equal(firstbt->lchild, secondbt->lchild))
				result = Equal(firstbt->rchild, secondbt->rchild);
	return result;
}
Btree Copy(Btree oldtree)
{
	Btree temp = new BtreeNode;
	if (oldtree != NULL)
	{
		temp->data = oldtree->data;
		temp->lchild = Copy(oldtree->lchild);
		temp->rchild = Copy(oldtree->rchild);
		return temp;
	}
	return NULL;
}