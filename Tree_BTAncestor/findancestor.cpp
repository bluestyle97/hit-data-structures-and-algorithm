//findancestor.cpp -- 寻找二叉树中任意两个结点的公共祖先
#include <iostream>

using namespace std;

struct btreenode					//二叉树结点
{
	char data;						//结点数据
	btreenode * lchild;				//左儿子
	btreenode * rchild;				//右儿子
	btreenode * parent;				//双亲
};
typedef btreenode * btree;			//二叉树

btree CreateBtree(void);			//函数：建立二叉树，并返回根节点指针
void PreOrder(btree);				//函数：先序遍历二叉树
void InOrder(btree);				//函数：中序遍历二叉树
void PostOrder(btree);				//函数：后续遍历二叉树
btree SearchNode(char, btree);		//函数：寻找二叉树中数据为字符c的结点，并返回其指针
btree FindAncestor(btree, btree);	//函数：寻找二叉树中两结点的最近公共祖先，并返回指针

int main()							//主程序
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       欢迎使用二叉树结点寻祖系统       |" << endl;
	cout << " ---------------------------------------- " << endl;
	btree t = new btreenode;
	btree ancestor = new btreenode;
	btree p = new btreenode;
	btree q = new btreenode;
	char choice = ' ';
	while (choice != '6')			//输入6时退出程序
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|       请按数字键选择相应功能：           |" << endl;
		cout << "|       1.建立二叉树（使用其他功能前必选） |" << endl;
		cout << "|       2.寻找两结点公共祖先               |" << endl;
		cout << "|       3.输出二叉树先序遍历序列           |" << endl;
		cout << "|       4.输出二叉树中序遍历序列           |" << endl;
		cout << "|       5.输出二叉树后序遍历序列           |" << endl;
		cout << "|       6.退出程序                         |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "        请输入您的选择：";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':
			cout << "请按先序输入各结点数据（若为空则输入#）：" << endl;
			t = CreateBtree();
			cout << "********二叉树建立完成！********" << endl;
			break;
		case '2':
			char a, b;
			cout << "请输入您想要查找的两个节点的数据：" << endl;
			cin >> a >> b;
			p = SearchNode(a, t);	//在二叉树中搜索要查找的两个结点
			q = SearchNode(b, t);
			if (p != NULL && q != NULL)		//若两个结点都查找成功，则输出他们的最近公共祖先数据
			{
				ancestor = FindAncestor(p, q);
				cout << "这两个结点最近公共祖先的数据为：" << ancestor->data << endl;
			}
			else
				cout << "您输入的节点数据有误！";
			break;
		case '3':
			PreOrder(t);
			break;
		case '4':
			InOrder(t);
			break;
		case '5':
			PostOrder(t);
			break;
		case '6':
			cout << endl;
			cout << " ------------------------------------------ " << endl;
			cout << "|       感谢使用二叉树结点寻祖系统         |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       您的输入有误，请重新输入！         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	cin.get();
	return 0;
}

btree CreateBtree(void)			//利用先序序列递归生成二叉树，并返回根结点
{
	btree t;
	char ch;
	cin >> ch;
	if (ch == '#')
		return NULL;
	else
	{
		t = new btreenode;
		t->parent = NULL;
		t->data = ch;
		t->lchild = CreateBtree();
		if (t->lchild != NULL)
			t->lchild->parent = t;
		t->rchild = CreateBtree();
		if (t->rchild != NULL)
			t->rchild->parent = t;
	}
	return t;
}

void PreOrder(btree t)
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrder(t->lchild);
		PreOrder(t->rchild);
	}
}

void InOrder(btree t)
{
	if (t != NULL)
	{
		InOrder(t->lchild);
		cout << t->data;
		InOrder(t->rchild);
	}
}

void PostOrder(btree t)
{
	if (t != NULL)
	{
		PostOrder(t->lchild);
		PostOrder(t->rchild);
		cout << t->data;
	}
}

btree SearchNode(char c, btree t)			//在二叉树t中查找数据为字符c的结点，并返回其指针
{
	btree a = NULL, b = NULL;
	if (t != NULL)
	{
		if (t->data == c)
			return t;
		else
		{
			a = SearchNode(c, t->lchild);	//先序遍历递归查找
			b = SearchNode(c, t->rchild);
			if (a == NULL && b == NULL)
				return NULL;
			else
				return (b == NULL) ? a : b;
		}
	}
	return NULL;
}

btree FindAncestor(btree p, btree q)	//查找结点p和q的最近公共祖先
{
	if (p == q)							//若p和q是同一结点，则它们的最近公共祖先就是它们本身
		return p;
	btree a = p;						//使指针a初始化指向p结点
	while (a != NULL)
	{
		btree b = q;					//使指针b初始化指向q结点
		while (a != b && b != NULL)		//b指针逐次向双亲结点移动，直到遇见a结点或到达根结点
			b = b->parent;
		if (a == b)						//若a与b指向同一结点，则搜索结束，退出循环
			break;
		else							//若b未能与a相遇，则使a指针向双亲方向移动
			a = a->parent;
	}
	return a;							//循环结束后，指针a与b指向同一结点，返回a即为p和q的最近公共祖先
}