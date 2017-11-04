//@Filename:	selectsort.cpp
//@Description:	Selectsort algorithm
//@Author:		Xu Jiale
//@Create Time: 2016/12/22, 12:46
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXSIZE 100

using namespace std;

//Function:		SelectSort
//Description:	Selectsort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements in the array
//Return:		void
void SelectSort(int[], int);

//Function:		Swap
//Description:	Swap two values of elements
//Arguments:	int &: the first element
//				int &: the second element
//Return:		void
void Swap(int &, int &);

int main()
{
	int data[MAXSIZE];
	int input;
	int count = 0;
	cout << "请输入数组元素：";
	while (cin >> input)
		data[count++] = input;
	cin.clear();
	SelectSort(data, count);
	cout << "数组选择排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void SelectSort(int data[], int n)
{
	//lowindex:	the index of the smallest element found by the current loop
	int lowindex;

	for (int i = 0; i < n - 1; i++)
	{
		lowindex = i;
		for (int j = i + 1; j < n; j++)		//与气泡排序区别：找到最小关键字后再进行交换，而不是发现更小关键字就直接交换
			if (data[j] < data[lowindex])
				lowindex = j;
		Swap(data[i], data[lowindex]);
	}
}
void Swap(int &a, int &b)
{
	if (a == b) return;
	a ^= b;
	b ^= a;
	a ^= b;
}