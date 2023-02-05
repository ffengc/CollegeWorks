#pragma once

#include<vector>
#include<set>
#include<assert.h>
#include<algorithm>
#include<iostream>
#include"Edge.h"

enum type
{
	SHAPE, CIRCLE, POLYGON
};

//3.定义一个抽象基类Shape
/**
 * 定义一个抽象基类Shape，提供周长double Circumference (), 面积double Area(), void Print(), 
 * void Move()等纯虚函数，提供虚函数bool IsValid()判断是否是合法。
 * 定义静态常量static const int UnknownValue = -1。.
 */
class Circle;
class Polygon;
class Shape;
typedef shared_ptr<Shape> ptr_shape;
class Shape
{
public:
	virtual type __type()
	{
		return SHAPE;
	}
public:
	Shape() {}
	~Shape() = default;
	Shape(const Shape& s) = default;
protected:
	static const int UnknownValue = -1;
public:
	virtual double Circumference() const = 0;
	virtual double Area()const = 0; 
	virtual void Print() const = 0;
	virtual void Move(double xoffset, double yoffset) = 0;
	virtual bool isValid()const
	{
		return true;
	}
public:
	friend ptr_shape operator&(const ptr_shape& ptr1, const ptr_shape& ptr2);
	friend ptr_shape operator|(const ptr_shape& ptr1, const ptr_shape& ptr2);
};




#define PI 3.14
class Circle :public Shape
{
public:
	type __type() final override
	{
		return CIRCLE;
	}
public:
	friend ptr_shape operator&(const ptr_shape& ptr1, const ptr_shape& ptr2);
	friend ptr_shape operator|(const ptr_shape& ptr1, const ptr_shape& ptr2);
protected:
	Point _center;
	double _radius;
public:
	Circle(const Point& p, double r)
		:_center(p), _radius(r) {}
	Circle(const Circle& c) = default;
	virtual ~Circle() = default;
public:
	//重写基类虚函数
	virtual double Circumference() const override
	{
		return 2 * PI * _radius;
	}
	virtual double Area() const override
	{
		return PI * _radius * _radius;
	}
	virtual void Print() const override
	{
		cout << typeid(*this).name() << endl;//打印this的类型
		cout << "  the radius is:" << this->_radius << endl;
		cout << "  the center is "  << _center << endl;
		cout << "  the circumference is:" << this->Circumference() << endl;
		cout << "  the area is:" << this->Area() << endl;
		cout << endl;
	}
	virtual void Move(double xoffset, double yoffset) override 
	{
		this->_center._x += xoffset;
		this->_center._y += yoffset;
	}
	virtual bool isValid() const override
	{
		return true;
	}
};


class Polygon :public Shape
{
public:
	type __type() final override
	{
		return POLYGON;
	}
public:
	friend ptr_shape operator&(const ptr_shape& ptr1, const ptr_shape& ptr2);
	friend ptr_shape operator|(const ptr_shape& ptr1, const ptr_shape& ptr2);
	friend pair<double, double> get_height_width(shared_ptr<Polygon>& ptr);//计算长和宽
protected:
	//shared_ptr<Edge>
	vector<shared_ptr<Edge>>_edges;
protected:
	//set的仿函数
	struct cmp
	{
		bool operator()(const Point& p1, const Point& p2) const
		{
			return p1._x + 2 * p1._y < p2._x + 2 * p2._y;
		}
	};
public:
	Polygon(vector<shared_ptr<Edge>>& edges)
		:_edges(edges) {}
	Polygon(double center_x, double center_y, double height, double width);
	Polygon(const Polygon& p) = delete;//不允许对象拷贝
	~Polygon() = default;
public:
	bool is_rectangle();
	virtual double Circumference() const override;
	virtual double Area()const override;
	virtual void Print() const override;
	virtual void Move(double xoffset, double yoffset) override;
	virtual bool isValid()const override;
	bool if_calculate();
};