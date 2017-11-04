// findloop.cpp -- 判断链表中是否有环
#include <iostream>

using namespace std;

struct node						//结点类型
{
	int data;					//数据
	node *next;					//指向下一结点的指针
};
typedef node * LIST;			//链表类型
typedef node * pointer;			//结点指针类型

pointer Append(int, pointer);	//函数：向链表末尾添加结点
void Initialize(LIST);			//函数：初始化链表
void Findloop(LIST);			//函数：判断链表中是否有环

int main()
{
	LIST l = new node;
	Initialize(l);
	Findloop(l);
	cin.get();
	cin.get();
	return 0;
}

pointer Append(int x, pointer p)
{
	pointer q = new node;
	q->data = x;
	q->next = NULL;			//链表末节点的next成员指向空指针
	p->next = q;			//在链表末尾追加节点
	return q;				//返回指向新添加结点的指针
}
void Initialize(LIST l)
{
	pointer p = new node;
	pointer q = new node;
	int d;
	int choice;				//变量choice：供用户选择环的入口位置
	cout << "请输入各结点的数据，输入-1代表结束输入：" << endl;			//输入环的各结点数据
	cin >> d;
	l->data = d;			//初始化链表头结点
	l->next = NULL;
	p = q = l;
	while (true)			//初始化其他结点
	{
		cin >> d;
		if (d == -1)
			break;
		p = Append(d, p);
	}
	cout << "您希望将第几个结点设为环的入口？（输入0则不生成环）" << endl;
	cin >> choice;
	if (choice != 0)		//设置环的入口结点
	{
		for (int i = 1; i < choice; i++)
			q = q->next;
		p->next = q;		//将链表的末结点指向环的入口结点
	}
	cout << "链表初始化完成！" << endl;
}
void Findloop(LIST l)
{
	pointer p = new node;
	pointer q = new node;
	int m = 0, n = 0;					//变量m用于记录计算环的长度，变量n用于计算环的入口结点与链表头结点的距离
	p = q = l;							//初始化两个指针并使其指向头结点
	while (p != NULL && q != NULL)
	{
		p = p->next;					//p指针每向后走一步，q指针向后走两步
		q = q->next->next;
		if (p == q)						//若移动若干次后p和q指针指向同一结点，则说明该链表中有环
		{
			cout << "该链表中有环！" << endl;
			p = p->next;				//p和q移动到同一位置后，q指针不动，p指针向后移动，且每移动一步m值加1
			m++;
			while (p != q)				//当p再次与q指向同一结点时，m的值即是环的长度
			{
				p = p->next;
				m++;
			}
			cout << "环的长度为" << m << endl;
			p = q = l;							//将p和q指针复位至链表头结点
			for (int i = 0; i < m; i++)			//将q指针向后移动到与头结点相距环的长度的位置处
				q = q->next;
			while (p != q)				//p和q指针同时向后移动，每移动一步n值加1
			{
				p = p->next;
				q = q->next;
				n++;
			}							//当p和q指针再次指向同一结点时，该结点就是环的入口结点，此时n值便是该结点与头结点的距离
			cout << "环的入口是链表中的第" << n + 1 << "个结点，该结点的数据为" << p->data << endl;
			return;
		}
	}
	cout << "该链表中没有环！" << endl;			//循环结束，链表中不存在环
}