


/*****************************************************************//**
 * \file   SparseMatrix.h
 * \brief  
 * 
 * \author yfc 21312780
 * \date   October 2022
 *********************************************************************/



#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cassert>
using namespace std;


/*********************************************** NonzeroElement类 ***********************************************/
class NonzeroElement {
public:
	int _row;
	int _col;
	double _val;
public:
	NonzeroElement()
		:_row(0), _col(0), _val(0) {}
};

bool cmp1(const NonzeroElement& e1, const NonzeroElement& e2) {
	return e1._row < e2._row;
}
bool cmp2(const NonzeroElement& e1, const NonzeroElement& e2) {
	return e1._col < e2._col;
}


/*********************************************** SparseMatrix类 ***********************************************/

class SparseMatrix {
private:
	int _Row;
	int _Col;
	int _data_size;
	NonzeroElement* _data;
public:
	//用一个NonzeroElement构造
	SparseMatrix(NonzeroElement* constructor, int sz);
	//用一个vector构造
	SparseMatrix(vector<vector<double>>constructor);
	~SparseMatrix();
	SparseMatrix(const SparseMatrix& sm);
	SparseMatrix& operator=(const SparseMatrix& sm);
	SparseMatrix& add(const SparseMatrix& sm);
	SparseMatrix& subtract(const SparseMatrix& sm);
	void output_Matrix_by_vector();
public:
	//重载+/- <<运算符
	SparseMatrix operator+(const SparseMatrix& sm);
	SparseMatrix operator-(const SparseMatrix& sm);
	//重载<<
public:
	friend ostream& operator<<(ostream& out, const SparseMatrix& sm);
	//get/set
public:
	//参数是行列的序号
	double get(int x, int y);
	void set(int x_, int y_, int val);
};


/*********************************************** SparseMatrix类相关接口定义 ***********************************************/

//流插入重载
ostream& operator<<(ostream& out, const SparseMatrix& sm) {
	vector<vector<double>>tmp(sm._Row, vector<double>(sm._Col, 0));
	for (int i = 0; i < sm._data_size; i++) {
		int x = sm._data[i]._row;
		int y = sm._data[i]._col;
		tmp[x][y] += sm._data[i]._val;
	}
	//打印这个vector
	for (int i = 0; i < tmp.size(); i++) {
		for (int j = 0; j < tmp[0].size(); j++) {
			std::cout << tmp[i][j] << " ";
		}
		std::cout << endl;
	}
	return out;
}

