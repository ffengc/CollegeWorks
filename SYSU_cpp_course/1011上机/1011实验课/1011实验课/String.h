#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

#ifndef STRNGBAD_H_
#define STRNGBAD_H_
class StringBad {
private:
	char* str;
	int len;
	static int num_strings;
public:
	StringBad(const char* s);
	StringBad();
	~StringBad();
	//要去实现深拷贝
	StringBad(const StringBad& s);
	//赋值重载
	StringBad& operator=(const StringBad& s);
	friend ostream& operator<<(ostream& cout, const StringBad& st);
};
int StringBad::num_strings = 0;
#endif
StringBad::StringBad(const char* s) {
	len = std::strlen(s);
	str = new char[len + 1];
	strcpy(str, s);
	num_strings++;
	cout << num_strings << ":\"" << str << "\"object created\n";
}
StringBad::StringBad() {
	len = 4;
	str = new char[4];
	strcpy(str, "C++");
	num_strings++;
	cout << num_strings << ":\"" << str << "\"default object created\n";
}
StringBad::~StringBad() {
	cout << "\"" << str << "\"object deleted,";
	--num_strings;
	cout << num_strings << "left\n";
	delete[]str;
}
ostream& operator<<(ostream& cout, const StringBad& st) {
	cout << st.str;
	return cout;
}
StringBad::StringBad(const StringBad& s) {
	str = new char[s.len + 1];
	strcpy(str, s.str);
}
StringBad& StringBad::operator=(const StringBad& s) {
	this->str = new char[s.len + 1];
	strcpy(str, s.str);
	return *this;
}



class StringLeaky {
private:
	char* str;
	size_t len;
public:
	StringLeaky(const char* s) {
		len = strlen(s);
		str = new char[len + 1];
		strcpy(str, s);
	}
	//添加析构函数
	~StringLeaky() {
		len = 0;
		delete[]str;
	}
	int GetLen()const {
		return len;
	}
};
void EatMemory() {
	StringLeaky str("Hello, I'm from SYSU.");
	cout << "Allocated " << str.GetLen() << " bytes memory,without free\n";
}