//judgebtree.cpp -- 判断是否为完全二叉树
#include <iostream>
#include <queue>

using namespace std;

struct node						//二叉树结点
{
	char data;					//数据
	struct node * lchild;		//左儿子
	struct node * rchild;		//右儿子
};
typedef struct node * btree;	//二叉树

btree CreateBtree(void);		//函数：输入先序序列生成二叉树
bool JudgeBtree(btree);			//函数：判断二叉树是否为完全二叉树
void PreOrder(btree);			//函数：先序遍历二叉树
void InOrder(btree);			//函数：中序遍历二叉树
void PostOrder(btree);			//函数：后续遍历二叉树

int main()						//主函数
{
	cout << " ---------------------------------------- " << endl;
	cout << "|       欢迎使用完全二叉树判定系统       |" << endl;
	cout << " ---------------------------------------- " << endl;
	char choice = ' ';
	btree T = new node;
	while (choice != '6')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|       请按数字键选择相应功能：           |" << endl;
		cout << "|       1.建立二叉树（使用其他功能前必选） |" << endl;
		cout << "|       2.判定完全二叉树                   |" << endl;
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
			T = CreateBtree();
			cout << "********二叉树建立完成！********" << endl;
			break;
		case '2':
			if (JudgeBtree(T))
				cout << "该二叉树是一个完全二叉树！" << endl;
			else
				cout << "该二叉树不是一个完全二叉树！" << endl;
			break;
		case '3':
			PreOrder(T);
			break;
		case '4':
			InOrder(T);
			break;
		case '5':
			PostOrder(T);
			break;
		case '6':
			cout << endl;
			
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|       您的输入有误，请重新输入！         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	cin.get();
	return 0;
}

btree CreateBtree(void)			//递归建立二叉树
{
	btree t;
	char ch;
	cin >> ch;
	if (ch == '#')				//输入字符为#表示该位置处结点为空
		return NULL;
	else
	{
		t = new node;			//根节点初始化
		t->data = ch;
		t->lchild = CreateBtree();
		t->rchild = CreateBtree();
	}
	return t;
}

bool JudgeBtree(btree T)		//层序遍历判断二叉树是否为完全二叉树
{
	bool flag = false;			//flag：判断是否找到空结点
	btree p;
	queue<btree> Q;
	if (T == NULL)				//若二叉树为空，则它是完全二叉树
		return true;
	Q.push(T);
	while (!Q.empty())		//若队列不为空
	{
		p = Q.front();
		Q.pop();
		if (p == NULL)			//若层序遍历到空结点，则将flag标记为true
			flag = true;
		else if (flag)			//若已经出现空结点，则判断该结点之后是否都是空结点，若找到非空结点，则该二叉树不是完全二叉树
			return false;
		else					//若当前结点非空，且之前没有找到空结点，则将该节点的左右儿子依次入队，供层序遍历使用
		{
			Q.push(p->lchild);
			Q.push(p->rchild);
		}
	}
	return true;				//循环完成，证明该二叉树是完全二叉树
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