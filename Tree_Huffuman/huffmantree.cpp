//huffman.cpp -- 建立哈弗曼树并进行编码压缩
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#define N 128			//ASCII字符的个数
#define MAXLEN 30		//文件名称的最大长度

using namespace std;

//数据类型定义
struct htnode			//结构体：哈夫曼树结点
{
	char chr;			//字符
	double weight;		//权重
	int lchild;			//左儿子
	int rchild;			//右儿子
	int parent;			//双亲
};
typedef htnode huffmantree[2 * N - 1];	//结构体数组：哈夫曼树类型
struct codenode			//结构体：哈夫曼编码的存储结构
{
	char chr;			//存储被编码的字符
	char bit[N + 1];	//字符编码位串
};
typedef codenode huffmancode[N];		//结构体数组：哈夫曼编码
int leafcount = 0;		//全局变量leafcount：计算哈夫曼树中叶结点个数，即文章中出现的字符种类的个数
int nodecount = 0;		//全局变量nodecount：计算哈夫曼树中所有结点个数

						//函数定义
void InitialTree(huffmantree &);					//函数：初始化哈夫曼树（将所有结点左右儿子和双亲设为-1，权重设为0）
void InitialLeaf(char *, huffmantree &);			//函数：初始化叶结点，从文章中读取字符信息统计权重，并按顺序存入哈夫曼树数组
int CreateTree(char *, huffmantree &);				//函数：读取给定文章生成哈夫曼树，并返回根结点下标
int FindChar(char, huffmantree);					//函数：从哈夫曼树数组中寻找给定字符并返回其下标，若未找到返回-1
void FindCombineNode(int *, int *, huffmantree);	//函数：从现有哈夫曼树结点中寻找权重最小的两个结点作为合并对象
void CombineTree(int, int, huffmantree &);			//函数：将给定的两个根结点作为左右子树合并到一个新结点
void PrintTree(int, huffmantree);					//函数：打印哈夫曼树所有叶结点的字符和权重信息
void Code(huffmantree, huffmancode &);				//函数：对哈夫曼树中存储的字符进行哈夫曼编码并将结果按顺序存储到编码数组中
int SearchCode(char, huffmancode);					//函数：在哈夫曼编码数组中寻找特定字符的哈夫曼编码，并返回该字符的下标
void Compress(char *, huffmancode);					//函数：对文章逐字符进行编码压缩并写入二进制文件
void PrintCode(huffmancode);						//函数：打印字符的哈夫曼编码（可选择打印单个字符或全部字符）
void DecompressScreen(char *, int, huffmantree);	//函数：解压缩二进制文件并输出到屏幕
void DecompressFile(char *, int, huffmantree);		//函数：解压缩二进制文件并输出到一个新的文件

