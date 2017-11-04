//@Filename:	bubblesort.cpp
//@Function:	Bubblesort algorithm
//@Author:		Xu Jiale
//@Create Time: 2016/12/22, 12:33
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXSIZE 100

using namespace std;

//Function:		BubbleSort
//Description:	The procedure of bubblesort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements in the array
//Return:		void
void BubbleSort(int[], int);

//Fucntion:		Swap
//Description:	Swap the value two elements
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
	BubbleSort(data, count);
	cout << "数组气泡排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void BubbleSort(int data[], int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > i; j--)
			if (data[j - 1] > data[j])
				Swap(data[j - 1], data[j]);
}
void Swap(int &a, int &b)
{
	if (a == b) return;
	a ^= b;
	b ^= a;
	a ^= b;
}