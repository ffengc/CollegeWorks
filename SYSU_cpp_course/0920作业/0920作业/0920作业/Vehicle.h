#pragma once
#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_set>
#include<cassert>
#include<functional>

using namespace std;

/*
1.定义一个Vehicle类，包含成员变量：float x_, float y_, float vx _, float vy_, 
	float width_, float height_以及static int vCount_，表示已经创建的车辆对象个数。
其中：(x_, y_)表示车辆中心的初始位置坐标，单位m，(vx_,vy_)表示车辆的初始速度，
	单位m/s，width_和height_分别表示车辆的宽和长，单位m；
实现Vehicle类的构造函数、复制构造函数、析构函数；
	其中：vx_和vy_的默认值分别为：6，0；width和height的默认值分别为2，4
实现void Display()函数，显式车辆基本信息；
实现成员函数IsCollision(const Vehcile &veh)：判断自身是否与车辆veh发生了碰撞，
	如果发生碰撞，则返回1，否则返回0。
*/

/// <summary>
/// 如果车的_vy不为0，车子是斜着的吗？
/// </summary>
class Vehicle {
private:
	float _x;
	float _y;
	float _vx;
	float _vy;
	float _width;
	float _height;
public:
	static int _vCount;
public:
	friend struct hash_name;
	friend ostream& operator<<(ostream& out, Vehicle& v);
	Vehicle(float x = 0, float y = 0, float vx = 6, float vy = 0, float width = 2, float height = 4)
		:_x(x), _y(y), _vx(vx), _vy(vy), _width(width), _height(height)
	{
		_vCount++;
	}
	~Vehicle() {
		//cout << "删除该车辆信息" << endl;
		--_vCount;
	}
	Vehicle(const Vehicle& v)
		:_x(v._x), _y(v._y), _vx(v._vx), _vy(v._vy), _width(v._width), _height(v._height) {
		_vCount++;
	}
	//展示车辆信息
	//1.this->Display()
	//2.operator<<
	void Display() {
		cout << "----------------------------" << endl;
		cout << "车辆中心的位置为:(" << _x << "," << _y << ")处" << endl;
		cout << "车辆速度为:(" << _vx << "," << _vy << ")" << endl;
		cout << "车辆宽度为:" << _width << endl;
		cout << "车辆长度为:" << _height << endl;
		cout << "----------------------------" << endl;
	}
	bool isCollision(const Vehicle& veh)const {
		///现假设即使车辆y方向上有速度 -- 车子也是直的
		float y1_g = this->_y + this->_width / 2.0;
		float y1_m = this->_y - this->_width / 2.0;
		float y2_g = veh._y + veh._width / 2.0;
		float y2_m = veh._y - veh._width / 2.0;

		float x1_g = this->_x + this->_height / 2.0;
		float x1_m = this->_x - this->_height / 2.0;
		float x2_g = veh._x + veh._height / 2.0;
		float x2_m = veh._x - veh._height / 2.0;
		//一共四种重叠的情况
		if (x1_g <= x2_g && x1_g >= x2_m && y1_g <= y2_g && y1_g >= y2_m)return true;
		if (x1_g <= x2_g && x1_g >= x2_m && y1_m <= y2_g && y1_m >= y2_m)return true;
		if (x1_m <= x2_g && x1_m >= x2_m && y1_m <= y2_g && y1_m >= y2_m)return true;
		if (x1_m <= x2_g && x1_m >= x2_m && y1_g <= y2_g && y1_g >= y2_m)return true;
		return false;
	}
	bool operator==(const Vehicle& v) const {
		return v._x == _x && v._y == _y && v._vx == _vx && v._vy == _vy && v._width == _width && v._height == _height;
	}
};
int Vehicle::_vCount = 0;//static变量在类外初始化
ostream& operator<<(ostream& out, Vehicle& v) {
	cout << "----------------------------" << endl;
	cout << "车辆中心的位置为:(" << v._x << "," << v._y << ")处" << endl;
	cout << "车辆速度为:(" << v._vx << "," << v._vy << ")" << endl;
	cout << "车辆宽度为:" << v._width << endl;
	cout << "车辆长度为:" << v._height << endl;
	cout << "----------------------------" << endl;
	return out;
}