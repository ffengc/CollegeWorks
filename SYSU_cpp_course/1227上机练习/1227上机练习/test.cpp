
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_map>
using namespace std;
#include<functional>
#include<numeric>
#include<fstream>


//使用width控制输出宽度
#if 0
int main()
{
	double values[] = { 1.23,35.36,653.7,4358.24 };
	for (size_t i = 0; i < 4; i++)
	{
		cout.width(10);
		cout << values[i] << endl;
	}
	return 0;
}
#endif



//使用setw操作符指定宽度
#include<iomanip>
#if 0
int main()
{
	double values[] = { 1.23,35.36,653.7,4358.24 };
	string names[] = { "Zoot","Jimmy","AI","Stan" };
	for (size_t i = 0; i < 4; i++)
	{
		cout << setw(6) << names[i] << setw(10) << values[i] << endl;
	}
	return 0;
}
#endif


//setiosflags参数：见ppt
//文件输出流成员函数
//open 把流与一个特定的磁盘文件关联起来
//put 把一个字符写道输出流中
//write 把内存中的一块内容写到一个文件输出流中
//seekp和tellp 操作文件流的内部指针
//close 关闭一个我呢见输出流关联的磁盘文件

#if 0
struct Date
{
	int mon;
	int day;
	int year;
};
int main()
{
	Date dt = { 6,10,92 };
	ofstream file("data.dat", ios_base::binary);
	file.write(reinterpret_cast<char*>(&dt), sizeof(dt));
	file.close();
	return 0;
}
#endif

//字符串输出流
//ostringstream
//利用ostringstream将数值转换为字符串
#include<sstream>
#if 0
template<class T>
inline string toString(const T& v)
{
	ostringstream os;
	os << v;//将变量v的值写入字符串流
	return os.str();//返回输出流生成的字符串
}
int main()
{
	string str1 = toString(5);
	cout << str1 << endl;
	string str2 = toString(1.2);
	cout << str2 << endl;
	return 0;
}
#endif

//to_string更简单，但格式化比较单一，相当于sprintf



//输入流

//为输入流指定一个终止字符
#if 0
int main()
{
	string line;
	cout << "Type a line terminated by '\t'" << endl;
	getline(cin, line, '\t');
	cout << line << endl;
	return 0;
}
#endif


//从一个payroll文件读一个二进制记录到一个结构中
#if 0
struct SalaryInfo
{
	size_t id;
	double salary;
};
int main()
{
	SalaryInfo employee1 = { 600001,8000 };
	ofstream os("payroll", ios_base::out | ios_base::binary);
	os.write(reinterpret_cast<char*>(&employee1), sizeof(employee1));
	os.close();


	//读出来
	ifstream is("payroll", ios_base::in | ios_base::binary);
	if (is)
	{
		SalaryInfo employee2;
		is.read(reinterpret_cast<char*>(&employee2), sizeof(employee2));
		cout << employee2.id << " " << employee2.salary << endl;
	}
	else
	{
		cout << "ERROR:Cannot open file 'payroll'." << endl;
	}
	is.close();
	return 0;
}
#endif



//字符串输入流

//用istringstream将字符串转换为数值
#if 0
template<class T>
inline T fromString(const string& str)
{
	istringstream is(str); //创建字符串输入流
	T v;
	is >> v; //从字符串输入流中读取变量v
	return v;
}
int main()
{
	int v1 = fromString<int>("5");
	cout << v1 << endl;
	double v2 = fromString<double>("1.2");
	cout << v2 << endl;
	return 0;
}
#endif


//宽字符、宽字符串与宽流
//宽字符 wchar_t 类型
//宽字符串 wstring 类型



//异常处理

//处理除0异常
#if 0
int divide(int x, int y)
{
	if (y == 0)throw x;
	return x / y;
}
int main()
{
	try
	{
		cout << "5/2=" << divide(5, 2) << endl;
		cout << "8/0=" << divide(8, 0) << endl;
		cout << "7/1=" << divide(7, 1) << endl;
	}
	catch (int e)
	{
		cout << e << " is divided by zero!" << endl;
	}
	cout << "That is ok." << endl;
	return 0;
}
#endif


//三角形面积计算
#include<stdexcept>
double area(double a, double b, double c) throw (invalid_argument)
{
	//判断三角形边长是否为正
	if (a <= 0 || b <= 0 || c <= 0)
		throw invalid_argument("the side length should be positive");
	//判断三条边是否满足三角不等式
	if (a + b <= c || b + c <= a || c + a <= b)
		throw invalid_argument("the side length should be fit the triangle inequation");
	//由Heron公式计算面积
	double s = (a + b + c) / 2.0;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}
int main()
{
	double a, b, c;
	cout << "Please inpput the side lengths of a triangle: ";
	cin >> a >> b >> c;
	try
	{
		double s = area(a, b, c);//尝试计算三角形面积
		cout << "Area:" << s << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Error:" << e.what() << endl;
	}
	return 0;
}