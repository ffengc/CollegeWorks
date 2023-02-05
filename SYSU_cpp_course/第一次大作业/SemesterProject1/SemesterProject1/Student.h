


/*****************************************************************//**
 * \file   Student.h
 * \brief  
 * 
 * \author yfc 21312780
 * \date   October 2022
 *********************************************************************/


#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cassert>
using namespace std;


/*********************************************** Student类 ***********************************************/

class Student {
private:
	static const size_t maxCourses = 3;
private:
	int _id;
	string _name;
	string _courseNames[maxCourses];
	double _grades[maxCourses];
	size_t _cnt_Course;
public:
	friend class StudentClass;
	friend bool ascending(const Student* first, const Student* second);
	friend bool descending(const Student* first, const Student* second);
	friend ostream& operator<<(ostream& out, const Student& st);
public:
	Student();
	Student(int id, string name, string* courseNames, double* grades, size_t size);
	Student(const Student& s);
	~Student();
	Student& operator=(const Student& s);
	bool AddCourse(const string& courseName, double grade);
	void SetGrade(const string& courseName, double grade);
	double GetGrade(const string& courseName) const;
	double GetAverageGrade()const;
	void ShowGrades()const;
};

/*********************************************** Student类相关接口定义 ***********************************************/

Student::Student()
	:_cnt_Course(0)
{
	//已经开过空间了
	//_courseNames = new string[maxCourses];
	//_grades = new double[maxCourses];
}
Student::Student(int id, string name, string* courseNames, double* grades, size_t size)
	:_id(id), _name(name), _cnt_Course(size)
{
#if 0 //err 不能memcpy -- memcpy不会调用string的赋值 -- 会越界访问
	memcpy(_courseNames, courseNames, sizeof(string) * maxCourses);
	memcpy(_grades, grades, sizeof(double) * maxCourses);
#endif
	for (int i = 0; i < maxCourses; i++) {
		_courseNames[i] = courseNames[i];
	}
	for (int i = 0; i < maxCourses; i++) {
		_grades[i] = grades[i];
	}
}
Student::Student(const Student& s) {
	//拷贝构造
	this->_id = s._id;
	this->_name = s._name;
#if 0//err
	memcpy(this->_courseNames, s._courseNames, sizeof(string) * maxCourses);
	memcpy(this->_grades, s._grades, sizeof(double) * maxCourses);
#endif
	for (int i = 0; i < maxCourses; i++) {
		_courseNames[i] = s._courseNames[i];
	}
	for (int i = 0; i < maxCourses; i++) {
		_grades[i] = s._grades[i];
	}
	this->_cnt_Course = s._cnt_Course;
}
Student::~Student() {//析构
	_id = 0;
	_name.clear();
	_cnt_Course = 0;
}
Student& Student::operator=(const Student& s) {
	if (this == &s)return*this;
	this->_id = s._id;
	this->_name = s._name;
	//memcpy(this->_courseNames, s._courseNames, sizeof(string) * maxCourses);
	//memcpy(this->_grades, s._grades, sizeof(double) * maxCourses);
	for (int i = 0; i < maxCourses; i++) {
		_courseNames[i] = s._courseNames[i];
	}
	for (int i = 0; i < maxCourses; i++) {
		_grades[i] = s._grades[i];
	}
	this->_cnt_Course = s._cnt_Course;
	return *this;
}
bool Student::AddCourse(const string& courseName, double grade) {
	if (_cnt_Course == maxCourses) {
		cout << "课程已满!" << endl;
		return false;
	}
	string tmp = courseName;
	_courseNames[_cnt_Course] = tmp;//
	_grades[_cnt_Course] = grade;
	cout << "添加成功" << endl;
	++_cnt_Course;
	return true;
}
void Student::SetGrade(const string& courseName, double grade) {
	//先找到名为coureName的课程所对应的下标
	int idx = 0;
	for (; idx < 3; idx++) {
		if (this->_courseNames[idx] == courseName)break;
	}
	if (idx == 3) {
		cout << "找不到该课程信息" << endl;
		return;
	}
	this->_grades[idx] = grade;
	cout << "修改成功" << endl;
}
double Student::GetGrade(const string& courseName) const {
	for (int i = 0; i < 3; i++) {
		if (this->_courseNames[i] == courseName) {
			return this->_grades[i];
		}
	}
	cout << "找不到该课程信息" << endl;
	return -1;//找不到该课程信息
}
double Student::GetAverageGrade()const {
	double grade_sum = 0;
	for (int i = 0; i < this->_cnt_Course; i++) {
		grade_sum += this->_grades[i];
	}
	return grade_sum / this->_cnt_Course;
}
void Student::ShowGrades()const {
	cout << "=====================================" << endl;
	cout << "Name:" << this->_name << endl;
	cout << "id:" << this->_id << endl;
	for (int i = 0; i < this->_cnt_Course; i++) {
		cout << this->_courseNames[i] << ":" << this->_grades[i] << endl;
	}
	cout << "=====================================" << endl;
}
//重载流提取
ostream& operator<<(ostream& out, const Student& st) {
	cout << "=====================================" << endl;
	cout << "Name:" << st._name << endl;
	cout << "id:" << st._id << endl;
	for (int i = 0; i < st._cnt_Course; i++) {
		cout << st._courseNames[i] << ":" << st._grades[i] << endl;
	}
	cout << "=====================================" << endl;
	return out;
}



