#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus


#elif
#endif

#include"Matrix.h"
#include"NameList.h"


#if 1
int main() {
	// 1 2 3
	// 4 5 6

	// 1 3 5
	// 2 4 6 
	vector<vector<double>>arr1 = { {1,2,3},{4,5,6} };
	vector<vector<double>>arr2 = { {1,3,5},{2,4,6} };
	Matrix m1(arr1);
	Matrix m2(arr2);
	cout << m1.nElements() << endl;//6
	cout << m1.size() << endl;//48
	m1.set(0, 0, 100);//把(0,0)位置的数值改成100
	cout << m1.get(0, 0) << endl;//100
	m2.print_Col(0);//1 2
	m2.print_Row(0);//1 3 5
	cout << endl;
	m2.print_Matrix();// 1 3 5
					  // 2 4 6 
	cout << endl;
	m1.add(m2);
	m1.print_Matrix();
	cout << endl;
	
	Matrix m3(6, 2, 3);
	m3 = m1 + m2;
	m3.print_Matrix();

	cout << endl;
	return 0;
}
#endif

int main() {
	NameList nl;
	int sz = 0;
	cin >> sz;
	for (int i = 0; i < sz; i++) {
		string tmp;
		cin >> tmp;
		nl.addName(tmp);
	}


	cout << endl;
	nl.deleteName("zhangsan");
	nl.print();

	/*
	5
	aa
	aaa
	ababa
	babab
	abbbb
	*/
	cout << endl << "test_search" << endl;
	vector<string>ret = nl.search("ab");
	vector<string>::iterator it = ret.begin();
	while (it != ret.end()) {
		cout << *it << endl;
		it++;
	}
	
	cout << endl;
	cout << "按照输入顺序打印" << endl;
	nl.print(0);
	cout << "按照升序打印" << endl;
	nl.print(1);
	cout << "按照降序打印" << endl;
	nl.print(2);
	return 0;
}