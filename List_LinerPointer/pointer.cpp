// linkedlist.cpp -- 线性表的指针实现
#include <iostream>

using namespace std;

//类型定义
template <typename elementtype>
struct celltype
{
	elementtype element;
	celltype * next;
};
template <typename elementtype>
typedef celltype * LIST;
template <typename elementtype>
typedef celltype * position;

//操作：插入
template <typename elementtype>
position Insert(elementtype x, position p, LIST &L)		//插入位置p之前
{
	position q = new celltype;
	position s = L;
	if (p == L)
	{
		q->element = x;
		q->next = p;
		return q;
	}
	else
	{
		while (s->next != p && s->next != NULL)
			s = s->next;
		q->element = x;
		q->next = s->next;
		s->next = q;
		return L;
	}
}

//操作：定位
template <typename elementtype>
position Locate(elementtype x, LIST L)
{
	position p = L;
	while (p != NULL)
	{
		if (p->element == x)
			return p;
		p = p->next;
	}
	return p;
}

//操作：取元素值
template <typename elementtype>
elementtype Retrieve(position p, LIST　L)
{
	return p->element;
}

//操作：删除
template <typename elementtype>
void Delete(position p, LIST L)		//删除p后面的元素
{
	position q = new celltype;
	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		delete q;
	}
}

//操作：前驱
template <typename elementtype>
position Previous(position p, LIST L)
{
	position q = new celltype;
	if (p == L)
		cerr << "前驱元素不存在" << endl;
	else
	{
		q = L;
		while (q->next != p)
			q = q->next;
		return q;
	}
}

//操作：后继
template <typename elementtype>
position Next(position p, LIST L)
{
	position q;
	if (p->next == NULL)
		cerr << "后继元素不存在" << endl;
	else
	{
		q = p->next;
		return q;
	}
}

//操作：清空
template <typename elementtype>
position Makenull(LIST &L)
{
	L = new celltype;
	L->next = NULL;
	return L;
}

//操作：表头
template <typename elementtype>
position First(LIST L)
{
	return L;
}

//操作：表尾
template <typename elementtype>
position End(LIST L)
{
	position q = L;
	while (q->next != NULL)
		q = q->next;
	return q;
}