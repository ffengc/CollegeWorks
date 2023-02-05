#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <assert.h>
using namespace std;


void clearup_the_string(string& s);
class ContextResults
{
private:
	vector<pair<string, int>> _sen;//用指针 -- 避免拷贝
	string _word;//目标单词
	set<size_t>_lines_number;//出现的行号
	size_t _times;//本单词在全文的出现次数
public:
	friend ostream& print(ostream& out, const ContextResults& cr);
	friend ostream& print_every_sentence(ostream& out, const ContextResults& cr);
public:
	ContextResults(vector<pair<string, int>> arr, string word, set<size_t>lines_number, size_t times)
		:_sen(arr), _word(word), _lines_number(lines_number), _times(times)
	{}
	ContextResults(const ContextResults& cr) = default;
	~ContextResults() = default;
};
vector<string> get_context(const string& arr, const string& target);
ostream& print(ostream& out, const ContextResults& cr);
ostream& print_every_sentence(ostream& out, const ContextResults& cr);

class FileQuery
{
private:
	void processing_sentences(string& s, int num);
	//为了其它函数打印时可以复用该函数 -- 封装多一层	__print_sentences()
	void __print_sentences(vector<pair<string, int>>& print_arr);
	void __init_hash_table(string& s, size_t line_num);
	void __init_heap();
	void __replace_word(string& s, const string& oldStr, const string& newStr);
	void __update_vector(const string& oldStr, const string& newStr);
	inline static bool sort_cmp(const pair<string, int>& e1, const pair<string, int>& e2)
	{
		return e1.first < e2.first;
	}
public:
	FileQuery(ifstream& input_file);
	~FileQuery();
	FileQuery(const FileQuery& fq); //允许深拷贝操作
	//打印所有的句子
	void print_sentences();
	//按升序打印所有的句子
	void print_sentences_ascend();
	//打印每个单词出现的次数
	void print_word_count();
	//打印词频最高的n个单词，对每个单词打印所有该单词出现的上下文
	void print_top_world_context(int n);
	//查找包含该单词的句子，打印出来
	void Find(const string& str);
	//将所有单词old替换成new，测试结果不少于3个例子
	void Replace(const string& oldstr, const string& newstr);
private:
	//优先队列需要的仿函数
	struct cmp
	{
		inline bool operator()(const pair<string, multiset<size_t>*>& e1, 
			const pair<string, multiset<size_t>*>& e2) const
		{
			return e1.second->size() < e2.second->size();
		}
	};
private:
	vector<string>sentences_;//存放所有句子
	vector<pair<string,int>>_sentences;//存放句子和相对应的行号 -- 因题目要求 -- 上面添加多了一个vector<string>sentences_
	//因为一个单词可能一行出现多次 -- 考虑使用multiset
	unordered_map<string, multiset<size_t>*>__hash_map;//use hash_table to save lines number
	//用哈希表可以让查找 -- O(1)
	priority_queue<pair<string, multiset<size_t>*>, 
		deque<pair<string, multiset<size_t>*>>, cmp> __string_heap;
	//用堆 -- 可以让topK更快
};

/**
 * 实现一个类FileQuery，拥有私有成员std::vector<std::string> sentences_，实现如下功能.
 * 读取一个指定文本文件poem.txt（将附录的文本拷贝至poem.txt）
 */