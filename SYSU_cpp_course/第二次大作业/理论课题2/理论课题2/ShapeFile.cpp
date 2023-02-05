
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif


#include"ShapeFile.h"


double ShapeFile::find_first_digit(const string& str)
{
	int ptr = 0;
	while (ptr < str.size())
	{
		if (isdigit(str[ptr]))
		{
			int fast = ptr;
			while (isdigit(str[fast]) || str[fast] == '.')
			{
				fast++;
			}
			string number(str.begin() + ptr, str.begin() + fast);
			if (str[ptr - 1] == '-')return -stod(number);
			return stod(number);
		}
		ptr++;
	}
	assert(false);
	return 0;
}
double ShapeFile::find_last_digit(const string& str)
{
	int ptr = str.size() - 1;
	while (ptr >= 0)
	{
		if (isdigit(str[ptr]))
		{
			int fast = ptr;
			while (isdigit(str[fast]) || str[fast] == '.')
			{
				fast--;
			}
			string number(str.begin() + fast + 1, str.begin() + ptr + 1);
			if (str[fast] == '-')return -stod(number);
			return stod(number);
		}
		ptr--;
	}
	assert(false);
	return 0;
}
vector<int> ShapeFile::get_idx(const string& str)
{
	int fast = 0;
	int slow = 0;
	vector<int>ret;
	while (fast < str.size())
	{
		while (fast < str.size() && !isdigit(str[fast]) && !isdigit(str[slow]))
		{
			fast++; slow++;
		}
		//此时fast已经是数字了
		while (fast < str.size() && isdigit(str[fast]))
		{
			fast++;
		}
		string number(str.begin() + slow, str.begin() + fast);
		ret.push_back(stoi(number));
		slow = fast;
	}
	return ret;
}
void ShapeFile::erase_the_first_idx(string& arr)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (isdigit(arr[i]))
		{
			int ii = i;
			while (isdigit(arr[ii]))
			{
				arr[ii] = '*';//把数字擦掉
				ii++;
			}
			return;
		}
	}
}
ShapeFile::ShapeFile(ifstream& infile)
{
	/*
	为每一行动态生成（new）一个Shape对象，
	以std::vector<Shape*> shapes_统一保存不同图形对象的指针。
	*/
	string tmp_sentence;
	size_t curent_line_num = 1;//把行号记录一下
	while (getline(infile, tmp_sentence))
	{
		if (tmp_sentence.size() == 0)continue;//当前行没有信息
		if (tmp_sentence[0] == '#')
		{
			//现在我们要确定录入状态是什么
			if (tmp_sentence.find("Point") != string::npos)
				cur_status = POINTS;
			else if (tmp_sentence.find("circle") != string::npos)
				cur_status = CIRCLE;
			else if (tmp_sentence.find("polygon") != string::npos)
				cur_status = POLYGON;
			else cur_status = null;
			continue;
		}
		if (cur_status == POINTS)
		{
			//录入点
			//先把Point后面那个编号擦掉
			erase_the_first_idx(tmp_sentence);
			double x = find_first_digit(tmp_sentence);
			double y = find_last_digit(tmp_sentence);
			this->__points.push_back(ptr_point(new Point(x, y)));
		}
		else if (cur_status == CIRCLE)
		{
			//录入圆
			double center = find_first_digit(tmp_sentence);
			center = (int)center;
			Point cen(*(this->__points[center - 1]));
			double r = find_last_digit(tmp_sentence);
			this->__shape.push_back(ptr_shape(new Circle(cen, r)));
		}
		else if (cur_status == POLYGON)
		{
			//录入多边形
			vector<int>point_indexs = get_idx(tmp_sentence);
			vector<shared_ptr<Edge>>p;
			for (size_t i = 0; i < point_indexs.size(); i++)
			{
				//现在我们有n个点的编号
				//现在要把他们按顺序组成边，存到p里面去
				if (i == point_indexs.size() - 1)
				{
					p.push_back(
						shared_ptr<Edge>(new Edge(*(__points[point_indexs[i] - 1]), *(__points[point_indexs[0] - 1])))
					);
				}
				else
				{
					p.push_back(
						shared_ptr<Edge>(new Edge(*(__points[point_indexs[i] - 1]), *(__points[point_indexs[i + 1] - 1])))
					);
				}
			}
			this->__shape.push_back(shared_ptr<Polygon>(new Polygon(p)));
		}
	}
}
void ShapeFile::Generate()
{
	//两两取&和取|
	for (size_t i = 0; i < __shape.size(); i++)
	{
		if (i == __shape.size() - 1)
		{
			auto ptr = __shape[i] & __shape[0];
			if (ptr)__compositeShape.push_back(ptr);
			ptr = __shape[i] | __shape[0];
			if (ptr)__compositeShape.push_back(ptr);
		}
		else
		{
			auto ptr = __shape[i] & __shape[i + 1];
			if (ptr)__compositeShape.push_back(ptr);
			ptr = __shape[i] | __shape[i + 1];
			if (ptr)__compositeShape.push_back(ptr);
		}
	}
}
void ShapeFile::Print()
{
	for (size_t i = 0; i < __shape.size(); i++)
	{
		__shape[i]->Print();
	}
	for (size_t i = 0; i < __compositeShape.size(); i++)
	{
		__shape[i]->Print();
	}
}