//类成员函数
SparseMatrix::SparseMatrix(NonzeroElement* constructor, int sz)
	:_data(constructor), _data_size(sz)
{
	//找到constructor里面最大的数
	this->_Row = (*max_element(constructor, constructor + sz, cmp1))._row;
	this->_Col = (*max_element(constructor, constructor + sz, cmp2))._col;
}
//用一个vector构造
SparseMatrix::SparseMatrix(vector<vector<double>>constructor) {
	this->_Row = constructor.size();
	this->_Col = constructor[0].size();
	//统计vector<<>>里面非0元素个数
	int cnt_zero = 0;
	for (int i = 0; i < constructor.size(); i++) {
		cnt_zero += count(constructor[i].begin(), constructor[i].end(), 0);
	}
	int cnt_non_zero = constructor.size() * constructor[0].size() - cnt_zero;
	this->_data = new NonzeroElement[cnt_non_zero];
	int pointer_arr = 0;
	for (int i = 0; i < constructor.size(); i++) {
		for (int j = 0; j < constructor[0].size(); j++) {
			if (constructor[i][j] != 0) {
				_data[pointer_arr]._row = i;
				_data[pointer_arr]._col = j;
				_data[pointer_arr]._val = constructor[i][j];
				pointer_arr++;
			}
		}
	}
	_data_size = pointer_arr;//下标给数组大小
}
SparseMatrix::~SparseMatrix() {
	this->_Row = 0;
	this->_Col = 0;
	delete[] this->_data;
}
SparseMatrix::SparseMatrix(const SparseMatrix& sm)
	:_Row(sm._Row), _Col(sm._Col)
{
	//注意，因为一开始的_data_size是0，也就是说this这边是没有开到空间放NonzeroElement的
	//直接memcpy过来肯定是越界的
	//if (this->_data_size != 0) {
	//	delete[] this->_data;
	//}
	this->_data_size = sm._data_size;
	_data = new NonzeroElement[_data_size];
	memcpy(this->_data, sm._data, sizeof(NonzeroElement) * _data_size);
}
SparseMatrix& SparseMatrix::operator=(const SparseMatrix& sm) {
	if (this == &sm)return*this;
	this->_Row = sm._Row;
	this->_Col = sm._Col;
	if (this->_data_size != 0) {
		delete[] this->_data;
	}
	this->_data_size = sm._data_size;
	_data = new NonzeroElement[_data_size];
	memcpy(this->_data, sm._data, sizeof(NonzeroElement) * _data_size);
	return *this;
}
SparseMatrix& SparseMatrix::add(const SparseMatrix& sm) {
	//直接加没办法加，要先创建一个vector
	//在vector上操作 -- 最后用vector构造SparseMatrix
	assert(this->_Row == sm._Row && this->_Col == sm._Col);//判断操作合法性
	vector<vector<double>>tmp(this->_Row, vector<double>(this->_Col, 0));
	//处理this
	for (int i = 0; i < this->_data_size; i++) {
		int x = this->_data[i]._row;
		int y = this->_data[i]._col;
		tmp[x][y] += this->_data[i]._val;
	}
	//处理sm
	for (int i = 0; i < sm._data_size; i++) {
		int x = sm._data[i]._row;
		int y = sm._data[i]._col;
		tmp[x][y] += sm._data[i]._val;
	}
	//用这个vector构造一个SparseMatrix对象 -- 复用
	SparseMatrix ans(tmp);
	*this = tmp;//按照题目的要求 -- 赋值给自己
	return *this;
}
SparseMatrix& SparseMatrix::subtract(const SparseMatrix& sm) {
	assert(this->_Row == sm._Row && this->_Col == sm._Col);//判断操作合法性
	vector<vector<double>>tmp(this->_Row, vector<double>(this->_Col, 0));
	//处理this
	for (int i = 0; i < this->_data_size; i++) {
		int x = this->_data[i]._row;
		int y = this->_data[i]._col;
		tmp[x][y] += this->_data[i]._val;
	}
	//处理sm
	for (int i = 0; i < sm._data_size; i++) {
		int x = sm._data[i]._row;
		int y = sm._data[i]._col;
		tmp[x][y] -= sm._data[i]._val;//这里改成-
	}
	//用这个vector构造一个SparseMatrix对象 -- 复用
	SparseMatrix ans(tmp);
	*this = tmp;//按照题目的要求 -- 赋值给自己
	return *this;
}
void SparseMatrix::output_Matrix_by_vector() {
	//打印this
	vector<vector<double>>tmp(this->_Row, vector<double>(this->_Col, 0));
	for (int i = 0; i < this->_data_size; i++) {
		int x = this->_data[i]._row;
		int y = this->_data[i]._col;
		tmp[x][y] += this->_data[i]._val;
	}
	//打印这个vector
	for (int i = 0; i < tmp.size(); i++) {
		for (int j = 0; j < tmp[0].size(); j++) {
			cout << tmp[i][j] << " ";
		}
		cout << endl;
	}
}
//重载+/- <<运算符
SparseMatrix SparseMatrix::operator+(const SparseMatrix& sm) {
	assert(this->_Row == sm._Row && this->_Col == sm._Col);
	SparseMatrix ans(*this);
	ans.add(sm);
	return ans;
}
SparseMatrix SparseMatrix::operator-(const SparseMatrix& sm) {
	assert(this->_Row == sm._Row && this->_Col == sm._Col);
	SparseMatrix ans(*this);
	ans.subtract(sm);
	return ans;
}
//get/set
//参数是行列的序号
double SparseMatrix::get(int x, int y) {
	assert(x >= 1 && x <= _Row && y >= 1 && y <= _Col);
	x--; y--;//把序号转化成下标
	//在_data中查找
	for (int i = 0; i < _data_size; i++) {
		if (_data[i]._row == x && _data[i]._col == y) {
			return _data[i]._val;
		}
	}
	return 0;//找不到则返回0
}
void SparseMatrix::set(int x_, int y_, int val) {
	assert(x_ >= 1 && x_ <= _Row && y_ >= 1 && y_ <= _Col);
	x_--; y_--;//把序号转化成下标
	vector<vector<double>>tmp(this->_Row, vector<double>(this->_Col, 0));
	//处理this
	for (int i = 0; i < this->_data_size; i++) {
		int x = this->_data[i]._row;
		int y = this->_data[i]._col;
		tmp[x][y] += this->_data[i]._val;
	}
	tmp[x_][y_] = val;
	SparseMatrix ans(tmp);
	//重新构造一个*this
	*this = ans;//把重新构造的结果赋值给*this
}



