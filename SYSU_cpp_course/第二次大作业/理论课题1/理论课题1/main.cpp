#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
#include<assert.h>
using namespace std;
#elif
#endif

enum Sex
{
	MALE = 0, FEMALE = 1
};


/**
 * 定义一个Person抽象基类，包含姓名，性别等基本属性，以及若干纯虚函数Work, Run等.
 */
class Person
{
public:
	virtual void Work()const = 0;
	virtual void Run()const = 0;
public:
	Person(string name, Sex sex)
		:_name(name), _sex(sex) {}
	Person(const Person& p) = default;
	~Person() = default;
	virtual void get_person_info() const 
	{}
protected:
	string _name;
	Sex _sex;
};

/**
 * 定义一个派生类Student，额外包含学校，年级等属性，添加新的虚函数Study，ReportGrades；
 */
class Student :public Person
{
public:
	Student(string name, Sex sex, string school, string grade)
		:Person(name, sex), _school(school), _grade(grade) {}	
	Student(const Student& s) = default;
	~Student() = default;
public:
	virtual void Work()const
	{
		cout << "Student::Work()" << endl;
	}
	virtual void Run()const
	{
		cout << "Student::Run()" << endl;
	}
	virtual void Study()const
	{
		cout << "Student::Study()" << endl;
	}
	virtual void ReportGrades()const
	{
		cout << "Student::ReportGrades()" << endl;
	}
	virtual void set_info()
	{
		//可以用多态，Student也可以定义以一个set_info
		cout << "CollegeStudent::set_grade() called" << endl;
		cout << "please input the name:"; cin >> this->_name;
		cout << "please input the sex(male/female)";
		string sex_tmp;
		cin >> sex_tmp;
		if (sex_tmp == "male")this->_sex = MALE;
		else if (sex_tmp == "female")this->_sex = FEMALE;
		else assert(false);//输入有误
		cout << "please input the school name:"; cin >> this->_school;
		cout << "please input the grade name"; cin >> this->_grade;
	}
public:
	virtual void get_person_info() const
	{
		cout << "======================================" << endl;
		cout << "Student::_name" << " " << this->_name << endl;
		cout << "Student::_sex" << " " << this->_sex << endl;
		cout << "Student::_school" << " " << this->_school << endl;
		cout << "Student::_grade" << " " << this->_grade << endl;
		cout << "Student::function call:" << endl;
		this->Work();
		this->Run();
		this->Study();
		this->ReportGrades();
		//this->set_grade(); //暂时不调用了 -- 影响打印整体性
		cout << "======================================" << endl;
	}
protected:
	string _school;
	string _grade;
};



/**
 * 定义一个CollegeStudent的派生类，额外包含专业、学生社团等属性.
 */
class CollegeStudent :public Student
{
public:
	CollegeStudent(string name, Sex sex, string school,
		string grade, string major, string student_organizations)
		:Student(name, sex, school, grade), _major(major), 
		_student_organizations(student_organizations) {}
	CollegeStudent(const CollegeStudent& cs) = default;
	~CollegeStudent() = default;
public:
	virtual void set_grade() //重写基类虚函数
	{
		cout << "CollegeStudent::set_grade() called" << endl;
		cout << "please input the name:"; cin >> this->_name;
		cout << "please input the sex(male/female)";
		string sex_tmp;
		cin >> sex_tmp;
		if (sex_tmp == "male")this->_sex = MALE;
		else if (sex_tmp == "female")this->_sex = FEMALE;
		else assert(false);//输入有误
		cout << "please input the school name:"; cin >> this->_school;
		cout << "please input the grade name"; cin >> this->_grade;
		cout << "please input the major"; cin >> this->_major;
		cout << "please input the student organizations"; cin >> this->_student_organizations;
	}
public:
	virtual void Work()const
	{
		cout << "CollegeStudent::Work()" << endl;
	}
	virtual void Run()const
	{
		cout << "CollegeStudent::Run()" << endl;
	}
	virtual void Study()const
	{
		cout << "CollegeStudent::Study()" << endl;
	}
	virtual void ReportGrades()const
	{
		cout << "CollegeStudent::ReportGrades()" << endl;
	}
public:
	virtual void get_person_info()const
	{
		cout << "======================================" << endl;
		cout << "CollegeStudent::_name" << " " << this->_name << endl;
		cout << "CollegeStudent::_sex" << " " << this->_sex << endl;
		cout << "CollegeStudent::_school" << " " << this->_school << endl;
		cout << "CollegeStudent::_grade" << " " << this->_grade << endl;
		cout << "CollegeStudent::_major" << " " << this->_major << endl;
		cout << "CollegeStudent::_student_organizations" << " " << this->_student_organizations << endl;
		cout << "CollegeStudent::function call:" << endl;
		this->Work();
		this->Run();
		this->Study();
		this->ReportGrades();
		//this->set_grade(); //暂时不调用了 -- 影响打印整体性
		cout << "======================================" << endl;
	}
protected:
	string _major;
	string _student_organizations;
};

/**
 * 实现一个report(const Person *)函数，打印对用对象的所有属性，并调用其所有函数.
 * 这里为了打印的整体性 -- 不调用类的set_grade()接口
 */
void report(const Person* pPerson)
{
	cout << typeid(*pPerson).name() << endl;//打印类型名
	pPerson->get_person_info();
	cout << endl << endl;
}

/**
 * main函数里，实例化2个Student对象，2个CollegeStudent对象，存放在一个数组里面，然后循环调用report函数。.
 */
int main()
{
	Student s1("James", MALE, "NBA", "18");
	Student s2("Curry", MALE, "NBA", "14");
	CollegeStudent cs1("Jack", MALE, "SYSU", "1","Math","baseball");
	CollegeStudent cs2("Sam", FEMALE, "SYSU", "2", "Chinese", "basketball");
	Student* student_info_list[] = { &s1,&s2,&cs1,&cs2 };
	for (auto e : student_info_list)
	{
		report(e);
	}
	return 0;
}