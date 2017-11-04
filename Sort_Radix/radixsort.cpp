//@Filename:	radixsort.cpp
//@Description:	Radix sort algorithm
//@Author:		Xu Jiale
//@Create Time:	2016/12/22, 13:12
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#include <queue>
#define MAXSIZE 100

using namespace std;

//Function:		RadixSort
//Description:	Radix sort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements in the array
//Return:		void
void RadixSort(int[], int);

//Function:		Radix
//Description:	Calculate the radix
//Arguments:	int: the number to be calculated
//				int: the radix's serial number we want to get
//Return:		int: the radix
int Radix(int, int);

//Function:		Figure
//Description:	Calculate the biggest figure of all elements in the aray
//Arguments:	int[]: the array
//				int: the number of elements in the array
//Return:		int: the figure calculated
int Figure(int[], int);

int main()
{
	int data[MAXSIZE];
	int input;
	int count = 0;
	cout << "请输入数组元素：";
	while (cin >> input)
		data[count++] = input;
	cin.clear();
	RadixSort(data, count);
	cout << "数组基数排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void RadixSort(int data[], int n)
{
	//Qdata:	the queue which stores data
	//Q[10]:	the buckets used during the sort
	//queuedata:a temporary variable which stores an element of the queue
	//radix:	the radix of an element
	queue<int> Qdata;
	queue<int> Q[10];
	int queuedata, radix;
	int figure = Figure(data, n);

	//Initialize Qdata
	for (int i = 0; i < n; i++)
		Qdata.push(data[i]);
	//Loop figure times, and the sort will be finished
	for (int i = 0; i < figure; i++)
	{
		while (!Qdata.empty())
		{
			queuedata = Qdata.front();
			Qdata.pop();
			radix = Radix(queuedata, i + 1);
			Q[radix].push(queuedata);
		}
		for (int j = 0; j < 10; j++)
			while (!Q[j].empty())
			{
				queuedata = Q[j].front();
				Q[j].pop();
				Qdata.push(queuedata);
			}
	}
	//Write sorted records back to the array
	for (int i = 0; i < n && !Qdata.empty(); i++)
	{
		queuedata = Qdata.front();
		Qdata.pop();
		data[i] = queuedata;
	}
}
int Radix(int number, int p)
{
	int power = 1;
	for (int i = 1; i < p; i++)
		power *= 10;
	return (number / power) % 10;
}
int Figure(int data[], int n)
{
	int figure = 0;
	int max = data[0];
	for (int i = 1; i < n; i++)
		if (data[i] > max)
			max = data[i];
	do
	{
		max /= 10;
		figure++;
	} while (max > 0);
	return figure;
}