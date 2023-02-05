
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<string>
#include<functional>
#include<map>
#include<unordered_map>
using namespace std;
#include<iostream>
#include<algorithm>
#include<unordered_set>

#elif
#endif

#if 0
//最后一个参数，要提供一个重载
void show_list3() {}
template<typename T, typename... Args>
void show_list3(T value, Args ... args)
{
	cout << value << " ";
	show_list3(args...);//递归调用
}
//改进后的show_list()
void show_list() {}
template<typename T>
void show_list(const T& val)
{
	cout << val << endl;
}
template<typename T, typename ...Args>
void show_list(const T& val, const Args&...args)
{
	cout << val << " ";
	show_list(args...);
}
int main()
{
	int n = 14;
	double x = 2.7;
	string mr = "Mr";
	//show_list3(n, x);
	//cout << endl;
	//show_list3(x * x, '!', 7, mr);
	show_list(n, x);
	cout << endl;
	show_list(x * x, '!', 7, mr);
	return 0;
}
#endif


//STL简介
#if 0
int main()
{
	//const int N = 5;
	vector<int>s = { 1,2,3,4,5 };
	//把s.begin()~s.end()之间的数据做一个negate<int>(取反)操作之后，输出到cout流上
	transform(s.begin(), s.end(), ostream_iterator<int>(cout, " "), negate<int>());//negate<int>()是一个仿函数
	return 0;
}
#endif


//mySort
#if 0
template<class T,class input_iterator,class output_iterator>
void mySort(input_iterator first, input_iterator last, output_iterator result)
{
	//先把输入的东西存到vector里面去，然后排序
	vector<T>s;
	for (; first != last; ++first)
	{
		s.push_back(*first);
	}
	sort(s.begin(), s.end());//对s进行排序
	copy(s.begin(), s.end(), result);//把排序好的vector拷贝到输出流上，输出流可以是容器迭代器，也可以是cout迭代器
}
int main()
{
	//unordered_multiset<int>set = { 1,2,3,4,5,1,2,3,12 };
	unordered_set<int>set = { 1,2,3,4,5,1,2,3,12 };
	vector<int>arr(set.size() + 1); arr[0] = 100;
	//把set.begin()~set.end()的数据放到arr.begin()+1的位置去
	mySort<int>(set.begin(), set.end(), arr.begin() + 1);
	for (const auto& e : arr)
	{
		cout << e << " ";
	}
	cout << endl;
#if 0
	mySort<int>(istream_iterator<int>(cin), istream_iterator<int>(), ostream_iterator<int>(cout, " "));
	//把stdin上上面的数据作为一个输入流 -- stdout上的数据作为一个输出流
	cout << endl;
#endif
	return 0;
}
#endif


//从流中读入几个实数，分别平方后输出
double square(double x) { return x * x; }
int main()
{
	unordered_set<int>s = { 1,2,1,2,3,4,5 };
	transform(s.begin(), s.end(), ostream_iterator<double>(cout, " "), square);//square就是一个仿函数
	return 0;
}