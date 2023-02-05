#pragma once

#ifdef __cplusplus
#elif
#endif

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
#include<set>
#include<functional>
#include<numeric>
using namespace std;


class Student {
protected:
	string _name;
	string _id;
	string _college_name;
public:
	Student(string name = "小明", string id = "101", string college_name = "SYSU")
		:_name(name), _id(id), _college_name(college_name) {}
	Student(const Student& s)
		:_name(s._name), _id(s._id), _college_name(s._college_name) {}
	~Student() {
		cout << "~Student()" << endl;
	}
public:
	void print() {
		cout << endl << endl;
		cout << "*******************" << endl;
		cout << "名字:" << this->_name << endl;
		cout << "学号:" << this->_id << endl;
		cout << "学校:" << this->_college_name << endl;
		cout << "*******************" << endl;
	}
};
class GraduateStudent final : public Student {
protected:
	string _research_direction;
	string _tutor_name;
public:
	GraduateStudent(string research_direction = "programming",
		string tutor_name = "TanGuang")
		:Student(),_research_direction(research_direction), _tutor_name(tutor_name) {}
	GraduateStudent(const GraduateStudent& gs)
		:Student(), _research_direction(gs._research_direction), _tutor_name(gs._tutor_name) {}
	~GraduateStudent() {
		cout << "~GraduateStudent()" << endl;
	}
public:
	void print() {
		Student::print();
		cout << "研究方向:" << this->_research_direction << endl;
		cout << "导师:" << this->_tutor_name << endl;
		cout << "*******************" << endl;
	}
};


void test_student() {
	//Student s;
	//s.print();
	GraduateStudent gs;
	gs.print();
}