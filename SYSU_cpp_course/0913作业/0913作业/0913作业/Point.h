#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<cmath>
using namespace std;


/*
1.定义一个Point类，包含成员变量float x_, float y_，
表示点的二维坐标(x, y)。实现成员函数GetDistance(Point &p)，
返回两点之间的距离。实现成员函数GetMidPoint(Point &p)，返回两点之间的中点。
自行实现Point类的构造函数、复制构造函数和析构函数。
*/
class Point {
private:
	float _x;
	float _y;
public:
	friend class Line;
	friend class Rectangle;
	friend ostream& operator<<(ostream& out, const Point& p);
	friend istream& operator>>(istream& in, Point& p);
	Point(float x = 0, float y = 0)//全缺省默认构造
		:_x(x), _y(y) {}
	~Point() {
		cout << "删除点(" << _x << "," << _y << ")" << endl;
	}
	//拷贝构造
	Point(const Point& p) //深拷贝
		:_x(p._x), _y(p._y)
	{}
	float GetDistance(const Point& p) {
		float distance = sqrt(pow(this->_x - p._x, 2) + pow(this->_y - p._y, 2));
		return distance;
	}
	Point GetMidPoint(const Point& p) {//只能传值返回
		Point mid;
		mid._x = (this->_x + p._x) / 2.0f;
		mid._y = (this->_y + p._y) / 2.0f;
		return mid;
	}
};
//输出点
ostream& operator<<(ostream& out, const Point& p) {
	out << "(" << p._x << "," << p._y << ")";
	return out;
}
//输入 -- 改变一个点
istream& operator>>(istream& in, Point& p) { //浅拷贝过来，不然改不了
	float x = 0;
	float y = 0;
	cin >> x >> y;
	p._x = x;
	p._y = y;
	return in;
}