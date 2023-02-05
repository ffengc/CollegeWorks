#pragma once

#include"Point.h"
/*
2. 定义一个Line类，包含成员变量Point start_, Point end_，Color color_，
表示有向线段的起点和终点，颜色（枚举）。
实现两种构造函数，一种以四个坐标值为参数，另一种以两个Point为参数。
实现Line类的复制构造函数。
*/


class Line {
private:
	enum Color {
		RED,GREEN,BLUE
	};
	Point _start;
	Point _end;
	Color _color;
public:
	friend class Rectangle;
	friend ostream& operator<<(ostream& out, Line& l);
	friend istream& operator>>(istream& in, Line& l);
	Line(float x1 = 0, float y1 = 0, float x2 = 0, float y2 = 0)
		:_color(RED)
	{
		//1.Line设置成Point的友元
		//2.调用Point的赋值构造也行
		this->_start._x = x1;
		this->_start._y = y1;
		this->_end._x = x2;
		this->_end._y = y2;
	}
	Line(const Point& p1, const Point& p2)
		:_start(p1), _end(p2), _color(RED) {}
	~Line() {
		cout << "删除该线段" << endl;
	}
	Line(const Line& line)//拷贝构造
		:_start(line._start), _end(line._end), _color(line._color) {}
	float getLineLength() {
		return _start.GetDistance(_end);
	}
};
//输出一条线
//流插入流提取重载
ostream& operator<<(ostream& out, Line& l) {
	cout << "----------------" << endl;
	out << "起始点：";
	out << l._start << endl;
	out << "终止点：";
	out << l._end << endl;
	out << "颜色：";
	out << l._color << endl;
	cout << "----------------" << endl;
	return out;
}
istream& operator>>(istream& in, Line& l) {
	float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	cout << "请输入起始点坐标:";
	cin >> x1 >> y1;
	cout << "请输入终止点坐标:";
	cin >> x2 >> y2;
	cout << "修改成功" << endl;
	return in;
}