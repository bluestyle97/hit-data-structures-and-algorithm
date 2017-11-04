//@Filename:	quicksort.cpp
//@Description:	Quicksort algorithm
//@Author:		Xu Jiale
//@Create Time: 2016/12/21, 22:11
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXSIZE 100
#define CUTOFF 3

using namespace std;

//Function:		QuickSort
//Description:	int[]: Quicksort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements int the array
//Return:		void
void QuickSort(int[], int);

//Function:		InsertSort
//Description:	int[]: Insertion sort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements in the array
//Return:		void
void InsertSort(int[], int);

//Function:		QSort
//Description:	The procedure of quicksort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the original index of the array
//				int: the terminal index of the array
//Return:		void
void QSort(int[], int, int);

//Function:		Swap
//Description:	Swap two values of elements
//Arguments:	int &: the first element
//				int &: the second element
//Return:		void
void Swap(int &, int &);

//Function:		FindPivot
//Description:	Find a new pivot from an array
//Arguments:	int[]: an array
//				int: the original index of the array
//				int: the terminal index of the array
//Return:		int: the pivot
int FindPivot(int[], int, int);

int main()
{
	int data[MAXSIZE];
	int input;
	int count = 0;
	cout << "请输入数组元素：";
	while (cin >> input)
		data[count++] = input;
	cin.clear();
	QuickSort(data, count);
	cout << "数组快速排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void QuickSort(int data[], int n)
{
	QSort(data, 0, n - 1);
}
void InsertSort(int data[], int n)
{
	int i, j, tmp;
	for (i = 1; i < n; i++)
	{
		tmp = data[i];
		for (j = i; j > 0 && data[j - 1] > tmp; j--)
			data[j] = data[j - 1];
		data[j] = tmp;
	}
}
void QSort(int data[], int left, int right)
{
	int i, j;
	int pivot;
	if (left + CUTOFF <= right)
	{
		pivot = FindPivot(data, left, right);
		i = left;
		j = right - 1;
		while (true)
		{
			while (data[++i] < pivot) {}
			while (data[--j] > pivot) {}
			if (i < j)
				Swap(data[i], data[j]);
			else
				break;
		}
		Swap(data[i], data[right - 1]);
		QSort(data, left, i - 1);
		QSort(data, i + 1, right);
	}
	//When there's only three elements to be sorted, use insertion sort
	else
		InsertSort(&data[left], right - left + 1);
}
void Swap(int &a, int &b)
{
	if (a == b) return;
	a ^= b;
	b ^= a;
	a ^= b;
}
int FindPivot(int data[], int left, int right)
{
	int mid = (left + right) / 2;

	if (data[left] > data[mid])
		Swap(data[left], data[mid]);
	if (data[left] > data[right])
		Swap(data[left], data[right]);
	if (data[mid] > data[right])
		Swap(data[mid], data[right]);
	Swap(data[mid], data[right - 1]);
	return data[right - 1];
}