int main()											//主函数
{
	cout << " ------------------------------------------ " << endl;
	cout << "|     欢迎使用哈夫曼树文件编码压缩系统     |" << endl;
	cout << " ------------------------------------------ " << endl;
	huffmantree T;									//T：定义哈夫曼树
	huffmancode D;									//D：定义哈夫曼编码数组
	char *filename = new char[MAXLEN];				//filename：待读入的文件名称
	int root = 0;									//root：哈夫曼树根结点下标
	char choice = ' ';								//choice：用于功能选择
	while (choice != '7')
	{
		cout << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "|        请按数字键选择相应功能            |" << endl;
		cout << "|        1.读取文件生成哈夫曼树            |" << endl;
		cout << "|        2.输出哈夫曼树叶节点数据          |" << endl;
		cout << "|        3.编码压缩并写入文件              |" << endl;
		cout << "|        4.输出字符的哈夫曼编码结果        |" << endl;
		cout << "|        5.解码文件输出到屏幕              |" << endl;
		cout << "|        6.解码文件输出到文件              |" << endl;
		cout << "|        7.退出程序                        |" << endl;
		cout << " ------------------------------------------ " << endl;
		cout << "         请输入您的选择：";
		cin >> choice;
		cout << " ------------------------------------------ " << endl;
		switch (choice)
		{
		case '1':		//输入1：读取文件生成哈夫曼树
			cout << "请输入文本文件名（无需输入拓展名）：";
			cin >> filename;
			root = CreateTree(filename, T);
			cout << "哈弗曼树已成功生成！" << endl;
			break;
		case '2':		//输入2：输出哈夫曼树叶节点数据
			cout << "哈夫曼树叶结点的数据为：" << endl;
			PrintTree(root, T);
			break;
		case '3':		//输入3：编码压缩并写入文件
			Code(T, D);
			Compress(filename, D);
			break;
		case '4':		//输入4：输出字符的哈夫曼编码结果
			PrintCode(D);
			break;
		case '5':		//输入5：解码文件输出到屏幕
			DecompressScreen(filename, root, T);
			break;
		case '6':		//输入6：解码文件输出到文件
			DecompressFile(filename, root, T);
			break;
		case '7':		//输入7：退出程序
			cout << " ------------------------------------------ " << endl;
			cout << "|    感谢使用哈弗曼树文件编码压缩系统      |" << endl;
			cout << " ------------------------------------------ " << endl;
			break;
		default:		//输入其他数字，重新输入
			cout << " ------------------------------------------ " << endl;
			cout << "|       您的输入有误，请重新输入！         |" << endl;
			cout << " ------------------------------------------ " << endl;
		}
	}
	delete[] filename;
	return 0;
}

void InitialTree(huffmantree &T)		//函数：初始化哈夫曼树
{
	for (int i = 0; i < 2 * N - 1; i++)
	{
		T[i].weight = 0;				//将所有结点左右儿子和双亲设为-1，权重设为0
		T[i].lchild = -1;
		T[i].rchild = -1;
		T[i].parent = -1;
	}
}

void InitialLeaf(char *filename, huffmantree &T)		//函数：初始化哈夫曼树叶结点（参数1：待读入的文件名称，参数2：哈夫曼树）
{
	char *filename_txt = new char[MAXLEN];		//filename_txt：要打开的文件的全名
	strcpy(filename_txt, filename);
	strcat(filename_txt, ".txt");		//在输入的文件名后面加上拓展名“.txt”构成文件全名
	char ch;							//ch：用于从文章中读取字符
	int pos;							//pos：用于寻找特定字符在哈夫曼树中的位置
	ifstream is;
	is.open(filename_txt);				//打开待读入的文件
	if (!is.is_open())					//若打开文件失败
	{
		cerr << "未能成功打开该文件！" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())					////判断是否到达文件结尾
	{
		is.get(ch);						//从文件中读取一个字符
		pos = FindChar(ch, T);			//在哈弗曼树中搜索该字符
		if (pos >= 0)					//若搜索到该字符，则将其权重加1
			T[pos].weight = T[pos].weight + 1;
		else							//若未搜索到该字符，则在当前最后一个叶结点后面的位置新建一个叶节点存储该字符，并将权重初始化为1
		{
			T[leafcount].chr = ch;
			T[leafcount].weight = 1;
			leafcount++;				//叶结点个数增加1
			nodecount = leafcount;		//初始化叶结点过程中结点总数始终等于叶结点数
		}
	}
	is.close();							//关闭文件
}

int CreateTree(char *filename, huffmantree &T)		//函数：读取文件生成哈夫曼树（参数1：待读入的文件名称，参数2：哈夫曼树）
{
	int *a = new int;					//整数型指针a、b：用于存储当前权重最小的两个结点的下标
	int *b = new int;
	int l, r, root;						//l、f：用于存储指针a和b指向的整数下标以便进行结合 root：最终生成的哈夫曼树的根结点下标
	InitialTree(T);						//初始化哈夫曼树
	InitialLeaf(filename, T);			//初始化叶结点
	while (nodecount < 2 * leafcount - 1)		//当结点总数=2*叶结点总数-1时，说明哈夫曼树已生成完毕
	{
		FindCombineNode(a, b, T);		//寻找当前所有结点中权重最小的两个，并将其下标分别存入指针a和b指向的地址中
		l = *a;
		r = *b;
		CombineTree(l, r, T);			//对结点进行合并，生成一个新结点
	}
	delete a;							//删除指针a和b
	delete b;
	root = nodecount - 1;
	return root;						//返回根结点下标
}

