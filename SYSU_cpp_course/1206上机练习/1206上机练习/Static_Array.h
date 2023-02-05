#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include<functional>
#include<algorithm>
#include<iostream>
#include<initializer_list>
#include<assert.h>
#include<numeric>
using namespace std;

//template<class T, class SumFunction, class CmpFunction, size_t N>
template<class T, size_t N>
class StaticArray 
{
protected:
	T* __arr;
	size_t __size;
	size_t __capacity = N;
public:
	StaticArray()
		:__size(0), __arr(new T[N]) {}
	StaticArray(const initializer_list<T>& list)
	{
		assert(list.size() <= N);
		__size = list.size();
		__arr = new T[list.size()];
		int i = 0;
		for (const auto& e : list)
		{
			__arr[i++] = e;
		}
	}
	~StaticArray()
	{
		delete[] __arr;
	}
	StaticArray(const StaticArray& sarr)
		:__size(sarr.__size), __capacity(sarr.__capacity)
	{
		__arr = new T[this->__capacity];
		for (size_t i = 0; i < sarr.__size; i++)
		{
			__arr[i] = sarr.__arr[i];
		}
	}
public:
	void push_back(const T& val)
	{
		assert(__size <= __capacity - 1);
		__arr[__size++] = val;
	}
	void pop_back()
	{
		assert(__size > 0);
		__size--;
	}
	size_t size()
	{
		return this->__size;
	}
public:
	//≈≈–Ú≤È’“«Û∫Õ
	template<class Cmp = nullptr>
	void sort(Cmp& cmp)
	{
		if(cmp)
			std::sort(__arr, __arr + __size, cmp);
		else
			std::sort(__arr, __arr + __size);
	}
	size_t find(const T& val)
	{
		assert(typeid(val).name() == typeid(T).name());
		int ret_idx = -1;
		for (size_t i = 0; i < __size; i++)
		{
			if (__arr[__size] == val)
			{
				ret_idx = i;
				break;
			}
		}
		return ret_idx;
	}
	T sum()
	{
		return accumulate(__arr, __arr + __size, 0);
	}
public:
	friend ostream& operator<<(ostream& out, const StaticArray& arr)
	{
		for (size_t i = 0; i < arr.__size; i++)
		{
			cout << arr.__arr[i] << " ";
		}
		cout << endl;
		return out;
	}
};