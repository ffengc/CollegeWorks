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


class Animal {
protected:
	size_t _age;
public:
	Animal(size_t age = 0)
		:_age(age) {}
	~Animal() {}
	Animal(const Animal& a)
		:_age(a._age) {}
};
class dog :public Animal {
public:
	dog(int age = 0) :Animal(age) {}
	~dog() {}
public:
	void SetAge(int age) {
		_age = age;
	}
};


void test_animal() {
	Animal a(10);
	dog d(20);
	d.SetAge(15);
}
