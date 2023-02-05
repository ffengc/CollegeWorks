

/*****************************************************************//**
 * \file   PointVector.h
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

/*********************************************** Point类 ***********************************************/
struct Point {
public:
	Point(int x = 0, int y = 0)
		:_x(x), _y(y) {}
	void print() {
		cout << "(" << _x << "," << _y << ")";
	}
public:
	friend ostream& operator<<(ostream& out, Point& p);
public:
	int _x;
	int _y;
};
ostream& operator<<(ostream& out, Point& p) {
	cout << "(" << p._x << "," << p._y << ")";
	return out;
}


/*********************************************** PointVector类 ***********************************************/


//另外可使用模板
//Vector<Point>
class PointVector {
public:
	//迭代器
	//vector底层迭代器类型就是原生指针 -- 因此不需要构造迭代器类重载核心行为
	typedef Point* iterator;
	typedef const Point* const_iterator;
	iterator begin() {
		return _data;
	}
	iterator end() {
		return _data + _size;
	}
	const_iterator begin()const {
		return _data;
	}
	const_iterator end()const {
		return _data + _size;
	}
	//成员函数
	PointVector();
	PointVector(const PointVector& x);
	template<class InputIterator>    //提供模板 -- const的可以用 不是const的也可以用
	PointVector(InputIterator first, InputIterator end);
	~PointVector();
	void swap(PointVector& v);
	void reserve(size_t n);//提供reserve接口
	void resize(size_t n, const Point& val = Point());//提供resize接口
	void clear();
	void push_back(const Point& x);
	void pop_back();
	Point& at(size_t idx);//返回第idx个元素的引用
	size_t size()const;
	size_t capacity()const;
	bool empty()const;
	Point& front();
	Point& back();
	bool insert(size_t pos, const Point& pt);//在pos之前插入一个Point对象
	bool erase(size_t pos);//删除pos位置的对象
public:
	//运算符重载
	PointVector& operator=(PointVector v);//现代写法，这里不传引用，复用拷贝构造
	Point& operator[](size_t pos);
	PointVector& operator+(const Point& p);
	PointVector& operator+(PointVector& v);
public:
	friend ostream& operator<<(ostream& out, PointVector& pv);
private:
	Point* _data;
	size_t _size;
	size_t _capacity;
};

/*********************************************** PointVector类相关接口定义 ***********************************************/
PointVector::PointVector()
	:_size(0), _capacity(0), _data(nullptr) {}
PointVector::~PointVector() {
	delete[] this->_data;
	_size = _capacity = 0;
}
//迭代器区间拷贝构造
template<class InputIterator> //提供模板 -- const的可以用 不是const的也可以用
PointVector::PointVector(InputIterator first, InputIterator end)
	:_size(0), _capacity(0), _data(nullptr)
{
	while (first != end) {
		push_back(*first);
		++first;
	}
}
//现代写法拷贝构造 -- 复用迭代器区间构造函数
void PointVector::swap(PointVector& v) {
	std::swap(_data, v._data);
	std::swap(_capacity, v._capacity);
	std::swap(_size, v._size);
}
PointVector::PointVector(const PointVector& x) 
	:_size(0), _capacity(0), _data(nullptr)
{
	PointVector tmp(x.begin(), x.end());
	swap(tmp);
}



//现在写法赋值重载 -- 复用！
PointVector& PointVector::operator=(PointVector v) {
	if (this == &v)return*this;
	swap(v);//调用swap，把v换给*this，又因为v是临时变量，可以把*this的旧数据删除，复用了析构和拷贝构造
	return *this;
}
Point& PointVector::operator[](size_t pos) {
	assert(pos >= 0);
	assert(pos < size());
	return _data[pos];
}
PointVector& PointVector::operator+(const Point& p) {
	//在vector末尾插入一个Point对象
	this->push_back(p);
	return *this;
}
PointVector& PointVector::operator+(PointVector& v) {
	//在vector后面append一个vector
	for (int i = 0; i < v.size(); i++) {
		(*this).push_back(v[i]);
	}
	return *this;
}
ostream& operator<<(ostream& out, PointVector& pv) {
	for (int i = 0; i < pv.size(); i++) {
		cout << pv[i] << " ";//此时需要给Point类重载一个<<
	}
	cout << endl;
	return out;
}



size_t PointVector::capacity()const {
	return this->_capacity;
}
size_t PointVector::size()const {
	return this->_size;
}
void PointVector::reserve(size_t n) {
	if (n > capacity()) {
		Point* tmp = new Point[n];
		size_t sz = size();
		if (_data) {
			for (size_t i = 0; i < sz; i++) {
				tmp[i] = _data[i];
			}
			delete[] _data;
		}
		_data = tmp;//赋值给_data
		_capacity = n;
		_size = sz;
	}
}
void PointVector::resize(size_t n, const Point& val) {//给个缺省值，不写默认填(0,0)
	//1.扩容+初始化
	//2.初始化
	//3.删除数据
	if (n > capacity()) {
		reserve(n);//直接调用reserve接口就行了
	}
	if (n > size()) {
		//初始化填值
		while (_size < n) {
			_data[_size] = val;//填值
			_size++;
		}
	}
	else {
		_size = n;//删除值
	}
}
void PointVector::push_back(const Point& v) {
	if (_size == _capacity) {
		reserve(capacity() == 0 ? 4 : capacity() * 2);
	}
	_data[_size] = v;
	++_size;
}
void PointVector::pop_back() {
	assert(_size > 0);//要保证能删
	--_size;
}
void PointVector::clear() {
	_size = 0;
}
Point& PointVector::at(size_t idx) {
	return _data[idx];
}
bool PointVector::empty()const {
	return _size == 0;
}
Point& PointVector::front() {
	assert(_size);
	return _data[0];
}
Point& PointVector::back() {
	assert(_size);
	return _data[_size - 1];
}
//如果按照STL规定使用迭代器插入，需要注意迭代器失效问题
bool PointVector::insert(size_t pos, const Point& pt) {
	//在pos之前插入一个Point对象
	assert(pos >= 0);
	assert(pos < _size);//检查合法性
	//或者这里return false
	if (_size == _capacity) {
		//扩容
		reserve(capacity() == 0 ? 4 : capacity() * 2);
	}
	//挪动数据
	int end = _size - 1;
	
	while (end >= (int)pos) {
		_data[end + 1] = _data[end];
		end--;
	}
	_data[pos] = pt;
	_size++;
	return true;
}
bool PointVector::erase(size_t pos) {
	//删除pos位置的对象
	assert(pos >= 0);
	assert(pos < _size);//检查合法性
	int begin = pos + 1;
	int end = this->_size;
	while (begin < end) {
		_data[begin - 1] = _data[begin];
		++begin;
	}
	--_size;
	return true;
}