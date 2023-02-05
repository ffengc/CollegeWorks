
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include"FileQuery.h"
#include <fstream>
#include <iostream>
#include <string>
#include <direct.h>
using namespace std;
#elif
#endif

void query(FileQuery& fq)
{
	while (1)
	{
		string str;
		cout << "请输入你要查询的单词(输入q退出查询):";
		cin >> str;
		if (str == "q")break;
		fq.Find(str);
	}
}

/**
 * 这里我在调用的时候是分别调用的 -- 避免一次打印太多东西
 * 老师如果需要测试分别取消接口调用的注释即可~.
 * 详情结果可见txt文件
 */
void runFileQuery(ifstream& infile)
{
	//start the sys!
	FileQuery sys(infile);
	//sys.print_sentences();
	//sys.print_sentences_ascend();
	//sys.print_word_count();
	//cout << "------------------ 打印频率前5高的单词 ------------------" << endl;
	//sys.print_top_world_context(5);
	//cout << "------------------ 打印频率前4高的单词 ------------------" << endl;
	//sys.print_top_world_context(4);
	//cout << "------------------ 打印频率前3高的单词 ------------------" << endl;
	//sys.print_top_world_context(3);
	//sys.Find("the");
	//query(sys);
	sys.Replace("the", "xxx");
	sys.Replace("my", "__my__");
	sys.Replace("o", "__o__");
	sys.Replace("kajfkasf", "adfasdf");//理论上找不到该单词
	query(sys);
	//cout << endl;
	//FileQuery sys2(sys);
	//sys2.Find("her");//调试可以证明 -- 深拷贝成功
	cout << endl;
}

int main(int argc, char** argv)
{
	// open the file from which user will query words
	if (argc >= 2) 
	{
		ifstream infile(argv[1]);
		if (infile.is_open()) 
		{
			runFileQuery(infile);
		}
		else 
		{
			cerr << "Failed opening input file!" << endl;
			return -1;
		}
	}
	else {
		cerr << "No input file name!" << endl;
	}
	return 0;
}