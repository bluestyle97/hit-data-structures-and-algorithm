//@Filename:	expression.cpp
//@Description:	Transform expressions by stack
//@Author:		Xu Jiale
//@Last Modify:	2016/01/18, 15:07
//Copyright (C) 2017 HIT. All rights reserved

#include <iostream>
#include <cmath>
#include <cstring>
#define MAXLEN 100

using namespace std;

//Struct:		node
//Description:	The node of stack
//Members:		bool: mark the data type of the node(true-double, false-char)
//				union: anonymous union
//				node *: the linked node
struct node
{
	bool flag;
	union
	{
		double Data;
		char Operator;
	};
	node * next;
};

//The pointer of a node
typedef node * Pointer;
//Stack
typedef node * Stack;

//Function:		CreateStack
//Description:	Create a new empty stack
//Arguments:	void
//Return:		Stack: the top pointer of a stack
Stack CreateStack(void);
//Function:		IsEmpty
//Description:	Judge whether a stack is empty or not
//Arguments:	Stack: the stack to be judged
//Return:		bool: the judge result
bool IsEmpty(Stack);
//Function:		MakeEmpty
//Description:	Clear a empty
//Arguments:	Stack: the stack to be cleared
//Return:		void
void MakeEmpty(Stack);
//Function:		Pop
//Description:	Delete the stack's top
//Arguments:	Stack: the stack to be modified
//Return:		void
void Pop(Stack);
//Function:		Pushdata
//Description:	Push a double-type data into the stack
//Arguments:	double: the data to be pushed
//				stacked: the stack
//Return:		void
void Pushdata(double, Stack);
//Fucntion:		Pushchar
//Description:	Push a char-type data into the stack
//Arguments:	char: the data to be pushed
//				Stack: the stack
//Return:		void
void Pushchar(char, Stack);
//Function:		Topdata
//Description:	Return the double-type data of the stack top
//Arguments:	Stack: the stack
//Return:		double: the double-type data
double Topdata(Stack);
//Fucntion:		Topchar
//Description:	Return the char-type data of the stack top
//Arguments:	Stack: the stack
//Return:		char: the char-type data
char Topchar(Stack);
//Function:		Calculate
//Description:	Calculate the value of theb expression
//Arguments:	Stack: the stack which stores the expression
//Return:		void
void Calculate(Stack);
//Function:		ToPostfix
//Description:	Transform infix expression into postfix expression
//Arguments:	char[]: inputed infix expression
//Return:		Stack: a stack which stores the transformed postfix expression
Stack ToPostfix(char[]);
//Function:		RevStack
//Description:	Reverse the elements in a stack
//Arguments:	Stack: the stack to be reversed
//Return:		Stack: the reversed stack
Stack RevStack(Stack);
//Function:		PrintStack
//Description:	Print the elements in a stack
//Arguments:	Stack: the stack to be printed
//Return:		void
void PrintStack(Stack);	
//Function:		Compare
//Description:	Compare the priority of operators
//Arguements:	char: the first operator
//				char: the second operator
//Return:		bool: the compare result
bool Compare(char, char);
//Function:		JudgeOpt
//Description:	Judge whether an operator is legal
//Arguemnts:	char: the operator to be judged
//Return:		bool: the judge result
bool JudgeOpt(char);
//Function:		Factorial
//Description:	Calculate the factorial of an integer
//Arguments:	int: the integer to be calculated
//Return:		int: the result
int Factorial(int);

int main()
{
	char s[MAXLEN];				//字符数组：用于读取输入
	Stack stk = CreateStack();	//创建一个空栈
	while (true)
	{
		cout << "请输入表达式（输入q退出）：" << endl;
		fgets(s, MAXLEN, stdin);//输入中缀表达式
		if (s[0] == 'q')		//若输入'q'则退出
			break;
		stk = ToPostfix(s);		//将中缀表达式转化为后缀表达式
		cout << "该表达式的后缀表达式为：";
		PrintStack(stk);		//打印后缀表达式内容
		Calculate(stk);			//计算表达式的值并输出
	}
	MakeEmpty(stk);				//将栈清空
	return 0;
}