int FindChar(char c, huffmantree T)		//函数：在哈弗曼树中搜索特定字符并返回其下标（参数1：待搜索字符，参数2：哈夫曼树）
{
	for (int i = 0; i < leafcount; i++)
	{
		if (T[i].chr == c)
			return i;
	}
	return -1;							//若未找到，则返回-1
}

void FindCombineNode(int *a, int *b, huffmantree T)		//函数：在当前所有结点中搜索权重最小的两个（参数1、2：指针传参以便得到下标，参数3：哈夫曼树）
{
	int mina, minb, tmp;				//mina：权重最小的结点的下标 minb：权重次小的结点的下标 temp：用于交换数据
	for (int j = 0; j < nodecount; j++)					//将mina初始化为当前哈夫曼树数组中第一个尚未被合并过的结点下标
		if (T[j].parent == -1)
		{
			mina = j;
			break;
		}
	for (int k = mina + 1; k < nodecount; k++)			//将minb初始化为当前哈夫曼树数组中第二个尚未被合并过的结点下标
		if (T[k].parent == -1)
		{
			minb = k;
			break;
		}
	if (T[mina].weight >= T[minb].weight)		//若mina的权重大于等于minb，则交换，以保证mina是最小，minb是次小
	{
		tmp = mina;
		mina = minb;
		minb = tmp;
	}
	int i = 0;
	while (i < nodecount)						//遍历哈夫曼树数组以找到权重最小的两个结点
	{
		if (T[i].parent == -1)					//判断结点是否已被合并过
		{
			if (T[i].weight <= T[mina].weight)			//若当前结点权重小于mina，则将该结点下标赋给mina
				mina = i;
			else if (T[i].weight <= T[minb].weight)		//否则若当前结点权重小于minb，则将该结点下标赋给minb
				minb = i;
			i++;
		}
		else
			i++;
	}
	*a = mina;			//遍历完成后，mina和minb就是权重最小的两个结点的下标，将其分别存储到指针a和b指向的地址
	*b = minb;
}

void CombineTree(int a, int b, huffmantree &T)		//函数：合并结点（参数1:、2：待合并的两个结点下标，参数3：哈夫曼树）
{													//新节点下标为当前结点总数，即nodecount
	T[nodecount].weight = T[a].weight + T[b].weight;//新结点权重为两个待合并结点权重的和
	T[nodecount].lchild = a;						//新结点左儿子下标为a
	T[nodecount].rchild = b;						//新结点右儿子下标为b
	T[a].parent = nodecount;						//下标为a和b的结点的双亲结点下标为新结点的下标，即nodecount
	T[b].parent = nodecount;
	nodecount++;									//结点总数nodecount增加1
}

void PrintTree(int root, huffmantree T)				//函数：打印哈夫曼树中所有叶结点信息（参数1：哈夫曼树根结点下标，参数2：哈夫曼树）
{
	int i = root;									//与递归先序遍历过程相同，不过只有到达叶结点时才打印字符及权重信息
	if (i == -1)
		return;
	if (T[i].lchild == -1 && T[i].rchild == -1)
		cout << T[i].chr << "  " << T[i].weight << endl;
	PrintTree(T[i].lchild, T);
	PrintTree(T[i].rchild, T);
}

