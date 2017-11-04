//buildbtree.cpp -- 根据二叉树的前序序列和中序序列建立二叉树
#include <iostream>
#include <string>

using namespace std;

struct btreenode			//二叉树结点
{
	char data;				//数据
	btreenode * lchild;		//左儿子
	btreenode * rchild;		//右儿子
};
typedef btreenode * btree;	//二叉树

struct set					//结构体：5元组，用于非递归建立二叉树
{
	btree parent;			//目前要建的根结点的父亲
	bool mark;				//标记目前子树根结点是parent的左儿子还是右儿子
	int pre;				//当前要建的子树的先序序列的起始标号
	int mid;				//当前要建的子树的中序序列的起始标号
	int len;				//序列长度
};

struct stacknode			//栈结点
{
	set * node;
	stacknode * next;
};
typedef stacknode * Stack;		//栈
typedef stacknode * pointer;	//栈结点指针

Stack CreateStack(void);	//函数：创建一个空栈
bool IsEmpty(Stack);		//函数：判断栈是否为空
void MakeEmpty(Stack);		//函数：清空栈
void Pop(Stack);			//函数：弹栈
void Push(set *, Stack);	//函数：压栈
set * Top(Stack);			//函数：返回栈顶元素

void BuildBtreeRec(string, string, btree &);	//函数：递归还原二叉树
btree BuildBtree(string, string, int);			//函数：非递归还原二叉树
void PreOrderRec(btree);	//函数：先序遍历二叉树
void InOrderRec(btree);		//函数：中序遍历二叉树
void PostOrderRec(btree);	//函数：后序遍历二叉树

int main()
{
	cout << " ------------------------------------------ " << endl;
	cout << "|         欢迎使用二叉树还原程序！         |" << endl;
	cout << " ------------------------------------------ " << endl;
	string preorder, inorder;
	cout << "请输入二叉树的先序遍历序列：";
	cin >> preorder;
	cout << "请输入二叉树的中序遍历序列：";
	cin >> inorder;
	btree result = new btreenode;
	char choice = ' ';
	while (choice != '6')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|        请按数字键选择相应功能            |" << endl;
		cout << "|        1.递归还原二叉树                  |" << endl;
		cout << "|        2.非递归还原二叉树                |" << endl;
		cout << "|        3.先序遍历二叉树                  |" << endl;
		cout << "|        4.中序遍历二叉树                  |" << endl;
		cout << "|        5.后序遍历二叉树                  |" << endl;
		cout << "|        6.退出程序                        |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "         请输入您的选择：";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':
			BuildBtreeRec(preorder, inorder, result);
			cout << "二叉树已还原！" << endl;
			break;
		case '2':
			result = BuildBtree(preorder, inorder, (int)preorder.size());
			cout << "二叉树已还原！" << endl;
			break;
		case '3':
			PreOrderRec(result);
			break;
		case '4':
			InOrderRec(result);
			break;
		case '5':
			PostOrderRec(result);
			break;
		case '6':
			cout << " ------------------------------------------ " << endl;
			cout << "|         感谢使用二叉树还原程序！         |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:
			cout << " ------------------------------------------ " << endl;
			cout << "|         您的输入有误，请重新输入！       |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	cin.get();
	cin.get();
	return 0;
}

Stack CreateStack(void)
{
	Stack s = new stacknode;
	if (s == NULL)
		cerr << "内存空间已满！" << endl;
	else
		s->next = NULL;
	return s;
}

bool IsEmpty(Stack s)
{
	return s->next == NULL;
}

void MakeEmpty(Stack s)
{
	if (s->next != NULL)
		while (!IsEmpty(s))
			Pop(s);
}

void Pop(Stack s)
{
	pointer p = new stacknode;
	if (!IsEmpty(s))
	{
		p = s->next;
		s->next = p->next;
		delete p;
	}
}

