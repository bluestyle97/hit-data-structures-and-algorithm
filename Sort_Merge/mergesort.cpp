//@Filename:	mergesort.cpp
//@Description: Mergesort algorithm
//@Author:		Xu Jiale
//@Create Time: 2016/12/21, 21:00
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#define MAXSIZE 100

using namespace std;

//Function:		MergeSort
//Description:	The main procedure of mergesort algorithm
//Arguments:	int[]: the array to be sorted
//				int: the number of the elements in the array
//Return:		void
void MergeSort(int[], int);

//Function:		MSort
//Description:	The procedure of mergesort
//Arguments:	int[]: the array to be sorted
//				int[]: the temporary array
//				int: the original index of the array
//				int: the terminal index of the array
//Return:		void
void MSort(int[], int[], int, int);

//Function:		Merge
//Description:	Merge two arrays
//Arguments:	int[]: the array to be sorted
//				int[]: the temporary array
//				int: the original index of the first array
//				int: the original index of the second array
//				int: the terminal index of the second array
//Return:		void
void Merge(int[], int[], int, int, int);

int main()
{
	int data[MAXSIZE];
	int input;
	int count = 0;
	cout << "请输入数组元素：";
	while (cin >> input)
		data[count++] = input;
	cin.clear();
	MergeSort(data, count);
	cout << "数组归并排序之后的结果为：";
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}

void MergeSort(int data[], int n)
{
	//Allocate space for temporary array
	int *tmparray = new int[n];		//临时数组
	//Recursive mergesort procedure
	MSort(data, tmparray, 0, n - 1);
	//Release the space of the temporary array
	delete[] tmparray;
}
void MSort(int data[], int tmp[], int left, int right)
{
	int mid = (left + right) / 2;
	if (left < right)
	{
		MSort(data, tmp, left, mid);
		MSort(data, tmp, mid + 1, right);
		Merge(data, tmp, left, mid + 1, right);
	}
}
void Merge(int data[], int tmp[], int lpos, int rpos, int rightend)
{
	//leftend:		the terminal index of the first array
	//tmppos:		a cursor
	//elementnum:	the number of elements in both arrays
	int leftend, tmppos, elementnum;

	leftend = rpos - 1;
	tmppos = lpos;
	elementnum = rightend - lpos + 1;
	//Choose the bigger elements from the two arrays adn copy it to the temporary
	//array, until one array has reached the end
	while (lpos <= leftend && rpos <= rightend)
		tmp[tmppos++] = (data[lpos] <= data[rpos]) ? data[lpos++] : data[rpos++];
	//Then copy the remaining  elements of the other array to the temporary array
	while (lpos <= leftend)
		tmp[tmppos++] = data[lpos++];
	while (rpos <= rightend)
		tmp[tmppos++] = data[rpos++];
	//Copy the temporary array to the data array
	for (int i = 0; i < elementnum; i++, rightend--)
		data[rightend] = tmp[rightend];
}