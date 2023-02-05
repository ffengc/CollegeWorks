#define _CRT_SECURE_NO_WARNINGS 1

/*
4 章练习
1. 编写一个名为Person的人员类，存储人员的姓名、年龄和住址信息。
为你的Person类添加正确的构造函数初始化其属性，
并提供操作使其能够返回姓名和住址，以及打印姓名和住址（通过成员函数实现）
2. 为该类实现默认构造函数和复制构造函数，
默认构造函数使用任意设定的一组值初始化成员变量，
复制构造函数可以打印一些信息来帮助观察复制构造的发生
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Person {
public:
	friend std::ostream& operator<<(std::ostream& out, const Person& p);
	friend std::istream& operator>>(std::istream& in, Person& p);
	~Person() { cout << "调用了Person的析构函数" << endl; }
	Person(string name = "小明", size_t age = 10, string addr = "广州")
		:_name(name), _age(age), _addr(addr) {}
	Person(Person& p) {
		this->_name = p._name;
		this->_age = p._age;
		this->_addr = p._addr;
		cout << "调用了Person的拷贝构造函数" << endl;
	}
	//打印信息第一种方式：get_peoinfo()
	//第二种方式：流插入流提取重载
	void get_peoinfo() {
		cout << "-------------" << endl;
		cout << "姓名为：" << this->_name << endl;
		cout << "年龄为:" << this->_age << endl;
		cout << "地址为:" << this->_addr << endl;
		cout << "-------------" << endl;
	}
	//修改联系人地址（也可以写成运算符重载形式）
	Person& modify_info(string newname, size_t newage, string newaddr) {
		//p的作用域是main，可以传引用返回
		this->_name = newname;
		this->_age = newage;
		this->_addr = newaddr;
		return *this;
	}
	//赋值重载(可用默认生成的)
	Person& operator=(Person& p) {
		this->_name = p._name;
		this->_age = p._age;
		this->_addr = p._addr;
		cout << "调用了赋值重载" << endl;
		return *this;
	}

private:
	string _name;
	size_t _age;
	string _addr;
};
ostream& operator<<(std::ostream& out, const Person& p) {
	//需要方位private属性 -- 设置成友元
	out << "-------------" << endl;
	out << "姓名为：" << p._name << endl;
	out << "年龄为:" << p._age << endl;
	out << "地址为:" << p._addr << endl;
	out << "-------------" << endl;
	return out;
}
std::istream& operator>>(std::istream& in, Person& p) {
	//请输入名字
	cout << "请输入名字:";
	in >> p._name;
	cout << "请输入年龄:";
	in >> p._age;
	cout << "请输入地址:";
	in >> p._addr;
	cout << "输入成功！" << endl;
	return in;
}




Person func(Person pp) {
	//传值调用，会调用拷贝构造 -- 深拷贝 -- 形参压栈
	//传值返回，也会调用拷贝构造 -- 返回拷贝压栈
	return pp;
}
void test1() {
	Person p;
	Person p1("李四", 20, "北京");
	p.get_peoinfo();
	p1.get_peoinfo();
	Person p2 = p1;
	p2.get_peoinfo();
	func(p);
	p2.get_peoinfo();
	p2.modify_info("王五", 30, "武汉").get_peoinfo();
}
void test2() {
	//第二种打印方式，重载流提取流插入
	Person p("李四", 20, "北京");
	cout << p << endl;
	cin >> p;
}
void test3() {
	Person p("张三", 70, "武汉");
	Person p2;
	p2 = p;
	cout << p2 << endl;
}
int main() {
	//test1();
	//test2();
	test3();
	return 0;
}