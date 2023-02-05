#pragma once

#include"Shape.h"
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

class ShapeFile
{
public:
	using ptr_shape = shared_ptr<Shape>;
	using ptr_point = shared_ptr<Point>;
	//读文件的状态
	enum Entry_status
	{
		null,POINTS, CIRCLE, POLYGON
	};
public:
	Entry_status cur_status = null;
protected:
	//处理字符串的一些接口
	double find_first_digit(const string& str);
	double find_last_digit(const string& str);
	vector<int> get_idx(const string& str);
	void erase_the_first_idx(string& arr);
public:
	ShapeFile(ifstream& infile);
	ShapeFile(const ShapeFile& sf) = delete;//不允许进行深拷贝
	~ShapeFile() = default;//使用了智能指针 -- 直接析构即可
	void Generate();
	void Print();
protected:
	int ExtractPoints(const string& line, vector<Point>& pts) {}//使用了其它函数代替实现
	vector<ptr_point>__points;
	vector<ptr_shape>__shape;
	vector<ptr_shape>__compositeShape;
};