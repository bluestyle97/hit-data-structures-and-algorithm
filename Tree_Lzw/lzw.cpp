//
//	@Filename: lzw.cpp
//	@Function: lzw编码压缩
//	@Author: 许家乐
//	@Create Time: 2016/12/15, 18:59
//	@Copyright (C) 2016 HIT. All rights reserved
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map>	//标准模板类map用作字典
#define N 256	//ASCII字符有256个

using namespace std;

//
//函数名：	InitDictionary
//功能：	初始化编码时所用字典，将256个ASCII字符作为键，将ASCII编码作为值
//参数：	一个标准模板类map<string, int>的对象的引用（待初始化的字典）
//返回值：	空
//
void InitDictionary(map<string, int> &);
//
//函数名：	InitDictionary（+1重载）
//功能：	初始化解码时所用字典，将ASCII编码作为键，将256个ASCII字符作为值
//参数：	一个标准模板类map<int, string>的对象的引用（待初始化的字典）
//返回值：	空
//
void InitDictionary(map<int, string> &);
//
//函数名：	Compress
//功能：	对文本文件进行lzw编码压缩，生成二进制压缩文件
//参数：	string（待压缩文件名）
//返回值：	空
//
void Compress(string);
//
//函数名：	Decompress
//功能：	解码二进制压缩文件，生成解压缩文本文件
//参数：	string（待压缩文件名）
//返回值：	空
//
void Decompress(string);

int main()
{
	cout << " --------------------------------------- " << endl;
	cout << "|     欢迎使用LZW编码文件压缩系统！     |" << endl;
	cout << " --------------------------------------- " << endl;

	//
	//数据定义
	//filename：	待压缩文件名（不带后缀）
	//quit：		退出程序时的输入字符串
	//
	string filename;

	//lzw编码压缩测试
	cout << " --------------------------------------- " << endl;
	cout << "|     请输入待压缩文件名(不带拓展名）：";
	cin >> filename;
	cout << " --------------------------------------- " << endl;
	Compress(filename);
	Decompress(filename);
	system("pause");
	return 0;
}
void InitDictionary(map<string, int> &dic)
{
	//初始化编码字典
	for (int i = 0; i < N; i++)
	{
		//stream：用于将char转换为string
		stringstream stream;
		char ch = i;
		stream << ch;
		//插入字典
		dic.insert(pair<string, int>(stream.str(), i));
	}
}
void InitDictionary(map<int, string> &dic)
{
	//初始化解码字典
	for (int i = 0; i < N; i++)
	{
		//stream：用于将char转换为string
		stringstream stream;
		char ch = i;
		stream << ch;
		//插入字典
		dic.insert(pair<int, string>(i, stream.str()));
	}
}
void Compress(string filename)
{
	//
	//数据定义
	//dictionary：	编码字典
	//count：		lzw编码，初始化为256
	//input_char：	下一个输入字符
	//prefix：		前缀字符串，初始化为空字符串
	//entry：		前缀字符串+下一个输入字符
	//filein：		待压缩文件名
	//fileout：		二进制压缩文件名
	//
	map<string, int> dictionary;
	unsigned int count = N;
	char input_char;
	string prefix = "";
	string input;
	string entry;
	string filein = filename + ".txt";
	string fileout = filename + ".dat";

	//初始化编码字典
	InitDictionary(dictionary);

	//文件输入输出流的打开及成功判断
	ifstream is(filein, ios::in);
	if (!is.is_open())
	{
		cerr << "待压缩文件打开失败！" << endl;
		exit(EXIT_FAILURE);
	}
	ofstream os(fileout, ios::binary);
	if (!os.is_open())
	{
		cerr << "压缩文件创建失败！" << endl;
		exit(EXIT_FAILURE);
	}

	//lzw编码算法
	while (!is.eof())
	{
		stringstream stream;
		//读入一个字符
		is.get(input_char);
		stream << input_char;
		entry = prefix + stream.str();
		//判断前缀+读入字符是否在编码字典中
		if (dictionary.find(entry) != dictionary.end())	//若在，则前缀变为 原前缀+读入字符
			prefix = entry;
		else											//若不在
		{
			os.write((char *)&dictionary[prefix], sizeof(unsigned int));		//将前缀的编码写入二进制文件
			dictionary[entry] = count++;							//将前缀+读入字符加入字典
			prefix = stream.str();									//将前缀设为读入字符
		}
	}
	//文件输入输出流的关闭
	is.close();
	os.close();
	cout << " --------------------------------------- " << endl;
	cout << "|     文件压缩完成！                    |" << endl;
	cout << " --------------------------------------- " << endl;
}
void Decompress(string filename)
{
	//
	//数据定义
	//dictionary：	解码字典
	//count：		lzw编码，初始化为256
	//input_code：	下一个输入编码
	//prefix：		前缀字符串，初始化为空字符串
	//input：		下一个字符串
	//entry：		前缀字符串+下一个输入字符串首字符
	//filein：		待解压二进制压缩文件名
	//filenout：	解压文件名
	//
	map<int, string> dictionary;
	unsigned int count = N;
	unsigned int input_code;
	string prefix = " ";
	string input;
	string entry;
	string filein = filename + ".dat";
	string fileout = filename += "dcp.txt";

	//初始化编码字典
	InitDictionary(dictionary);

	//文件输入输出流的打开及成功判断
	ifstream is(filein, ios::binary);
	if (!is.is_open())
	{
		cerr << "待解压文件打开失败！" << endl;
		exit(EXIT_FAILURE);
	}
	ofstream os(fileout, ios::out);
	if (!os.is_open())
	{
		cerr << "待写入文件创建失败！" << endl;
		exit(EXIT_FAILURE);
	}

	//读入第一个编码并输出字符串到输出流
	is.read((char *)&input_code, sizeof(unsigned int));
	prefix = dictionary[input_code];
	os << prefix;

	//lzw解码算法
	while (!is.eof())
	{
		//输入下一个编码
		is.read((char *)&input_code, sizeof(unsigned int));
		//取出下一个字符串input
		input = dictionary[input_code];
		//将input记录到输出流
		os << input;
		//entry加入字典
		entry = prefix + input[0];
		dictionary[count++] = entry;
		//前缀=input
		prefix = input;
	}
	//文件输入输出流的关闭
	is.close();
	os.close();
	cout << " --------------------------------------- " << endl;
	cout << "|     文件解压完成！                    |" << endl;
	cout << " --------------------------------------- " << endl;
}
