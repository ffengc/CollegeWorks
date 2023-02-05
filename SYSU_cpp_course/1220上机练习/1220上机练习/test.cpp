
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif


#include<vector>
#include<unordered_map>
#include<set>
#include<numeric>
#include<iostream>
#include<functional>
#include<algorithm>
#include<string>
using namespace std;


//写法1
#if 0
int mult(int x, int y) { return x * y; }
int sub(int x, int y) { return x - y; }
int main()
{
	int a[] = { 1,2,3,4,5 };
	const int N = sizeof(a) / sizeof(a[0]);
	cout << accumulate(a, a + N, 1, mult) << endl;
	cout << accumulate(a, a + N, 0, sub) << endl;
	return 0;
}
#endif

//写法2
#if 0
struct MultClass
{
	int operator()(int x, int y)const
	{
		return x * y;
	}
};
struct SubClass
{
	int operator()(int x, int y)const
	{
		return x - y;
	}
};
int main()
{
	int a[] = { 1,2,3,4,5 };
	const int N = sizeof(a) / sizeof(a[0]);
	cout << accumulate(a, a + N, 1, MultClass()) << endl;
	cout << accumulate(a, a + N, 0, SubClass()) << endl;
	return 0;
}
#endif

//我们还可以用库里有的
#if 0
int main()
{
	int a[] = { 1,2,3,4,5 };
	const int N = sizeof(a) / sizeof(int);
	cout << accumulate(a, a + N, 1, multiplies<int>()) << endl;
	return 0;
}
#endif

#if 0
int main()
{
	int arr[] = { 30,90,10,40,70,50,20,80 };
	const int N = sizeof(arr) / sizeof(arr[0]);
	vector<int>a(arr, arr + N);//要利用迭代器区间构造
	cout << "before sort" << endl;
	copy(a.begin(), a.end(), ostream_iterator<int>(cout, " ")); cout << endl;//打印到stdout上
	sort(a.begin(), a.end(), greater<int>());
	cout << "after sort" << endl;
	copy(a.begin(), a.end(), ostream_iterator<int>(cout, " ")); cout << endl;//打印到stdout上
	return 0;
}
#endif

//函数适配器
//1.绑定适配器
//2.组合适配器
//3.指针函数适配器

//需求：寻找第一个大于40的数

//bind1st 绑定第一个参数
//bind2nd 绑定第二个参数
#if 0
int main()
{
	vector<int>a = { 30,90,10,40,70,50,20,80 };
	//auto p = find_if(a.begin(), a.end(),greater<int>());//err 因为find_if只接受一元的
	//所以绑一个就行
	auto p = find_if(a.begin(), a.end(), bind2nd(greater<int>(), 40));
	if (p != a.end())
	{
		cout << "第一个大于40d的数字是:" << *p << endl;
	}
	return 0;
}
#endif
//但是在如果仿函数不止两元呢？

//C++提供的通用的函数 bind
//bit也讲过
#if 0
void fn(int n1, int n2, int n3) //假设这个是我们的仿函数
{
	cout << n1 << " " << n2 << " " << n3 << endl;
}
int fn2()
{
	cout << "fn2 has called" << endl; return -1;
}
int main()
{
	using namespace std::placeholders;
	auto bind_test1 = bind(fn, 1, 2, 3);//此时的bind_test1就是参数为1,2,3的函数fn
	auto bind_test2 = bind(fn, _1, _2, _3);
	auto bind_test3 = bind(fn, 0, _1, _2);
	auto bind_test4 = bind(fn, _2, 0, _1);//这里还调整了参数的顺序

	bind_test1();
	bind_test2(3, 8, 24);
	bind_test2(1, 2, 3, 4, 5);//4,5会被丢弃
	bind_test3(10, 24);//输出0,10,24
	bind_test3(10, fn2());//输出0,10,-1
	bind_test4(10, 24);//24,0,10
	return 0;
}
#endif
//bind取代旧接口 bind1st/bind2nd

//需求：找到第一个大于40的数
#if 0
int main()
{
	using namespace std::placeholders;
	vector<int>a = { 30,90,10,40,70,50,20,80 };
	//auto p = find_if(a.begin(), a.end(),greater<int>());//err 因为find_if只接受一元的
	//所以绑一个就行
	auto p = find_if(a.begin(), a.end(), bind(greater<int>(), _1, 40));
	if (p != a.end())
	{
		cout << "第一个大于40d的数字是: " << *p << endl;
	}
	return 0;
}
#endif



//lambda表达式
/*
* [a]表示值传递捕获变量a(多个参数可以用逗号分隔) 
* [=]表示值传递捕获上下文所有变量 
* [&a]表示引用传递捕获变量a 
* [&]表示引用传递捕获上下文所有变量 
* [this]表示值传递捕获当前的this指针
* [=, &a, &b]表示值传递捕获上下文所有变量，但是a、b变量以 引用传递方式捕获
* [&, a, this]表示引用传递捕获上下文所有变量，但是a和this指 针以值传递方式捕获。
*/

//一些匿名函数的例子
void test1()
{
	int x = 100, y = 200, z = 300;
	auto ff = [=, &y, &z](int n) //[=, &a, &b]表示值传递捕获上下文所有变量，但是a、b变量以 引用传递方式捕获
	{
		cout << x << endl;
		y++; z++;
		return n * n;
	};
	cout << ff(15) << endl;
	cout << y << ", " << z << endl;
}
void test2()
{
	vector<string>words =
	{
		"abcdefadsg","abcdeasdfasdfadsfgh"
		"aabadsdcdef","aaassdafsdasddsdf",
		"aaaadfe"
	};
	//按照字符串的长度排序
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b)
		{ return a.size() < b.size(); });
	copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"));
	cout << endl << "--------------" << endl;
	//获取一个迭代器，指向第一个满足size()>=sz的元素
	int sz = 10;
	auto wc = find_if(words.begin(), words.end(), [sz](const string& a) {return a.size() > sz; });
	cout << *wc << endl;
}

int main()
{
	//test1();
	test2();
	return 0;
}


//智能指针
//循环引用问题