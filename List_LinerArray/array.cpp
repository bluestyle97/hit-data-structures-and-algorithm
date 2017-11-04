//@Filename:	array.cpp
//@Description:	Array achievement of liner list
//@Author:		Xu Jiale
//@Create Time:	2016/12/27, 16:01
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXLEN 100

using namespace std;

//Strut:		LIST
//Description:	Liner list achieved by array
//Members:		elements: the elements in the liner list
//				last: the position of the last element
template <typename elementtype>
struct LIST
{
	elementtype elements[MAXLEN];
	int last;
};
typedef int position;

//Function:		Insert
//Description:	Insert an element to a liner list
//Arguments:	elementtype: the element to be inserted
//				position: the position to insert to
//				LIST &: the liner list
//Return:		void
template <typename elementtype>
void Insert(elementtype, position, LIST &);
//Function:		Locate
//Description:	Find the location of an element in the liner list
//Arguments:	elementtype: the element to be located
//				LIST: the liner list
//Return:		position: the position of the element
template <typename elementtype>
position Locate(elementtype, LIST);
//Function:		Retrieve
//Description:	Find the element located at a specific position
//Arguments:	position: the position to be retrieved
//				LIST: the liner list
//Return:		elementtype: the element located at the position
template <typename elementtype>
elementtype Retrieve(position, LIST);
//Function:		Delete
//Description:	Delete an element from the liner list
//Arguments:	positon: the position to be deleted
//				LIST &: the liner list
//Return:		void
template <typename elementtype>
void Delete(position, LIST &);
//Function:		Previous
//Description:	Find the previous element in the liner list
//Arguments:	position: the position of current element
//				LIST: the liner list
//Return:		position: the position of the previous element
template <typename elementtype>
position Previous(position, LIST);
//Function:		Next
//Description:	Find the next element in the liner list
//Arguments:	position: the position of current element
//				LIST: the liner list
//Return:		position: the position of the next element
template <typename elementtype>
position Next(position, LIST);
//Function:		MakeNull
//Description:	Create an empty liner list
//Arguments:	LIST: the liner list
//Return:		position: the first position of the liner list
template <typename elementtype>
position MakeNull(LIST &);
//Function:		First
//Description:	Return the first element in the liner list
//Arguments:	LIST: the liner list
//Return:		elementtyoe: the first element
template <typename elementtype>
elementtype First(LIST);
//Function:		End
//Description:	Return the last element in the liner list
//Arguments:	LIST: the liner list
//Return:		the last element
template <typename elementtype>
elementtype End(LIST);

int main()
{
	return 0;
}

template <typename elementtype>
void Insert(elementtype x, position p, LIST &L)
{
	position q;
	if (L.last > MAXLEN - 1)
		cerr << "链表已满" << endl;
	else if (p > L.last + 1 || p < 1)
	{
		for (q = L.last; q >= p; q--)
			L.elements[q + 1] = L.elements[q];
		L.last++;
		L.elements[p] = x;
	}
}
template <typename elementtype>
position Locate(elementtype x, LIST L)
{
	position q;
	for (q = 1; q <= L.last; q++)
	{
		if (L.elements[q] == x)
			return q;
	}
	return L.last + 1;
}
template <typename elementtype>
elementtype Retrieve(position p, LIST L)
{
	if (p > L.last || p < 1)
		cerr << "指定元素不存在" << endl;
	else
		return L.elements[p];
}
template <typename elementtype>
void Delete(position p, LIST &L)
{
	position q;
	if (p > L.last || p < 1)
		cerr << "指定元素不存在" << endl;
	else
	{
		for (q = p; q < L.last; q++)
			L.elements[p] = L.elements[p + 1];
		L.last--;
	}
}
template <typename elementtype>
position Previous(position p, LIST L)
{
	if (p > L.last || p <= 1)
		cerr << "前驱元素不存在" << endl;
	else
		return p - 1;
}
template <typename elementtype>
position Next(position p, LIST L)
{
	if (p >= L.last || p < 1)
		cerr << "后继元素不存在" << endl;
	else
		return p + 1;
}
template <typename elementtype>
position MakeNull(LIST &L)
{
	L.last = 0;
	return L.last + 1;
}
template <typename elementtype>
elementtype First(LIST L)
{
	return L.elements[1];
}
template <typename elementtype>
elementtype End(LIST L)
{
	return L.elements[L.last];
}