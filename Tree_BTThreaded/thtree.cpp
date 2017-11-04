//@Filename:	thtree.cpp
//@Description:	Threaded binary tree
//@Author:		Xu Jiale
//@Create Time:	2017/01/01, 11:08
//Copyright (C) 2017 HIT. All rights reserved

#include <iostream>

using namespace std;

struct node
{
	char data;
	node *lchild;
	node *rchild;
	bool ltag;
	bool rtag;
};
typedef node * ThTree;

ThTree pre = NULL;

ThTree CreateThTree(void);
ThTree InNext(ThTree);
ThTree PreNext(ThTree);
void InOrderThTree(ThTree);
void ThInOrder(ThTree);
void RchildInsert(ThTree, ThTree);

int main()
{
	return 0;
}

ThTree CreateThTree(void)
{
	ThTree t = new node;
	char ch;
	cin >> ch;
	if (ch == '#')
		return NULL;
	else
	{
		t->data = ch;
		t->lchild = CreateThTree();
		t->rchild = CreateThTree();
	}
	return t;
}
ThTree InNext(ThTree p)
{
	ThTree q;
	node * q;
	q = p->rchild;
	if (p->rtag == true)
		while (q->ltag == true)
			q = q->lchild;
	return q;
}
ThTree PreNext(ThTree p)
{
	ThTree q = NULL;
	if (p->ltag == true)
		q = p->lchild;
	else
	{
		q = p;
		while (q->rtag = false)
			q = q->rchild;
		q = q->rchild;
	}
	return q;
}
void InOrderThTree(ThTree t)
{
	if (t != NULL)
	{
		InOrderThTree(t->lchild);
		t->ltag = (t->lchild) ? true : false;
		t->rtag = (t->rchild) ? true : false;
		if (pre != NULL)
		{
			if (pre->rtag == false)
				pre->rchild = t;
			if (pre->ltag == false)
				t->lchild = pre;
		}
		pre = t;
		InOrderThTree(t->rchild);
	}
}
void ThInOrder(ThTree head)
{
	ThTree temp = head;
	do
	{
		temp = InNext(temp);
		if (temp != head)
			cout << temp->data;
	} while (temp != head);
}
void RchildInsert(ThTree s, ThTree r)
{
	ThTree t = NULL;
	r->rchild = s->rchild;
	r->rtag = s->rtag;
	r->lchild = s;
	r->ltag = false;
	s->rchild = r;
	s->rtag = true;
	if (r->ltag == true)
	{
		t = InNext(r);
		t->lchild = r;
	}
}