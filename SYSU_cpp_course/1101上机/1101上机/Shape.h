#pragma once


#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
#include<set>
#include<functional>
#include<numeric>
using namespace std;


class Shape{
public:
	Shape(double area = 0)
		:_area(area) {}
	Shape(const Shape& s)
		:_area(s._area) {}
	~Shape() = default;
protected:
	double _area = 0;
};
class Rectangle :public Shape {
public:
	Rectangle(int row = 0, int col = 0)
		:Shape(row* col), _row(row), _col(col) {}
	Rectangle(const Rectangle& r)
		:Shape(r._row* r._col), _row(r._row), _col(r._col) {}
	~Rectangle() = default;
public:
	double GetArea() {
		return this->_area;
	}
private:
	size_t _row;
	size_t _col;
};
#define PI 3.14
class Circle final :public Shape {
public:
	Circle(double r = 0)
		:Shape(r* r* PI), _r(r) {}
	Circle(const Circle& r)
		:Shape(r._r* r._r* PI), _r(r._r) {}
	~Circle() = default;
public:
	double GetArea() {
		return this->_area;
	}
protected:
	double _r;
};
class Square final : public Rectangle  {
public:
	Square(int len = 0)
		:Rectangle(len,len), _len(len) {}
	Square(const Square& s)
		:Rectangle(s._len, s._len), _len(s._len) {}
	~Square() = default;
public:
	double GetArea() {
		return this->_area;
	}
protected:
	size_t _len;
};


void test_Shape() {
	Square s(2);
	cout << s.GetArea() << endl;
	Rectangle r(2, 3);
	cout << r.GetArea() << endl;
	Circle c(1);
	cout << c.GetArea() << endl;
}