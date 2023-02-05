#define _CRT_SECURE_NO_WARNINGS 1

#include"Complex.h"
#include"String.h"

#if 1 //测试复数类
int main() {
	Complex C1(1, 0);
	C1.show();
	Complex C2(1, 1);
	C2.show();
	C1.add(C2).show();
	cout << Complex::Complex_size() << endl;

	Complex a1(1, 1);
	Complex a2(2, 2);
	Complex ret = Complex_mul(a1, a2);
	ret.show();
	//现在添加一些重载 -- 不再去用show，add这些函数了
	//真正使用a+b的时候，ab应该都是不受影响的，而不是加在a上
	//但是为了可以这样写，还需要重载一次<< -- 或者使用模板参数
	//cout << (C1 + C2) << endl;
	Complex ret2 = C1 + C2;
	cout << ret2 << endl;

	cin >> C1;
	cout << C1 << endl;

	//再重载一个乘法的
	Complex b1;
	Complex b2(1, 1);
	Complex ans = b1 * b2;
	cout << ans << endl;
	return 0;
}
#endif

//测试StringBad类
#if 0
int main() {
	StringBad s = "abcdefg";
	StringBad scopy = s;
	cout << s << endl;
	//测试赋值
	StringBad s2;
	s2 = s;
	cout << s2 << endl;
	return 0;
}
#endif


//测试StringLeaky类
#if 0
int main() {
	EatMemory();//可以用死循环去跑
	return 0;
}
#endif