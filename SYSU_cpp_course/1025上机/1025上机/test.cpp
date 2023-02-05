#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

#elif
#endif

//SYSU_CPP_1025_EXP

//1.Matrix和NameList


//2.std::vector的使用
#if 0
vector<int> get_the_sum_of_adjacent_elements(vector<int>& nums) {
	vector<int>ret;
	for (int i = 0; i < nums.size(); i += 2) {
		ret.push_back(nums[i] + nums[i + 1]);
	}
	return ret;
}
void print_vector(vector<int>& v) {
	vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
}
void test_vector() {
	vector<int>nums;
	int x = 0;
	while (cin >> x) {
		nums.push_back(x);
		if (cin.get() == '\n')break;
	}
	//size()为偶数
	if (nums.size() % 2 == 0) {
		vector<int>ret;
		ret = get_the_sum_of_adjacent_elements(nums);
		print_vector(ret);
	}
	else {
		cout << "输入元素个数为奇数,err" << endl;
		print_vector(nums);
	}
}
int main() {
	test_vector();
	return 0;
}
#endif



//3.字符串过滤程序
#include<set>
#include<unordered_map>
class Solution {
public:
	void stringFilter(const string& inputStr, string& outStr) {
		outStr.clear();
		//用红黑树去重
		set<char>s;
		s.insert(inputStr.begin(), inputStr.end());
		set<char>::iterator it = s.begin();
		while (it != s.end()) {
			outStr += *it;
			it++;
		}
	}
	void stringZip(const string& inputStr, string& outStr) {
		outStr.clear();
		//双指针控制即可
		int fast = 0;
		int slow = 0;
		while (fast < inputStr.size()) {
			while (inputStr[fast] == inputStr[slow])fast++;
			if (fast - slow > 1) {
				outStr += (fast - slow) + '0';
			}
			outStr += inputStr[slow];
			slow = fast;
		}
	}
};
int main() {
	string s = "deedf";
	string s2 = "afafafaf";
	string s3 = "pppppppp";
	string ret;
	Solution().stringFilter(s, ret);
	cout << ret << endl;
	Solution().stringFilter(s2, ret);
	cout << ret << endl;
	Solution().stringFilter(s3, ret);
	cout << ret << endl;

	string ss = "cccddecc";
	string ss2 = "adef";
	string ss3 = "pppppppp";
	Solution().stringZip(ss, ret);
	cout << ret << endl;
	Solution().stringZip(ss2, ret);
	cout << ret << endl;
	Solution().stringZip(ss3, ret);
	cout << ret << endl;

	return 0;
} 