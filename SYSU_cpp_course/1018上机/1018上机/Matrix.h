


/*****************************************************************//**
 * \file   Matrix.h
 * \brief  
 * 
 * \author Administrator
 * \date   October 2022
 *********************************************************************/
#pragma once


#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;


//为什么一个矩阵非要存在一个一维数组里面？
//用一个double**_data
//或者数组指针不好吗？


//可以继续优化的地方
//1.重载IO
//2.矩阵的打印用printf好点 -- 对齐 -- 更美观


//重载[][]


class Matrix {
public:
	Matrix(int sz = 0, int row = 0, int col = 0)
		:_data(nullptr), _nRows(row), _nColumns(col) {
		_data = new double[sz];//提前开好sz的空间
	}
	Matrix(vector<vector<double>>arr)
		:_nRows(arr.size()), _nColumns(arr[0].size())
	{
		//用一个二维vector构造
		int idx = 0;//控制_data[]
		_data = new double[arr.size() * arr[0].size()];
		for (int i = 0; i < _nRows; i++) {
			for (int j = 0; j < _nColumns; j++) {
				_data[idx] = arr[i][j];
				idx++;
			}
		}
	}
	~Matrix() {
		delete[] _data;
		_nRows = 0;
		_nColumns = 0;
	}
	Matrix(const Matrix& m) {
		int sz = m._nRows * m._nColumns;
		_data = new double[sz];
		memcpy(_data, m._data, sizeof(double) * sz);
		this->_nColumns = m._nColumns;
		this->_nRows = m._nRows;
	}
	Matrix& operator=(const Matrix& m) {
		assert(m._nColumns == this->_nColumns && m._nRows == this->_nRows);//判断操作合法性
		int sz = this->_nColumns * this->_nRows;
		memcpy(_data, m._data, sz*sizeof(double));
		return *this;
	}
	size_t nElements() {
		return this->_nColumns * this->_nRows;
	}
	size_t size() {
		return this->nElements() * sizeof(double);
	}
	double* operator[](int row) {
		assert(row && row < this->_nRows);
		return this->_data + row * this->_nColumns; //返回地址就行
	}
	// 1 2 3 4
	// 5 6 7 8
	void set(int x, int y, double val) {
		//设置坐标为(x,y)的值 注意,x从0开始
		int idx = x * _nColumns + y;
		this->_data[idx] = val;
	}
	double get(int x, int y) {
		int idx = x * _nColumns + y;
		return _data[idx];
	}
	void print_Row(int row) {
		//输出某行的值
		int start = row * _nColumns;
		for (int i = 0; i < _nColumns; i++) {
			cout << _data[start++] << " ";
		}
		cout << endl;
	}
	void print_Col(int col) {
		//输出某列的值
		int start = col;
		for (int i = 0; i < _nRows; i++) {
			cout << _data[start] << " ";
			start += _nColumns;
		}
		cout << endl;
	}
	void print_Matrix() {
		//为了打印出矩阵的样子 -- 采用双层循环
		int sz = this->_nColumns * this->_nRows;
		for (int i = 0; i < _nRows; i++) {
			for (int j = 0; j < _nColumns; j++) {
				cout << _data[i * _nColumns + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	Matrix& add(const Matrix& m) {
		assert(m._nColumns == this->_nColumns && m._nRows == this->_nRows);//判断操作合法性
		int sz = this->_nColumns * this->_nRows;
		for (int i = 0; i < sz; i++) {
			_data[i] += m._data[i];
		}
		return *this;
	}
	Matrix& sub(const Matrix& m) {
		assert(m._nColumns == this->_nColumns && m._nRows == this->_nRows);//判断操作合法性
		int sz = this->_nColumns * this->_nRows;
		for (int i = 0; i < sz; i++) {
			_data[i] -= m._data[i];
		}
		return *this;
	}
public:
	//重载+/-
	Matrix operator+(const Matrix& m) {
		assert(m._nColumns == this->_nColumns && m._nRows == this->_nRows);//判断操作合法性
		int sz = this->_nColumns * this->_nRows;
		Matrix ans(sz, m._nRows, m._nColumns);
		for (int i = 0; i < sz; i++) {
			ans._data[i] = m._data[i] + this->_data[i];
		}
		return ans;//不能传引用
	}
	Matrix operator-(const Matrix& m) {
		assert(m._nColumns == this->_nColumns && m._nRows == this->_nRows);//判断操作合法性
		int sz = this->_nColumns * this->_nRows;
		Matrix ans(sz, m._nRows, m._nColumns);
		for (int i = 0; i < sz; i++) {
			ans._data[i] = this->_data[i] - m._data[i];
		}
		return ans;//不能传引用
	}
private:
	double* _data;
	size_t _nRows;
	size_t _nColumns;
};