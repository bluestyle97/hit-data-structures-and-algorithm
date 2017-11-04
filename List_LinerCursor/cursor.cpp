// linkedlist.cpp -- 线性表的游标实现
#include <iostream>
#define MAXSIZE 100

using namespace std;

//类型定义
template <typename elementtype>
struct space
{
	elementtype element;
	int next;
};
template <typename elementtype>
space SPACE[MAXSIZE];		//存储池
typedef int cursor;
cursor av;		//游标变量，标识线性表

				//存储池管理：可用空间的初始化
template <typename elementtype>
void Initialize(space &S, int *av)
{
	int i;
	for (j = 0; j < MAXSIZE - 1; j++)
		S[j].next = j + 1;
	S[j].next = -1;
	*av = 0;
}

//操作：插入
template <typename elementtype>
void Insert(elementtype x, cursor p, space &S)		//插入p后面
{
	cursor q;
	S[q].element = x;
	S[q].next = S[q].next;
	S[p].next = q;
}

//操作：删除
template <typename elementtype>
void Delete(cursor p, space &S)
{
	cursor q;
	if (S[p].next != -1)
	{
		q = S[p].next;
		S[p].next = S[q].next;
	}
}