Stack CreateStack(void)			//创建一个空栈
{
	Stack S = new node;
	if (S == NULL)
		cerr << "内存空间已满！" << endl;
	S->next = NULL;
	return S;
}

bool IsEmpty(Stack S)			//判断栈是否为空
{
	return S->next == NULL;
}

void MakeEmpty(Stack S)			//清空栈
{
	if (S == NULL)
		cerr << "空栈！" << endl;
	else
		while (!IsEmpty(S))
			Pop(S);
}

void Pop(Stack S)				//弹栈
{
	Pointer p = new node;
	if (IsEmpty(S))
		cerr << "空栈！" << endl;
	else
	{
		p = S->next;
		S->next = p->next;
		delete p;
	}
}

void Pushdata(double x, Stack s)
{
	Pointer p = new node;
	p->flag = true;
	p->Data = x;
	p->next = s->next;
	s->next = p;
}

void Pushchar(char c, Stack s)
{
	Pointer p = new node;
	p->flag = false;
	p->Operator = c;
	p->next = s->next;
	s->next = p;
}

double Topdata(Stack s)
{
	if (!IsEmpty(s))
		return s->next->Data;
}

char Topchar(Stack s)
{
	if (!IsEmpty(s))
		return s->next->Operator;
}

void Calculate(Stack s)				//计算后缀表达式的值
{
	Stack result = CreateStack();	//用于存储计算结果的栈
	Pointer p = new node;
	char opt;						//操作符
	double numa, numb;				//操作数
	p = s->next;
	while (p != NULL)
	{
		if (p->flag == true)		//若栈顶元素为double型操作数，则直接将其压入栈result中
			Pushdata(p->Data, result);
		else						//若栈顶元素为char型操作符
		{
			opt = p->Operator;
			numb = Topdata(result); //从栈result中弹出栈顶的两个操作数
			Pop(result);
			numa = Topdata(result);
			Pop(result);
			switch (opt)			//根据操作符类型判断进行何种运算，并将计算结果压入栈result中
			{
			case '+':
				Pushdata(numa + numb, result);
				break;
			case '-':
				Pushdata(numa - numb, result);
				break;
			case '*':
				Pushdata(numa * numb, result);
				break;
			case '/':
				Pushdata(numa / numb, result);
				break;
			case '%':
				if (fabs(numa - (int)numa) < 1e-5 && fabs(numb - (int)numb) < 1e-5)
					Pushdata((int)numa % (int)numb, result);
				else
					cout << "小数不能进行求余运算！" << endl;
				break;
			case '^':
				Pushdata(pow(numa, numb), result);
				break;
			default:
				cout << "遇到无法识别的操作符！" << endl;
			}
		}
		p = p->next;
	}
	cout << "该表达式的值为：" << result->next->Data << endl;	//最终result栈顶元素就是表达式的值，将其输出
}

