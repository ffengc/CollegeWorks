/*****************************************************************//**
 * \file   Shape.h
 * \brief  
 * 
 * \author Administrator
 * \date   November 2022
 *********************************************************************/
#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include<map>
#include<set>
using namespace std;

#include<iostream>
#include<cmath>

class Shape{
protected:
	double _area;
	double _length;
public:
	Shape(int area = 0, int length = 0)
		:_area(area), _length(length) {}
	Shape(const Shape& s) = default;
	virtual ~Shape() = default;
public:
	virtual void GetArea() = 0 {}
	virtual void GetLength() = 0 {}
	virtual void Display() = 0 {}
};
class Triangle:public Shape{
protected:
	double _a = 0;
	double _b = 0;
	double _c = 0;
public:
	Triangle(double a = 0, double b = 0, double c = 0) {
		this->_a = a;
		this->_b = b;
		this->_c = c;
		this->_area = this->get_tri_area();
	}
	Triangle(const Triangle& t) = default;
	~Triangle() = default;
	inline double get_tri_area() const {
		double half_c = (_a + _b + _c) / 2;
		return sqrt(half_c * (half_c - _a) * (half_c - _b) * (half_c - _c));
	}
	void input_edges(int a = 0, int b = 0, int c = 0) {
		this->_a = a;
		this->_b = b;
		this->_c = c;
	}
	void Display() override {
		double round = _a + _b + _c;
		cout << "----------------------" << endl;
		cout << "a:" << this->_a << endl;
		cout << "b:" << this->_b << endl;
		cout << "c:" << this->_c << endl;
		cout << "the_area_is:" << this->_area << endl;
		cout << "the_rount_is:" << round << endl;
		cout << "----------------------" << endl;
	}
	void GetArea() {
		cout << "the_area_is:" << this->_area << endl;
	}
	void GetLength() {
		double round = _a + _b + _c;
		cout << "the_rount_is:" << round << endl;
	}
};
#define PI 3.14
class Circle :public Shape {
protected:
	double _r = 0;
public:
	Circle(double r = 0) {
		this->_r = r;
		this->_area = this->get_cir_area();
	}
	Circle(const Circle& c) = default;
	~Circle() = default;
	inline double get_cir_area() const {
		return PI * this->_r * this->_r;
	}
	void input_edges(int r = 0) {
		this->_r = r;
	}
	void Display() override {
		double round = 2 * PI * this->_r;
		cout << "----------------------" << endl;
		cout << "r:" << this->_r << endl;
		cout << "the_area_is:" << this->_area << endl;
		cout << "the_rount_is:" << round << endl;
		cout << "----------------------" << endl;
	}
	void GetArea() {
		cout << "the_area_is:" << this->_area << endl;
	}
	void GetLength() {
		double round = 2 * PI * this->_r;
		cout << "the_rount_is:" << round << endl;
	}
};

void printa(Shape** shape_arr, int sz) {
	for (int i = 0; i < sz; i++) {
		//指针调用 -- 触发多态
		cout << typeid(*(shape_arr[i])).name() << ":" << endl;
		shape_arr[i]->Display();
	}
}