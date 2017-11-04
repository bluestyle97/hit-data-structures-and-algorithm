//stackshare.cpp -- 多栈共享一段空间及其删除算法
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#define N 80

using namespace std;

struct stacknode		//栈结点
{
	char data;			//数据
	int next;			//下一结点
};

void ShareStack(stacknode[]);		//函数：从文件中读取数据初始化三个栈使其共享一段存储空间
bool IsEmpty(int, stacknode[]);		//函数：判断栈是否为空
void Pop(int, stacknode[]);			//函数：弹出栈顶元素
void PrintStack(int, stacknode[]);	//函数：打印栈中元素

int main()
{
	stacknode stk[N];		//使用静态链表存储栈的信息
	char choice = ' ';		//choice：选择功能
	int number;				//number：栈的编号（1,2,3）
	while (choice != '4')
	{
		cout << endl;
		cout << "请按数字键选择功能：" << endl;		//打印菜单
		cout << "1.初始化栈元素" << endl;
		cout << "2.弹出栈顶元素" << endl;
		cout << "3.打印栈中元素" << endl;
		cout << "4.退出程序" << endl;
		cin >> choice;
		switch (choice)
		{
		case '1':		//初始化栈
			ShareStack(stk);
			cout << "栈初始化完成！" << endl;
			break;
		case '2':		//弹出所选栈的栈顶元素
			cout << "请输入您想弹出的栈编号(1,2,3)：";
			cin >> number;
			Pop(number, stk);
			break;
		case '3':		//打印栈中元素
			cout << "请输入您想打印的栈编号(1,2,3)：";
			cin >> number;
			PrintStack(number, stk);
			break;
		case '4':		//退出程序
			cout << "感谢您的使用，再见！" << endl;
			break;
		default:
			cout << "你的输入有误，请重新输入！" << endl;
		}
	}
	cin.get();
	return 0;
}

void ShareStack(stacknode stk[])
{
	char input;		//input：用于读取字符数据
	int top = 3;	//top：当前已初始化的最大栈结点下标
	for (int i = 0; i < 3; i++)		//将前三个数组成员分别作为三个栈的栈顶元素
		stk[i].next = 0;
	for (int i = N - 1; i >= 3; i--) //初始化存储空间，以最后一个元素为栈顶将栈结点链入空链
		stk[i].next = i - 1;
	stk[N - 1].next = 0;		//空栈栈顶元素的下一个结点初始化为0
	ifstream is;
	is.open("input.txt");		//打开文件
	if (!is.is_open())			//若文件打开失败
	{
		cerr << "打开文件失败！" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof() && top < N)	//从文件中读取栈的数据
	{
		is.get(input);		//从文件中读取一个字符
		stk[top].data = input;		//将读取的字符存储到存储空间内top结点处
		if ('0' <= input && input <= '9')	//若该字符是数字，则将其压入栈顶为下标0元素的栈
		{
			stk[top].next = stk[0].next;
			stk[0].next = top;
		}
		else if ('a' <= input && input <= 'z' || 'A' <= input && input <= 'Z')
		{									//若该字符是字母，则将其压入栈顶为下标1元素的栈
			stk[top].next = stk[1].next;
			stk[1].next = top;
		}
		else								//若该字符是其他符号，则将其压入栈顶为下标2元素的栈
		{
			stk[top].next = stk[2].next;
			stk[2].next = top;
		}
		top++;		//top指向下一个未初始化结点
	}
	if (top < N - 1)		//若存储空间未满，则将top所指向下一结点初始化为0，表示该结点不在任何一个栈中
		stk[top].next = 0;
	is.close();		//关闭文件
}

bool IsEmpty(int number, stacknode stk[])
{
	return stk[number].next == 0;		//判断编号为number的栈（即栈顶为number-1的栈）是否为空
}

void Pop(int number, stacknode stk[])	//弹出编号为number的栈的栈顶元素
{
	int index;							//index：存储栈顶元素结点下标
	if (IsEmpty(number - 1, stk))		//若栈已空，则不弹栈
	{
		cout << "该栈已空！" << endl;
		return;
	}
	index = stk[number - 1].next;		//找到栈顶元素
	stk[number - 1].next = stk[index].next;		//弹栈操作
	stk[index].next = stk[N - 1].next;			//将删除空间链入空闲链
	stk[N - 1].next = index;
	cout << "该元素已弹出！" << endl;
}

void PrintStack(int number, stacknode stk[])
{
	int pos = number - 1;		//pos：栈顶元素下标
	int count = 1;
	cout << "栈中元素如下：" << endl;
	do
	{
		pos = stk[pos].next;	//打印栈中所有元素
		if (pos != 0)
			cout << setw(2) << pos << ":" << setw(2) << stk[pos].data;
		if (count % 4 == 0)		//打印格式：下标：数据 每行输出4个栈元素
			cout << endl;
		else
			cout << "\t";
	} while (pos != 0 && count++);
	cout << endl << "栈中元素打印完毕！" << endl;
}