void Push(set *t, Stack s)
{
	pointer p = new stacknode;
	p->node = t;
	p->next = s->next;
	s->next = p;
}

set *Top(Stack s)
{
	if (!IsEmpty(s))
		return s->next->node;
}

void BuildBtreeRec(string pre, string in, btree &t)		//递归还原二叉树
{
	t = new btreenode;
	if (pre.size() == 0)
	{
		t = NULL;
		return;
	}
	t->data = pre[0];
	int index = 0;
	t->lchild = NULL;
	t->rchild = NULL;
	while (index < (int)in.size() && in[index] != pre[0])
		index++;
	int left_length = index;
	int right_length = pre.size() - index - 1;
	if (left_length > 0)
		BuildBtreeRec(pre.substr(1, left_length), in.substr(0, left_length), t->lchild);
	if (right_length > 0)
		BuildBtreeRec(pre.substr(1 + left_length, right_length), in.substr(1 + left_length, right_length), t->rchild);
}

btree BuildBtree(string pre, string in, int n)
{
	btree parent, head;
	bool flag;
	int prestart, midstart, length;
	Stack stk = CreateStack();
	head = new btreenode;				//开辟一个头结点，其左孩子结点指向二叉树根结点
	head->lchild = head->rchild = NULL;
	set s = { head, false, 0, 0, n };
	Push(&s, stk);						//五元组入栈
	while (!IsEmpty(stk))				//若栈不空，循环建树
	{
		set *tmp = Top(stk);
		tmp->parent = new btreenode;
		Pop(stk);			//栈顶五元组出栈
		if (tmp->len > 0)	//子树不空，则建立子树根结点
		{
			if (tmp->mark == false)			//当前根结点是parent的左孩子
			{
				tmp->parent->lchild = new btreenode;
				tmp->parent->lchild->data = pre[tmp->pre];
				tmp->parent->lchild->lchild = NULL;
				tmp->parent->lchild->rchild = NULL;
				int k = 0;
				while (k < tmp->len)
				{
					if (pre[tmp->pre] == in[tmp->mid + k])
						break;
					k++;
				}
				set s1 = { tmp->parent->lchild, false, tmp->pre + 1, tmp->mid, k };
				set s2 = { tmp->parent->rchild, true, tmp->pre + k + 1, k + 1, tmp->len - k - 1 };
				Push(&s1, stk);
				Push(&s2, stk);
			}
			else							//当前根结点是parent的右孩子
			{
				tmp->parent->rchild = new btreenode;
				tmp->parent->rchild->data = pre[tmp->pre];
				tmp->parent->rchild->lchild = NULL;
				tmp->parent->rchild->rchild = NULL;
				int k = 0;
				while (k < tmp->len)		//若相等，记载中序序列中找到根节点的位置，跳出循环
				{
					if (pre[tmp->pre] == in[tmp->mid + k])
						break;
					k++;
				}
				set s1 = { tmp->parent->lchild, false, tmp->pre + 1, tmp->mid, k };		//把当前子树的根结点的左子树的信息入栈
				set s2 = { tmp->parent->rchild, true, tmp->pre + k + 1, k + 1, tmp->len - k - 1 };		//把当前子树的根结点的右子树的信息入栈
				Push(&s1, stk);
				Push(&s2, stk);
			}
		}
	}
	return head->lchild;		//返回头结点的左孩子指针，即二叉树的跟结点指针
}

void PreOrderRec(btree t)
{
	if (t != NULL)
	{
		cout << t->data;
		PreOrderRec(t->lchild);
		PreOrderRec(t->rchild);
	}
}

void InOrderRec(btree t)
{
	if (t != NULL)
	{
		InOrderRec(t->lchild);
		cout << t->data;
		InOrderRec(t->rchild);
	}
}

void PostOrderRec(btree t)
{
	if (t != NULL)
	{
		PostOrderRec(t->lchild);
		PostOrderRec(t->rchild);
		cout << t->data;
	}
}