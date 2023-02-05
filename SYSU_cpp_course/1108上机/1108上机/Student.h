

/*****************************************************************//**
 * \file   Student.h
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

class Student{
protected:
	string _name;
	string _id;
public:
	Student() {}
	Student(string name, string id)
		:_name(name), _id(id) {}
	Student(const Student& st)
		:_name(st._name),_id(st._id){}
	virtual ~Student() {} //触发多态条件
public:
	inline void GetName(const string& name) {
		this->_name = name;
	}
	inline void GetId(const string& id) {
		this->_id = id;
	}
	virtual void Display() {
		cout << "-------------------" << endl;
		cout << "this->name:" << this->_name << endl;
		cout << "this->id:" << this->_id << endl;
		cout << "-------------------" << endl;
	}
};
class ScienceStudent :public Student {
protected:
	string _science_number;
public:
	ScienceStudent()
		:_science_number(), Student() {}
	ScienceStudent(string name, string id,string science_number)
		:Student(name, id), _science_number(science_number){}
	ScienceStudent(const ScienceStudent& sst)
		:Student(sst._name, sst._id), _science_number(sst._science_number) {}
	virtual ~ScienceStudent(){}
public:
	void Display() override { //这里符合重写条件 -- 可以触发多态
		cout << "-------------------" << endl;
		cout << "this->name:" << this->_name << endl;
		cout << "this->id:" << this->_id << endl;
		cout << "this->science_number:" << this->_science_number << endl;
		cout << "-------------------" << endl;
	}
};
class EngineeringStudent :public Student {
protected:
	string _engineering_number;
public:
	EngineeringStudent()
		:_engineering_number(), Student() {}
	EngineeringStudent(string name, string id, string engineering_number)
		:Student(name, id), _engineering_number(engineering_number) {}
	EngineeringStudent(const EngineeringStudent& est)
		:Student(est._name, est._id), _engineering_number(est._engineering_number) {}
	virtual ~EngineeringStudent() {}
public:
	void Display() override { //这里符合重写条件 -- 可以触发多态
		cout << "-------------------" << endl;
		cout << "this->name:" << this->_name << endl;
		cout << "this->id:" << this->_id << endl;
		cout << "this->engineering_number:" << this->_engineering_number << endl;
		cout << "-------------------" << endl;
	}
};
void print(Student** st_arr, int sz) {
	//基类指针调用 -- 触发多态
	for (int i = 0; i < sz; i++) {
		st_arr[i]->Display();
	}
}

void printMore(Student** st_arr, int sz){
	for (int i = 0; i < sz; i++) {
		//方法1：使用typeid.name()方法
		cout << typeid(*(st_arr[i])).name() << ":" << endl;
		st_arr[i]->Display();
	}
}