int main() {
#if 0  //和下面的#if有重定义 -- 不要同时放出来
	cout << "======== 测试拷贝构造 ========" << endl;
	vector<vector<double>>arr = { {1, 2, 3}, { 2,0,4 } ,{1,0,1} };
	SparseMatrix sm(arr);
	SparseMatrix sm2 = sm;
	sm.output_Matrix_by_vector();
	cout << endl;
	sm2.output_Matrix_by_vector();
#endif
#if 1

	vector<vector<double>>arr = { {1, 2, 3}, { 2,0,4 } ,{1,0,1} };
	SparseMatrix sm(arr);
	sm.output_Matrix_by_vector();

	std::cout << endl;
	vector<vector<double>>arr2 = { {1,0,0},{1,0,0},{1,0,0} };
	SparseMatrix sm2(arr2);
	sm2.output_Matrix_by_vector();

	std::cout << "===============测试加法===============" << endl;
	vector<vector<double>>test_add_a = { {0,0,3,0,4},{0,0,5,7,0},{0,0,0,0,0},{0,2,6,0,0} };
	vector<vector<double>>test_add_b = { {3,0,0,0,0},{0,4,0,0,0},{0,0,1,0,0},{0,0,2,0,0} };
	SparseMatrix a(test_add_a);
	SparseMatrix b(test_add_b);
	std::cout << "a矩阵:" << endl;
	std::cout << a << std::endl;
	std::cout << "b矩阵" << endl;
	std::cout << b << endl;
	a.add(b);
	std::cout << "a+b:" << endl;
	std::cout << a << std::endl;
	std::cout << "===============测试减法===============" << endl;
	vector<vector<double>>test_sub_a = { {0,0,3,0,4},{0,0,5,7,0},{0,0,0,0,0},{0,2,6,0,0} };
	vector<vector<double>>test_sub_b = { {3,0,0,0,0},{0,4,0,0,0},{0,0,1,0,0},{0,0,2,0,0} };
	SparseMatrix aa(test_sub_a);
	SparseMatrix bb(test_sub_b);
	std::cout << "a矩阵:" << endl;
	std::cout << aa << std::endl;
	std::cout << "b矩阵" << endl;
	std::cout << bb << endl;
	aa.subtract(bb);
	std::cout << "a-b:" << endl;
	std::cout << aa << std::endl;


	std::cout << "============== 测试重载 ==============" << endl;
	sm.output_Matrix_by_vector();
	std::cout << endl;
	sm2.output_Matrix_by_vector();
	std::cout << endl;
	

#if 1 
	vector<vector<double>>arr3 = { {0,0,0},{0,0,0},{0,0,0} };
	SparseMatrix sm3(arr3);
	//sm3 = sm + sm2; 选择运行
	sm3 = sm - sm2;
	sm3.output_Matrix_by_vector();
#endif
	std::cout << "=============== 测试流插入重载 ==================" << endl;
	vector<vector<double>>arr5 = { {1, 2, 3}, { 2,0,4 } ,{1,0,1} };
	SparseMatrix sm5(arr);
	std::cout << sm5 << endl;
	std::cout << "=============== 测试get/set ====================" << endl;
	vector<vector<double>>arr6 = { {1, 2, 3}, { 2,0,4 } ,{1,0,1} };
	SparseMatrix sm6(arr6);
	std::cout << sm6 << endl;
	std::cout << sm6.get(1, 2) << endl;
	sm6.set(1, 2, 0);
	sm6.set(1, 3, 100);
	std::cout << sm6 << endl;
#endif
	return 0;
}