/*********************************************** __StudentClass_iterator类 ***********************************************/

//StudentClass迭代器 -- 用于遍历
template<class Ref,class Ptr> //const类型可以，不是const类型也可以
struct __StudentClass_iterator {
public:
	Ptr _pointer;
public:
	__StudentClass_iterator(Ptr pointer)
		:_pointer(pointer) {}
	//控制迭代器核心行为
	Student operator*() {
		return **(this->_pointer);//因为StudentClass存的是数组指针
	}
	Ref operator->() {
		return *(this->_pointer);
	}
	__StudentClass_iterator& operator++() { //前置++
		_pointer++;
		return *this;
	}
	__StudentClass_iterator operator++(int) { //后置++
		__StudentClass_iterator tmp(*this);//暂时保存一下现在的对象
		_pointer++;
		return tmp;
	}
	//--是同一个道理，不重复实现了，如果只正向遍历用不到--
	bool operator!=(const __StudentClass_iterator& it)const {
		return _pointer != it._pointer;
	}
	bool operator==(const __StudentClass_iterator& it)const {
		return _pointer == it._pointer;
	}
};



/*********************************************** StudentClass类 ***********************************************/

class StudentClass {
private:
	static const size_t maxStudents = 20;
	static size_t _studentCount;
	string _code;
	Student* _students[maxStudents];
public:
	//只要是容器 -- 我们就可以提供迭代器
	typedef __StudentClass_iterator<Student*&, Student**> iterator;
	typedef __StudentClass_iterator<const Student*&, const Student**> const_iterator;
	iterator begin() {
		return iterator(_students);
	}
	iterator end() {
		return iterator(_students + _studentCount);
	}
	const_iterator begin()const {
		return const_iterator((const Student**)_students);
	}
	const_iterator end()const {
		return const_iterator((const Student**)_students + _studentCount);
	}
public:
	StudentClass();
	StudentClass(string code, Student** students, size_t cnt_stu);
	~StudentClass();
	StudentClass(const StudentClass& sc);
	StudentClass& operator=(const StudentClass& sc);
	//存取函数
	void Addstudent(const Student* student);
	void ShowStudent(int id)const;
	void ShowStudentByIdOrder(bool(*compare)(const Student*, const Student*));
	static void showStudentCount() {
		cout << "现在已有的学生数量为:" << _studentCount << endl;
	}
};
size_t StudentClass::_studentCount = 0;



/*********************************************** StudentClass类相关接口定义 ***********************************************/

StudentClass::StudentClass()
{
	++_studentCount;
}
StudentClass::StudentClass(string code, Student** students, size_t cnt_stu)
	:_code(code)
{
	_studentCount = cnt_stu;
	memcpy(this->_students, students, sizeof(Student*) * cnt_stu);
}
StudentClass::~StudentClass() { //析构
	_studentCount = 0;
	_code.clear();
}
StudentClass::StudentClass(const StudentClass& sc) {
	++_studentCount;
	this->_studentCount = sc._studentCount;
	this->_code = sc._code;
	memcpy(this->_students, sc._students, sizeof(Student*) * sc._studentCount);
}
StudentClass& StudentClass::operator=(const StudentClass& sc) {
	if (this == &sc)return*this;
	//++_studentCount;
	this->_studentCount = sc._studentCount;
	this->_code = sc._code;
	memcpy(this->_students, sc._students, sizeof(Student*) * sc._studentCount);
	return *this;
}
//存取函数
void StudentClass::Addstudent(const Student* student) {
	assert(this->_studentCount != maxStudents);//判断是否能放得下
	//Student(int id, string name, string* courseNames, double* grades, size_t size)
	Student* tmp = new Student((*student));
	this->_students[this->_studentCount] = tmp;
	++_studentCount;
}
void StudentClass::ShowStudent(int id)const {
	for (int i = 0; i < _studentCount; i++) {
		if (this->_students[i]->_id == id) {
			//展示学生信息
			cout << "****************************************" << endl;
			cout << "Name:" << this->_students[i]->_name << endl;
			cout << "id:" << this->_students[i]->_id << endl;
			this->_students[i]->ShowGrades();//调用展示成绩的接口
			cout << "****************************************" << endl;
			return;
		}
	}
}
void StudentClass::ShowStudentByIdOrder(bool(*compare)(const Student*, const Student*)) {
	sort(this->_students, this->_students + _studentCount, compare);
	//展示所有学生信息
	for (int i = 0; i < _studentCount; i++) {
		//展示学生信息
		this->_students[i]->ShowGrades();//调用展示成绩的接口
	}
}