Stack ToPostfix(char s[])			//中缀表达式转化为后缀表达式
{
	Stack result = CreateStack();	//创建用于存储转化结果的空栈
	Stack opt = CreateStack();		//创建用于存储操作符的空栈
	int index = 0;					//索引：标识本轮解析的起点
	int cursor = 0;					//游标：用于解析输入字符串
	int pos;						//用于判断小数部分数位的游标
	bool flg, sgn;					//布尔型变量flg：用于判断当前解析出的类型，true为操作数，false为操作符
									//布尔型变量sgn：用于判断操作数的符号，true为正，false为负
	double num;						//double型num：用于存储解析出的操作数
	while (index < (int)strlen(s) - 1)	//输入字符串的解析
	{
		num = 0;					//各变量的初始化
		flg = false;
		sgn = true;
		if (s[cursor] == '-' && (0 == cursor || JudgeOpt(s[cursor - 1])))	//判断操作数是否为负
		{
			sgn = false;
			cursor++;
		}
		while ('0' <= s[cursor] && s[cursor] <= '9')	//解析操作数的整数部分，将其存入num
		{
			flg = true;
			num = num * 10 + s[cursor] - '0';
			cursor++;
		}
		if (s[cursor] == '.')		//解析操作数的小数部分，将其存入num
		{
			pos = cursor;
			cursor++;
			while ('0' <= s[cursor] && s[cursor] <= '9')
			{
				num += ((s[cursor] - '0') * 1.0 / pow(10, cursor - pos));
				cursor++;
			}
		}
		if (flg == true && s[cursor] == '!')	//若解析出操作数且检测到!运算符，则将操作数转化为它的阶乘
		{
			if (fabs(num - (int)num) < 1e-5)	//判断操作数是否为整数
				num = Factorial((int)num);
			cursor++;
		}
		if (sgn == false)			//若操作数符号被标识为负，则将操作数取反
			num = -num;
		if (flg == true)
			Pushdata(num, result);	//将解析出的操作数压入栈result
		else if (s[cursor] == ' ')	//若遇到空格字符则直接跳过
			cursor++;
		else						//若当前解析处不是操作数
		{
			if (IsEmpty(opt))		//若操作符栈opt为空，则直接将当前位置处的操作符压入其中
				Pushchar(s[cursor], opt);
			else					//若操作符栈opt不为空
			{
				if (s[cursor] == ')')	//当遇到右括号时，将栈opt中的操作符逐个弹出并压入result栈中，直到左括号被弹出为止
				{
					while (Topchar(opt) != '(')
					{
						Pushchar(Topchar(opt), result);
						Pop(opt);
					}
					Pop(opt);
				}
				else
				{
					while (Compare(Topchar(opt), s[cursor]))	//比较操作符的优先级，弹出opt栈中的操作符并压入result栈，直到遇到比当前待处理操作符优先级低的操作符为止
					{
						Pushchar(Topchar(opt), result);
						Pop(opt);
					}
					Pushchar(s[cursor], opt);	//最后压入当前待处理操作符
				}
			}
			cursor++;
		}
		index = cursor;		//将下轮解析字符串的起点设为当前游标位置
	}
	while (!IsEmpty(opt))	//将opt中剩余的操作符逐个弹出并压入result栈中
	{
		Pushchar(Topchar(opt), result);
		Pop(opt);
	}
	result = RevStack(result);  //将result栈中的元素逆置
	return result;			//返回result栈顶指针
}

Stack RevStack(Stack s)		//栈的逆置操作
{
	Stack r = CreateStack();
	Pointer p = s->next;
	while (p != NULL)
	{
		if (p->flag == true)
			Pushdata(p->Data, r);
		else
			Pushchar(p->Operator, r);
		p = p->next;
	}
	return r;
}

void PrintStack(Stack s)	//打印栈中的元素
{
	Pointer p = new node;
	p = s->next;
	while (p != NULL)
	{
		if (p->flag == true)
			cout << p->Data << ' ';
		else
			cout << p->Operator << ' ';
		p = p->next;
	}
	cout << endl;
}

bool Compare(char a, char b)		//比较操作符的优先级
{
	if (a == '^' && (b == '^' || b == '*' || b == '/' || b == '%' || b == '+' || b == '-'))
		return true;
	else if ((a == '*' || a == '/' || a == '%') && (b == '+' || b == '-'))
		return true;
	else if ((a == '+' || a == '-') && (b == '+' || b == '-'))
		return true;
	else if ((a == '*' || a == '/' || a == '%') && (b == '*' || b == '/' || b == '%'))
		return true;
	else
		return false;
}

bool JudgeOpt(char c)		//判断是否为合法操作符
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
		return true;
	return false;
}

int Factorial(int n)		//整数的阶乘运算
{
	int result = 1;
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}