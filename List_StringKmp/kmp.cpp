//@Filename:	kmp.cpp
//@Description:	KMP string match algorithm
//@Author:		Xu Jiale
//@Create Time:	2016/12/29, 21:39
//Copyright (C) 2016 HIT. All rights reserved

#include <iostream>
#include <cstring>
#define MAXLEN 100

using namespace std;

//Function:		IndexKMP
//Description:	KMP string match algorithm
//Arguments:	char *: the main string
//				char *: the pattern string
//Return:		int: the index of the first pattern string found in the main string,
//					 if failed to match, return -1

int IndexKMP(char *, char *);
//Function:		GetNext
//Description:	char *: Initialize the array "next"
//Arguments:	char *: the pattern string
//				int[]: the array "next" to be intialized
//Return:		void
void GetNext(char *, int[]);

int main()
{
	char MainString[MAXLEN];
	char PatternString[MAXLEN];
	int index;
	cout << "请输入主字符串：";
	cin >> MainString;
	cout << endl;
	cout << "请输入模式字符串：";
	cin >> PatternString;
	cout << endl;
	index = IndexKMP(MainString, PatternString);
	if (index >= 0)
		cout << "匹配成功！模式串在主串中的位置为：" << index << endl;
	else
		cout << "匹配失败！" << endl;
	cout << endl;
	system("pause");
	return 0;
}

int IndexKMP(char *main, char *pattern)
{
	//i:	the cursor of the main string during the match
	//		always point to the character being compared in the main string
	//j:	the cursor of the pattern string during the match
	//		always point to the character being compared in the pattern string
	//Next:	the array "next" of the pattern string
	int i = 0;
	int j = 0;
	int Next[MAXLEN];

	//Intialize the array "next" of the pattern string
	GetNext(pattern, Next);
	//Loop until having reached the end of the main or the pattern string
	while (i < (int)strlen(main) && j < (int)strlen(pattern))
	{
		//If j = -1, it means we should compare the next character of the main
		//string with the head character of the pattern string, so ++i and ++j
		//If main[i] = main[j], it means the current match succeed, so we should
		//compare the next character of the main string with the next character
		//of the pattern string, so ++i and ++j
		if (j == -1 || main[i] == pattern[j])
		{
			++i;
			++j;
		}
		//If the current match fail, we should compare the current character of
		//the main string with the "Next[j]" character of the pattern string, so
		//make j = Next[j]
		else
			j = Next[j];
		//If j has reached the end of the pattern string, then the match succeed,
		//return the index of the first character
		if (j == (int)strlen(pattern))
			return (i - (int)strlen(pattern));
	}
	//If the match fail eventually, return -1
	return -1;
}
void GetNext(char *string, int next[])
{
	int i = 0;
	int j = -1;
	next[0] = -1;
	while (i < (int)strlen(string) - 1)
	{
		if (j == -1 || string[i] == string[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
}