// poly.cpp -- 多项式乘法
#include <iostream>

using namespace std;

struct polynode			//结构：多项式中的单项式节点类型
{
	int coef;			//结构成员coef：单项式的系数
	int exp;			//结构成员exp：单项式的次数
	polynode *link;		//结构成员link:指向下一节点位置的指针
};
typedef polynode * poly;		//类型poly：多项式链表
typedef polynode * pointer;		//类型pointer：指向链表节点的指针

pointer Attach(int, int, pointer);		//函数：创建一个单项式节点，将其链接到参数指针之后，并返回指向该节点的指针
void Initialize(poly);					//函数：初始化多项式链表
pointer MultiMono(pointer, pointer);	//函数：计算两个单项式相乘的结果，为其生成一个节点，并返回指向该节点的指针
poly Multiply(poly, poly);				//函数：将两个多项式逐项相乘，结果保存到链表中，并返回指向该链表的指针
pointer Delete(poly, pointer);			//函数：删除多项式链表中参数指针所指向的元素
poly Simplify(poly);					//函数：化简多项式，合并同类项
void PrintPoly(poly);					//函数：打印多项式

int main()
{
	poly f = new polynode;				//f和g：待相乘的两个多项式
	poly g = new polynode;
	poly result;						//result：存储f和g相乘的结果
	Initialize(f);						//初始化多项式f和g
	Initialize(g);
	result = Multiply(f, g);			//计算多项式乘积
	cout << endl;
	cout << "多项式相乘的结果化简前为：" << endl;
	PrintPoly(result);
	result = Simplify(result);
	cout << "多项式相乘的结果化简后为：" << endl;
	PrintPoly(result);
	cin.get();
	cin.get();
	return 0;
}

pointer Attach(int c, int e, pointer d)
{
	pointer q = new polynode;
	q->coef = c;
	q->exp = e;
	q->link = NULL;
	d->link = q;		//追加结点q至d指针指向的结点之后
	return q;			//返回链表末节点
}

void Initialize(poly f)
{
	pointer p = new polynode;
	int c, e;
	int count = 1;		//变量count：当前正在输入的项数
	cout << "==========初始化多项式==========" << endl;
	cout << "<<<提示：输入一对0表示结束输入>>>" << endl;
	cout << "请输入第" << count << "项的系数和次数（用空格分隔）：";
	cin >> c >> e;
	f->coef = c;		//初始化多项式链表头结点
	f->exp = e;
	f->link = NULL;
	p = f;
	count++;
	while (true)
	{
		cout << "请输入第" << count << "项的系数和次数（用空格分隔）：";
		cin >> c >> e;
		if (c == 0 && e == 0)		//输入一对0表示输入结束，退出循环
			break;
		p = Attach(c, e, p);		//向多项式链表末尾追加新节点，使p指向新的末结点
		count++;
	}
}

pointer MultiMono(pointer a, pointer b)
{
	pointer p = new polynode;		//指针p：指向单项式a和b相乘所得结果
	p->coef = a->coef * b->coef;	//两个单项式相乘，系数相乘
	p->exp = a->exp + b->exp;		//两个单项式相乘，次数相加
	p->link = NULL;					//指针成员初始化为空
	return p;						//返回指向单项式相乘结果的指针
}

poly Multiply(poly f, poly g)
{
	pointer a = f, b = g->link;
	int c, e;
	pointer p;
	pointer result = MultiMono(f, g);		//初始化乘积多项式链表头结点
	p = result;
	while (a != NULL)				//两个多项式中的单项式逐项相乘
	{
		while (b != NULL)
		{
			c = a->coef * b->coef;
			e = a->exp + b->exp;
			p = Attach(c, e, p);	//各项相乘结果依次链接
			b = b->link;
		}
		b = g;
		a = a->link;
	}
	return result;					//返回乘积结果链表头指针
}

pointer Delete(poly f, pointer p)
{
	pointer pos = f;
	pointer s = new polynode;
	s = f;
	if (p == f)						//若删除头结点，则返回新的头结点
	{
		s = s->link;
		return s;
	}
	while (s->link != p && s != NULL)		//查找待删除的结点位置
		s = s->link;
	s->link = p->link;				//删除结点p
	return pos;						//返回头指针
}

poly Simplify(poly f)
{
	pointer p, q, head;
	head = p = f;					//p指针首先指向第一项
	while (!(p == NULL || p->link == NULL))
	{
		q = p->link;				//q指向p后面的一项
		while (q != NULL)
		{
			if (q->exp == p->exp)			//若q项的次数与p项相同，则合并p和p项，并删除q项
			{
				p->coef = p->coef + q->coef;
				head = Delete(f, q);
				q = q->link;		//q向后移动，继续与p比较判断是否能合并
				continue;
				if (p->coef == 0)	//若p项系数为0，删除p项
					head = Delete(f, p);
			}
			else q = q->link;
		}
		p = p->link;				//p向后移动
	}
	return head;					//返回头指针
}

void PrintPoly(poly f)				//打印多项式
{
	pointer p = f;
	while (p != NULL)
	{
		if (p->coef > 0 && p != f)
		{
			if (p->exp == 0)
				cout << "+" << p->coef;
			else
				cout << "+" << p->coef << "x^" << p->exp;
		}
		else if (p->coef < 0)
		{
			if (p->exp == 0)
				cout << p->coef;
			else
				cout << p->coef << "x^" << p->exp;
		}
		else
			if (p->exp == 0)
				cout << p->coef;
			else
				cout << p->coef << "x^" << p->exp;
		p = p->link;
	}
	cout << endl;
}