void Code(huffmantree T, huffmancode &D)		//函数：对子符进行编码并存入哈夫曼编码数组中（参数1：哈夫曼树，参数2：哈夫曼编码数组）
{
	int i, posa, posb;
	for (i = 0; i < leafcount; i++)				//对leafcount个叶结点字符进行编码
	{
		posa = i;								//pos初始化为当前叶结点下标
		int len = 0;							//len：表示哈夫曼编码长度
		char hcode[N + 1];						//数组：存储哈夫曼编码结果
		D[i].chr = T[i].chr;					//将当前叶结点字符存入哈夫曼编码数组
		while (T[posa].parent != -1)			//判断是否移动到根结点
		{
			posb = T[posa].parent;				//从叶结点出发向双亲结点移动
			if (T[posb].lchild == posa)			//若posa是posb的左儿子，则哈夫曼编码写入一个0
				hcode[len] = '0';
			else								//若posa是posb的右儿子，则哈夫曼编码写入一个1
				hcode[len] = '1';
			posa = posb;						//向双亲结点移动
			len++;
		}
		for (int j = 0; j < len; j++)			//将hcode逆置存入哈夫曼编码数组中即得到正确的哈夫曼编码
			D[i].bit[j] = hcode[len - j - 1];
		D[i].bit[len] = '\0';					//加入空字符标识编码结尾
	}
	cout << "编码完成！" << endl;
}

int SearchCode(char c, huffmancode D)			//函数：在哈夫曼编码数组中从查找特定字符编码，返回其下标（参数1：待查找字符，参数2：哈夫曼编码数组）
{
	for (int i = 0; i < leafcount; i++)
		if (D[i].chr == c)
			return i;
	return -1;
}

void Compress(char *filename, huffmancode D)	//函数：将文件编码压缩并写入二进制文件（参数1：待压缩文件名，参数2：哈夫曼编码数组）
{
	char *filename_txt = new char[MAXLEN];
	strcpy(filename_txt, filename);
	strcat(filename_txt, ".txt");				//在待压缩文件后加入后缀“.txt”得到待压缩文件全名
	char *filename_dat = new char[MAXLEN];
	strcpy(filename_dat, filename);
	strcat(filename_dat, ".dat");				//在待压缩文件后加入后缀“.dat”得到待写入的二进制文件全名
	ifstream is;
	ofstream os;
	char ch;				//ch：用于读取字符
	int index;				//index：某字符在哈夫曼编码数组中的下标
	int count = 0;			//count：用于记录读取的哈夫曼编码的位数
	unsigned char set;		//无符号字符set：长度为一个字节（8bit），用作位操作的容器
	set &= 0;				//容器set初始化为00000000
	is.open(filename_txt);	//打开待压缩文件
	if (!is.is_open())
	{
		cerr << "打开文本文件失败！" << endl;
		exit(EXIT_FAILURE);
	}
	os.open(filename_dat, ios::binary);		//打开待写入二进制文件
	if (!os.is_open())
	{
		cerr << "打开二进制文件失败！" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())		//判断是否读取到文件结尾
	{
		is.get(ch);			//读取一个字符
		index = SearchCode(ch, D);
		int pos = 0;		//pos：读取哈夫曼编码的游标
		while (D[index].bit[pos] != '\0')		//若已读取一个字符的哈夫曼编码的所有位，则循环结束，读取下一个字符
		{
			set <<= 1;		//容器set左移一位
			count++;		//计数器count加1
			if (D[index].bit[pos] == '1')		//若当前读取到的哈弗曼编码位为1，则set最低位设为1
				set |= 1;
			if (count == 8)	//若计数器count等于8，则说明已经读够8位
			{
				os.write((char *)&set, sizeof(char));		//将当前容器set中的8个位写入二进制文件
				set &= 0;	//清空set，以读取下一个8位
				count = 0;	//计数器置0
			}
			pos++;			//读取哈夫曼编码的下一位
		}
	}
	set <<= (8 - count);	//在剩余位后面补0凑够8位写入二进制文件
	os.write((char *)&set, sizeof(char));
	cout << "文件压缩完成，请到文件 " << filename_dat << " 中查看！" << endl;
	is.close();				//关闭文件
	os.close();
}

