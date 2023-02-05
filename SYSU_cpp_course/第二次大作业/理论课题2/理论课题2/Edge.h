#pragma once

#include<iostream>
using namespace std;



/**
 * 1. 定义一个点类Point，表示平面上的一个点，包含坐标double x_, double y_，提供打印功能Print()。
 * 提供一个Move(double xoffset, double yoffset)函数，表示平移偏移量(xoffset, yoffset)..
 */
class Circle;
class Polygon;
class Shape;
typedef shared_ptr<Shape> ptr_shape;
class Point
{
public:
	friend class Edge;
	friend class Circle;
	friend class Polygon;
	friend ostream& operator<<(ostream& out, const Point& p);
	friend ptr_shape operator&(const ptr_shape& ptr1, const ptr_shape& ptr2);
	friend ptr_shape operator|(const ptr_shape& ptr1, const ptr_shape& ptr2);
protected:
	double _x;
	double _y;
public:
	Point(double x = 0, double y = 0)
		:_x(x), _y(y) {}
	Point(const Point& p) = default;
	~Point() = default;
public:
	void Print() const
	{
		cout << "(" << this->_x << "," << this->_y << ")";
	}
	void Move(double xoffset, double yoffset)
	{
		this->_x += xoffset;
		this->_y += yoffset;
	}
};

/**
 * 定义一个边类Edge，
 * 包括一条边的两个Point端点，
 * 提供求长度Length()和打印Print()函数。
 * 打印函数需要重用Point类的相关打印功能。
 */
class Edge
{
public:
	friend class Polygon;
	friend ptr_shape operator&(const ptr_shape& ptr1, const ptr_shape& ptr2);
	friend ptr_shape operator|(const ptr_shape& ptr1, const ptr_shape& ptr2);
protected:
	Point _point1;
	Point _point2;
public:
	Edge(const Point& p1 = Point(), const Point& p2 = Point())
		:_point1(p1), _point2(p2) {}
	Edge(const Edge& e) = default;
	~Edge() = default;
public:
	//题目要求：Print()需要复用<class Point>的Print
	double Length() const
	{
		return sqrt(pow(_point1._x - _point2._x, 2) + pow(_point1._y - _point2._y, 2));
	}
	void Print() const
	{
		double length = this->Length();
		cout << endl;
		cout << "第一个端点为" << _point1 << endl;
		cout << "第二个端点为" << _point2 << endl;
		cout << "长度为" << length << endl;
		cout << endl;
	}
	void Move(double xoffset = 0, double yoffset = 0)
	{
		_point1.Move(xoffset, yoffset);//重用Point的一些方法
		_point2.Move(xoffset, yoffset);
	}
};