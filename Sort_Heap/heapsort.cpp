//@Filename:	heapsort.cpp
//@Description: Heapsort algorithm
//@Author:		Xu Jiale
//@Create Time: 2016/12/20, 22:32
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXSIZE 100
#define LeftChild(i) (2 * (i) + 1)

using namespace std;

//Function:		Heapsort
//Description:	Heapsort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of elements in the array
//Return:		void
void HeapSort(int[], int);

//Fuction:		PushDown
//Description:	Adjust the maximum heap
//Arguments:	int[]: the array to be sorted
//				int: the index of the heap's root
//				int: the number of elements in the array
//Return:		void
void PushDown(int[], int, int);

//Function:		Swap
//Description:	Swap the value of two elements
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
	HeapSort(data, count);
	cout << "数组堆排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void PushDown(int data[], int i, int n)
{
	int child, tmp;

	//Percolate down
	for (tmp = data[i]; LeftChild(i) < n; i = child)
	{
		child = LeftChild(i);
		//Compare the left child with the right child and choose the bigger one
		if (child != n - 1 && data[child + 1] > data[child])
			child++;
		//If the parent record is smaller than its child record, the child record moves upward
		if (tmp < data[child])
			data[i] = data[child];
		else
			break;
	}
	//Put the original root record in the final empty child node
	data[i] = tmp;
}
void HeapSort(int data[], int n)
{
	int i, tmp;

	//Build maximum heap, arrage the heaps whose roots are n/2,n/2-1...2,1,0 in order
	for (i = n / 2; i >= 0; i--)
		PushDown(data, i, n);
	//DeleteMax
	for (i = n - 1; i > 0; i--)
	{
		Swap(data[0], data[i]);
		PushDown(data, 0, i);		//Adjust the heap to make it a maximum heap again
	}
}
void Swap(int &a, int &b)
{
	if (a == b) return;
	a ^= b;
	b ^= a;
	a ^= b;
}