#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
using namespace std;
#elif
#endif

#include<iostream>


//1.
#if 0
class Base1 {
public:
	//加上virtual构成虚函数的重写 -- 触发多态
	virtual void display()const {
	//void display()const {
		cout << "Base1::display()" << endl;
	}
};
class Base2 :public Base1 {
public:
	void display()const {
		cout << "Base2::display()" << endl;
	}
};
class Derived :public Base2 {
public:
	void display()const {
		cout << "Derived::display()" << endl;
	}
};
void fun(Base1* ptr) {
	ptr->display();
}
void test1() {
	Base1 base1;
	Base2 base2;
	Derived derived;
	fun(&base1);
	fun(&base2);
	fun(&derived);
}
#endif



//2.
//构成继承建议使用虚析构
#if 0
class Base {
public:
	virtual ~Base() {
		cout << "Base::~Base()" << endl;
	}
};
class Derived :public Base {
public:
	Derived() {
		this->p = new int(0);
	}
	~Derived() {
		cout << "Derived::~Derived()" << endl;
		delete this->p;
	}
private:
	int* p;
};
void fun(Base* b) {
	delete b;
}
void test2() {
	Base* b = new Derived();
	fun(b);
}
#endif

#include"Student.h"
void test3() {
	Student st1("小明", "201");
	ScienceStudent st2("张三", "202", "001");
	EngineeringStudent st3("李四", "203", "010");
	Student* student_info_arr[] = { &st1,&st2,&st3 };
	//print(student_info_arr, 3);
	printMore(student_info_arr, 3);
}
void test4() {
	ScienceStudent Alice("Alice", "201", "01");
	ScienceStudent Bob("Bob", "202", "02");
	EngineeringStudent Carrol("Carrol", "203", "010");
	EngineeringStudent David("David", "204", "020");
	Student* student_info_arr[] = { &Alice,&Bob,&Carrol,&David };
	//print(student_info_arr, 4);
	printMore(student_info_arr, 4);
}

#include"Shape.h"
void test5() {
	Triangle t1(3, 4, 5);
	Circle c1(3);
	Shape* shape_arr[] = { &t1,&c1 };
	printa(shape_arr, 2);
}
int main(){
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}