#define _CRT_SECURE_NO_WARNINGS 1


#include"Point.h"
#include"Line.h"
#include"Rectangle.h"
using namespace std;


void test1() {
	Point p1;
	Point p2(3, 4);
	cout << p2.GetDistance(p1) << endl;
}
void test2() {
	Point p1;
	Point p2(3, 4);
	cout << p1 << " " << p2 << endl;
}
void test3() {
	Point p1(3, 4);
	Point p2 = p1;//编译器会默认生成赋值重载，不用自己写
	Point p3(1, 2);
	p3 = p1;
	cout << p1 << p2 << p3 << endl;
}
void testPoint() {
	//test1();
	//test2();
	test3();
}
void testLine() {
	Point p1(1, 3);
	Point p2(1, 0);
	Line line1(p1, p2);
	Line line2 = line1;
	Line line3(1, 2, 2);
	cout << line1 << line2 << line3 << endl;
	cout << line1.getLineLength() << endl;
}
void testRec() {
	Point p1(0, 0);
	Point p2(0, 3);
	Point p3(3, 3);
	Point p4(3, 0);
	Line l1(p1, p2);
	Line l2(p2, p3);
	Line l3(p3, p4);
	Line l4(p4, p1);
	Rectangle rec1(l1, l2, l3, l4);
	rec1.draw();
}
int main() {
	//testPoint();
	//testLine();
	testRec();
	return 0;
}

/*
* 4.实现非成员函数CombineRectangles()，输入两个矩形，
* 输出合并后的几何对象（可以是Line数组），参数形式自行定义。
*/