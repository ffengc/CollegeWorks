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


//题目要求设计了一个菱形继承
class Vehicle {
public:
	size_t maxSpeed = 0;
	size_t Weight = 0;
public:
	Vehicle() = default;
	Vehicle(const Vehicle& v) = default;
	~Vehicle() = default;
public:
	virtual void run() {
		cout << "Vehicle::run()" << endl;
	}
	virtual void stop() {
		cout << "Vehicle::stop()" << endl;
	}
};
class Bicycle :virtual public Vehicle {
public:
	size_t height = 0;
	virtual void run() {
		cout << "Bicycle::run()" << endl;
	}
	virtual void stop() {
		cout << "Bicycle::stop()" << endl;
	}
};
class Automobile :virtual public Vehicle {
public:
	size_t seatCount = 0;
	virtual void run() {
		cout << "Automobile::run()" << endl;
	}
	virtual void stop() {
		cout << "Automobile::stop()" << endl;
	}
};
class Motocycle :public Bicycle, public Automobile {
public:
	void run() {
		cout << "Motocycle::run()" << endl;
	}
	void stop() {
		cout << "Motocycle::stop()" << endl;
	}
};


void test_Vehicle() {
	Vehicle v;
	Automobile a;
	Motocycle m;
	//不采用虚继承会产生冗余性和二义性问题
	m.maxSpeed = 10;//此时的maxSpeed都是同一个变量了
	//m.run();
	//此外可以采用虚函数触发多态
	Vehicle* pv = &m;//这里会有一个切片
	pv->run();//多态触发
	cout << endl;
}