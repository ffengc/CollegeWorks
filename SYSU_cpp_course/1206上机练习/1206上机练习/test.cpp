
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

/**
 * 1.编写一个类模板Array<class T, int SIZE>，
 * 封装数组元素，提供排序、查找、求和和打印功能。
 * 然后产生类型实参分别为int型，double型和string型的模板类，
 * 调用上述功能；编写Score类，包含string student_id和double score两个数据成员, 
 * 产生Array<Score>类。手工初始化3个对象，调用上述排序、查找、求和和打印功能。.
 */

#include"Static_Array.h"
struct Score
{
	friend struct CmpScore;
protected:
	string __student_id;
	double __score;
public:
	Score()
		:__student_id("000"), __score(100) {}
	Score(const Score& s) = default;
};
struct CmpScore
{
	bool operator()(const Score& s1, const Score& s2)
	{
		return s1.__score < s2.__score;
	}
};
//不提供Score和string的求和仿函数 -- 不支持Score求和
void test1()
{
	StaticArray<double, 10>arr = { 10.0,9,7,5,3,1,2,4,6,8 };
	//StaticArray<int, 10>arr2(arr);
	//cout << endl;
	arr.sort(CmpScore());
	cout << arr;
	cout << arr.sum() << endl;
}
void test2()
{
	StaticArray<string, 10>arr = { "aba","adsf","asdf" ,"aa"};
	cout << arr;
	arr.sort(CmpScore());
	cout << arr;
	//cout << arr.sum() << endl;
}
int main()
{
	//test1();
	test2();
	return 0;
}