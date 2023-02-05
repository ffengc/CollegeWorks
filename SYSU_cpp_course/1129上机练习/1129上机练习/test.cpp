
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<functional>
#include<iostream>
#include<initializer_list>
#include<string.h>
#include<numeric>
using namespace std;

#elif
#endif

/*
1.
编写函数模板，template<class T>my_swap(T &a, T&b)，
对a和b进行交换。产生类型分别为int, double的函数，
在main函数中进行验证。
*/
#if 0
template<class T>
void my_swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}
int main()
{
	int a = 10; int b = 20;
	double x = 5.5; double y = 6.6;
	cout << a << " " << b << endl;
	cout << x << " " << y << endl;
	my_swap(a, b); my_swap(x, y);
	cout << a << " " << b << endl;
	cout << x << " " << y << endl;
	return 0;
}
#endif


//顺序表
#if 0
template<class T>
class MyArray
{
protected:
	size_t __size;
	T* __arr;
public:
	MyArray(T* arr = nullptr, size_t size = 0)
	{
		if (size > __size)
		{
			reserve(size);
		}
		for (size_t i = 0; i < size; i++)
		{
			__arr[i] = arr[i];
		}
		__size = size;
	}
	MyArray(const initializer_list<T>& arr)
	{
		typename initializer_list<T>::iterator it = arr.begin();
		int arr_size = arr.size();
		this->__arr = new T[arr_size];
		T* cur = this->__arr;
		this->__size = arr_size;
		while (it != arr.end())
		{
			*cur++ = *it++;
		}
	}
	MyArray(const MyArray& myarr)
	{
		if (myarr.__size > __size)
		{
			//扩容
			reserve(myarr.__size);
		}
		for (size_t i = 0; i < myarr.__size; i++)
		{
			__arr[i] = myarr[i];
		}
		this->__size = myarr.__size;
	}
	~MyArray()
	{
		__size = 0;
		delete[] __arr;
		__arr = nullptr;
	}
	MyArray<T>& operator=(const MyArray& myarr)
	{
		if (&myarr == this)return *this;
		if (myarr.__size > __size)
		{
			//扩容
			reserve(myarr.__size);
		}
		memcpy(this->__arr, myarr.__arr, __size * sizeof(T));
		this->__size = myarr.__size;
		return *this;
	}
	void print_list() const
	{
		for (size_t i = 0; i < __size; i++)
		{
			cout << __arr[i] << " ";
		}
		cout << endl;
	}
	void reserve(int newSize)
	{
		T* newPtr = new T[newSize];
		for (size_t i = 0; i < __size; i++)
		{
			newPtr[i] = __arr[i];
		}
		this->__size = newSize;
		this->__arr = newPtr;
	}
	void sort()
	{
		sort(__arr, __arr + __size);
	}
	void reverse()
	{
		std::reverse(__arr, __arr + __size);
	}
	size_t find(const T& val)
	{
		//返回下标
		T* ptr = std::find(__arr, __arr + __size, val);
		return ptr - __arr;
	}
	T sum()
	{
		T ret = accumulate(__arr, __arr + __size, 0);
		return ret;
	}
};


int main()
{
	int arr[] = { 1,2,3,4,5 };
	MyArray<int>myArray(arr, sizeof(arr) / sizeof(arr[0]));
	myArray.print_list();
	cout << myArray.sum() << endl;
	cout << myArray.find(2) << endl;
	myArray.reverse();
	myArray.print_list();
	return 0;
}
#endif

template<class T>
class MyIncrement
{
protected:
	T __value;
public:
	MyIncrement(const T& tag = 0)
		:__value(tag) {}
	MyIncrement(const MyIncrement& my) = default;
	~MyIncrement() = default;
public:
	MyIncrement<T> operator++(int)
	{
		MyIncrement tmp = *this;//拷贝构造
		++this->__value;
		return tmp;
	}
	MyIncrement<T>& operator++()
	{
		++this->__value;
		return *this;
	}
	T toIncrement()
	{
		++(*this);
		return this->__value;
	}
};
int main()
{
	MyIncrement<int> myint(7);
	MyIncrement<double> mydouble(11.1);
	cout << "Incremented int value: " << myint.toIncrement() << endl;
	cout << "Incremented double value: " << mydouble.toIncrement() << endl;
	return 0;
}