void PrintCode(huffmancode D)		//函数：打印哈夫曼编码信息（参数：哈夫曼编码数组）
{
	char choice;
	cout << " ------------------------------------------ " << endl;
	cout << "|        请按数字键选择相应功能            |" << endl;
	cout << "|        1.查询单个字符哈夫曼编码          |" << endl;
	cout << "|        2.查询全部字符哈夫曼编码          |" << endl;
	cout << " ------------------------------------------ " << endl;
	cout << "         请输入您的选择：";
	cin >> choice;
	if (choice == '1')		//输入1：打印特定字符哈夫曼编码
	{
		char c;
		cout << "请输入您想查询的字符：";
		cin >> c;
		for (int i = 0; i < leafcount; i++)
		{
			if (D[i].chr == c)
			{
				cout << "字符" << c << "的编码结果为： ";
				puts(D[i].bit);
				return;
			}
		}
		cout << "未查找到该字符！" << endl;
	}
	else if (choice == '2')	//输入2：打印所有字符哈夫曼编码
	{
		cout << "全部字符的哈夫曼编码为：" << endl;
		for (int i = 0; i < leafcount; i++)
		{
			cout << D[i].chr << "： ";
			puts(D[i].bit);
		}
	}
	else
		cout << "您的输入有误！" << endl;
}

void DecompressScreen(char *filename, int root, huffmantree T)		//函数：解压缩二进制文件并输出到屏幕（参数1：待解压的二进制文件名称，参数2：哈夫曼树）
{
	char *filename_dat = new char[MAXLEN];
	strcpy(filename_dat, filename);
	strcat(filename_dat, ".dat");		//在待解压文件后加入后缀“.dat”得到待解压的二进制文件全名
	int pos = root;						//pos：用于遍历哈夫曼树的游标
	unsigned char set;					//无符号字符set：长度为一个字节（8bit），用作位操作的容器
	ifstream is;
	is.open(filename_dat, ios::binary);	//打开待解压文件
	if (!is.is_open())
	{
		cerr << "打开压缩文件失败！" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())					//判断是否读取到二进制文件结尾
	{
		is.read((char *)&set, sizeof(char));	//从文件中读取一个字节（8位）二进制编码存入容器set中
		for (int i = 0; i < 8; i++)		//根据二进制编码遍历二叉树以寻找叶结点
		{
			if ((set & 0x80) == 0)		//若set&10000000=00000000，则set最高位为0，哈夫曼树中向左儿子移动
				pos = T[pos].lchild;
			else						//若set&10000000=00000001，则set最高位为1，哈夫曼树中向右儿子移动
				pos = T[pos].rchild;
			set <<= 1;		//set左移一位以判断下一位
			if (T[pos].lchild == -1 && T[pos].rchild == -1)		//若移动到叶结点则将该叶结点中的字符输出到屏幕
			{
				cout << T[pos].chr;
				pos = root;				//pos重新初始化为根结点便于下一次遍历
			}
		}
	}
	is.close();		//关闭文件
}

void DecompressFile(char *filename, int root, huffmantree T)	//与上一函数过程相同，只是将解码结果输出到文件“待压缩文件名dcp.txt”而不是屏幕中
{
	char *filename_dat = new char[MAXLEN];
	char *filename_txt = new char[MAXLEN];
	strcpy(filename_dat, filename);
	strcat(filename_dat, ".dat");
	strcpy(filename_txt, filename);
	strcat(filename_txt, "dcp.txt");
	int pos = root;
	unsigned char set;
	ifstream is;
	ofstream os;
	is.open(filename_dat, ios::binary);
	if (!is.is_open())
	{
		cerr << "打开压缩文件失败！" << endl;
		exit(EXIT_FAILURE);
	}
	os.open(filename_txt);
	if (!os.is_open())
	{
		cerr << "打开解压缩文件失败！" << endl;
		exit(EXIT_FAILURE);
	}
	while (!is.eof())
	{
		is.read((char *)&set, sizeof(char));
		for (int i = 0; i < 8; i++)
		{
			if ((set & 0x80) == 0)
				pos = T[pos].lchild;
			else
				pos = T[pos].rchild;
			set <<= 1;
			if (T[pos].lchild == -1 && T[pos].rchild == -1)
			{
				os << T[pos].chr;
				pos = root;
			}
		}
	}
	is.close();
	os.close();
	cout << "文件解压缩完成，请到文本文件 " << filename_txt << " 中查看！" << endl;
}