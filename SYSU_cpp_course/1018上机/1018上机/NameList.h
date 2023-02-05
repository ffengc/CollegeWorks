#pragma once


#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

//可以改进的地方
//重载多点东西

class NameList {
public:
	NameList() {} //自定义类型会去调用自己的构造，所以我们不用写
	~NameList() {}//同理，不用写
	NameList(const NameList& nl) {
		this->_names = nl._names;
	}
	NameList& operator=(const NameList& nl) {
		this->_names = nl._names;
		return *this;
	}
	void addName(const string& s) {
		this->_names.push_back(s);
	}
	void deleteName(const string& s) {
		vector<string>::iterator pos = find(_names.begin(), _names.end(), s);
		if (pos == _names.end()) {
			cout << "找不到该名字" << endl;
			return;
		}
		_names.erase(pos);//不要再使用pos -- 注意迭代器失效
	}
	vector<string>search(const string& sub) {
		vector<string>ret;
		for (int i = 0; i < this->_names.size(); i++) {
			if (_names[i].find(sub) != _names[i].npos) {
				ret.push_back(this->_names[i]);
			}
		}
		return ret;
	}
	void print_arr(vector<string>& arr) {
		vector<string>::iterator it = arr.begin();
		while (it != arr.end()) {
			cout << *it << endl;
			it++;
		}
	}
	void print(int order = 0) {
		//1 升序
		//2 降序
		if (order == 0) {
			print_arr(this->_names);
		}
		else if (order == 1) {
			vector<string>tmp = this->_names;
			sort(tmp.begin(), tmp.end());
			print_arr(tmp);
		}
		else {
			vector<string>tmp = this->_names;
			sort(tmp.begin(), tmp.end(), greater<string>());
			print_arr(tmp);
		}
	}
private:
	vector<string>_names;
};