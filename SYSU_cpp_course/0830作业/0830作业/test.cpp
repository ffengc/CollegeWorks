#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class homework_Solution {
public:
	//进制转化
	void test_decimal_conversion() {
		int input = 0;
		cout << "请输入一个十六进制数字:" << endl;
		cin >> std::hex >> input;
		cout << "十进制为" << std::dec << input << endl;
		cout << "八进制为" << std::oct << input << endl;
	}
#if 1
	//实现1
	template<class T1, class T2 = int>
	float add(T1 num1, T2 num2 = 1) {
		return num1 + num2;
	}
#endif
#if 0
	//实现2
	int add(int x, int y = 1) { return x + y; }//缺省参数
	float add(int x, float y) { return x + y; }
	float add(float x, int y) { return x + y; }
	float add(float x, float y) { return x + y; }
#endif
};
int main() {
	//homework_Solution().test_decimal_conversion();
	int a = 1;
	int b = 2;
	float c = 3.1f;
	float d = 4.5f;
	cout << "add(a)的值为" << homework_Solution().add(a) << endl;//2
	cout << "add(a,b)的值为" << homework_Solution().add(a, b) << endl;//3
	cout << "add(a,c)的值为" << homework_Solution().add(a, c) << endl;//4.1
	cout << "add(c,a)的值为" << homework_Solution().add(c, a) << endl;//4.1
	cout << "add(c,d)的值为" << homework_Solution().add(c, d) << endl;//7.6
	return 0;
}