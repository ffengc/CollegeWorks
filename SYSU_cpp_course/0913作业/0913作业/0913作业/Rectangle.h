#pragma once

#include"Line.h"

/*
3. 定义一个Rectangle类，包含四个Line对象，
实现构造和复制构造函数。实现求周长函数，
以及draw()绘图函数（模拟即可）
*/

class Rectangle {
private:
	Line _line1;//1
	Line _line2;//2
	Line _line3;//1
	Line _line4;//2
	bool is_rectangle_Valid() {
		float x1 = _line1._start._x;
		float y1 = _line1._start._y;
		float x2 = _line2._start._x;
		float y2 = _line2._start._y; 
		float x3 = _line3._start._x;
		float y3 = _line3._start._y;
		float x4 = _line4._start._x;
		float y4 = _line4._start._y;
		//四个点的重心
		float x0 = (x1 + x2 + x3 + x4) / 4.0;
		float y0 = (y1 + y2 + y3 + y4) / 4.0;
		float dist1_square = pow(abs(x0 - x1), 2) + pow(abs(y0 - y1), 2);
		float dist2_square = pow(abs(x0 - x2), 2) + pow(abs(y0 - y2), 2);
		float dist3_square = pow(abs(x0 - x3), 2) + pow(abs(y0 - y3), 2);
		float dist4_square = pow(abs(x0 - x4), 2) + pow(abs(y0 - y4), 2);
		return (dist1_square == dist2_square && dist2_square == dist3_square 
			&& dist3_square == dist4_square)
			? true : false;
	}
public:
	//矩形对象生成不允许无参传递
	Rectangle(const Line& l1, const Line& l2, const Line& l3, const Line& l4)
		:_line1(l1), _line2(l2), _line3(l3), _line4(l4)
	{
		//检查矩形是否合法
		if (!is_rectangle_Valid()) {
			cout << "该矩形对象不合法!" << endl;
			exit(-1);//直接退出程序
			//Rectangle::~Rectangle();//直接析构
		}
	}
	~Rectangle() {
		cout << "销毁该矩形对象" << endl;
	}
	Rectangle(const Rectangle& r) 
		:_line1(r._line1),_line2(r._line2),_line3(r._line3),_line4(r._line4)
	{}
	void draw() {
		cout << "#########################" << endl;
		cout << "这个矩形四条边分别为：" << endl;
		cout << _line1 << _line2 << _line3 << _line4 << endl;
		cout << "#########################" << endl;
	}
};