//@Filename:	insertsort.cpp
//@Description:	Insertionsort algorithm
//@Author:		Xu Jiale
//@Create Time: 2016/12/20, 19:33
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXSIZE 100

using namespace std;

//Function:		InsertSort
//Description:	Insertion sort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements in the array
//Return:		void
void InsertSort(int[], int);

int main()
{
	int data[MAXSIZE];
	int input;
	int count = 0;
	cout << "请输入数组元素：";
	while (cin >> input)
		data[count++] = input;
	cin.clear();
	InsertSort(data, count);
	cout << "数组插入排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
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
