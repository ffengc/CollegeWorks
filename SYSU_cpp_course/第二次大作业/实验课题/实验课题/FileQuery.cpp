
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include"FileQuery.h"



//其它接口
void clearup_the_string(string& s)
{
	size_t i = 0;
	while (s[i] == ' ')i++;
	string tmp;
	for (; i < s.size(); i++)
	{
		if (ispunct(s[i]))continue;
		tmp += tolower(s[i]);
	}
	s = tmp;//把tmp还给s
}
vector<string> get_context(const string& arr, const string& target)
{
	//目标：
	//从arr这个string中提取target的上下文
	vector<string>ret(3);//要返回的上下文
	istringstream line(arr);
	string word;
	vector<string>words;
	while (line >> word)
	{
		words.push_back(word);
	}
	auto it = find(words.begin(), words.end(), target);
	if (it == words.end())return ret;
	if (words.size() > 1)
	{
		if (it == words.begin())
		{
			ret[0] = "";
			ret[1] = *it;
			ret[2] = *(it + 1);
		}
		else if (it == words.end() - 1)
		{
			ret[0] = *(it - 1);
			ret[1] = *it;
			ret[2] = "";
		}
		else
		{
			ret[0] = *(it - 1);
			ret[1] = *it;
			ret[2] = *(it + 1);
		}
	}
	//如果该句子只有一个单词，且该单词就是target，只返回一个单词
	else if (word.size() == 1)
	{
		ret[0] = "";
		ret[1] = *it;
		ret[2] = "";
	}
	return ret;
}
ostream& print(ostream& out, const ContextResults& cr)
{
	cout << cr._word << endl;//打印该单词
	cout << "occurances:" << cr._times << endl;//打印出现次数
	for (auto e : cr._lines_number)
	{
		//在e这一行中有我们想要的句子
		//cr._sen;在cr._sen里面查找行号 = e的句子
		for (size_t i = 0; i < cr._sen.size(); i++)
		{
			if (cr._sen[i].second == e)
			{
				vector<string>ret = get_context(cr._sen[i].first, cr._word);
				if (ret[0].size() == 0 && ret[1].size() == 0 && ret[2].size() == 0)continue;
				cout << "  " << "(line:" << e << ")" << ret[0] << " " << ret[1] << " " << ret[2] << endl;
			}
		}
	}
	return out;
}
ostream& print_every_sentence(ostream& out, const ContextResults& cr)
{
	cout << cr._word << endl;
	cout << "occurance:" << cr._times << endl;
	for (auto& e : cr._lines_number)
	{
		//e : 行号
		for (size_t i = 0; i < cr._sen.size(); i++)
		{
			if (cr._sen[i].second == e)
			{
				//打印该句子
				cout << "  " << "(line:" << e << ")" << cr._sen[i].first << endl;
			}
		}
	}
	return out;
}



//内部接口
void FileQuery::processing_sentences(string& s, int num)
{
	//利用双指针分割所有的句子
	int slow = 0;
	int fast = 0;
	while (fast < s.size())
	{
		while (fast < s.size() && (s[fast] != ',' && s[fast] != '.'))
		{
			fast++;
		}
		//此时把[slow,fast)之间的字符push到vector里面 -- 同时初始化哈希表
		string tmp(s.begin() + slow, s.begin() + fast);
		clearup_the_string(tmp);
		this->_sentences.push_back({ tmp,num });
		this->sentences_.push_back(tmp);
		fast++;
		slow = fast;
	}
}
void FileQuery::__print_sentences(vector<pair<string, int>>& print_arr)
{
	for (auto& e : print_arr)
	{
		cout << "(line:" << e.second << ") " << e.first << endl;
	}
}
void FileQuery::__init_hash_table(string& s, size_t line_num)
{
	istringstream line(s);
	string word;
	while (line >> word)
	{
		clearup_the_string(word);//调用一次清理字符串
		auto& lines = this->__hash_map[word];
		if (!lines)
		{
			//开一个新的set
			lines = new multiset<size_t>;
		}
		lines->insert(line_num);
	}
}
void FileQuery::__init_heap()
{
	//先清空优先队列
	while (!this->__string_heap.empty())
	{
		__string_heap.pop();
	}
	assert(__string_heap.size() == 0);
	//遍历哈希表
	for (auto e : this->__hash_map)
	{
		//e : {string, multiset<size_t>*}
		//priority_queue<pair<string, multiset<size_t>*>, deque<pair<string, multiset<size_t>*>>, cmp()>
		//cout << typeid(e).name() << endl;
		this->__string_heap.push(e);
	}
}
void FileQuery::__replace_word(string& s, const string& oldStr, const string& newStr)
{
	vector<string>words;
	istringstream lines(s);
	string word;
	while (lines >> word)
	{
		words.push_back(word);
	}
	//替换
	for (auto& e : words)
	{
		if (e == oldStr)e = newStr;
	}
	s.clear();
	for (auto& e : words)
	{
		s += e;
		s += ' ';
	}
}
void FileQuery::__update_vector(const string& oldStr, const string& newStr)
{
	for (size_t i = 0; i < _sentences.size(); i++)
	{
		__replace_word(sentences_[i], oldStr, newStr);
		__replace_word(_sentences[i].first, oldStr, newStr);
	}
}
FileQuery::FileQuery(ifstream& input_file)
{
	string tmp_sentence;
	size_t curent_line_num = 1;//把行号记录一下
	while (getline(input_file, tmp_sentence))
	{
		//分割出所有句子
		processing_sentences(tmp_sentence, curent_line_num);//vector procesing
		//此时vector已经初始化好了 -- 现在要初始化哈希表
		__init_hash_table(tmp_sentence, curent_line_num);
		curent_line_num++;//行号++
	}
	__init_heap();
}
FileQuery::~FileQuery()
{
	//只有__hash_map的second域需要自己处理
	for (auto& e : __hash_map)
	{
		auto ptr = e.second;
		delete ptr;
	}
}
FileQuery::FileQuery(const FileQuery& fq)
{
	unordered_map<string, multiset<size_t>*>tmp_hash_table;
	priority_queue<pair<string, multiset<size_t>*>, deque<pair<string, multiset<size_t>*>>, cmp> tmp_heap;
	this->_sentences = fq._sentences;//调用std::vector的拷贝构造
	for (auto e : fq.__hash_map)
	{
		auto ptr_tmp = e.second;
		auto new_ptr = new multiset<size_t>(*(e.second));
		tmp_hash_table.insert({ e.first,new_ptr });//往哈希表插入新的指针
		tmp_heap.push({ e.first,new_ptr });//往优先队列插入新的pair
	}
	//赋值
	this->__hash_map = tmp_hash_table;
	this->__string_heap = tmp_heap;
}
void FileQuery::print_sentences()
{
	cout << "打印所有的句子" << endl;
	__print_sentences(this->_sentences);
}
void FileQuery::print_sentences_ascend()
{
	cout << "按升序打印所有的句子" << endl;
	vector<pair<string, int>>sort_v = this->_sentences;
	sort(sort_v.begin(), sort_v.end(), sort_cmp);
	this->__print_sentences(sort_v);
}
void FileQuery::print_word_count()
{
	//打印单词出现的次数
	//遍历哈希表即可
	cout << "打印每个单词出现的次数" << endl;
	for (auto e : this->__hash_map)
	{
		cout << e.first << ":" << e.second->size() << endl;
	}
}
void FileQuery::print_top_world_context(int n)
{
	//打印最高频的n个单词
	auto tmp = this->__string_heap;//拷贝一个堆 -- O(n)
	//priority_queue<pair<string, multiset<size_t>*>, deque<pair<string, multiset<size_t>*>>, cmp>
	//cout << typeid(tmp).name() << endl;
	//cout << endl;
	//先把前n个高频单词取出来
	vector<pair<string, multiset<size_t>*>>res_arr;
	for (size_t i = 0; i < n; i++)
	{
		res_arr.push_back(tmp.top());
		tmp.pop();
	}
	for (size_t i = 0; i < res_arr.size(); i++)
	{
		//把行号提取一下
		set<size_t>num_arr;
		multiset<size_t>::iterator it = res_arr[i].second->begin();
		while (it != res_arr[i].second->end())
		{
			num_arr.insert(*it);
			it++;
		}
		ContextResults cr(_sentences, res_arr[i].first, num_arr, res_arr[i].second->size());
		print(cout, cr) << endl;
	}
}
void FileQuery::Find(const string& str)
{
	//在哈希表中查找 -- 复杂度为O(1)
	auto it = __hash_map.find(str);
	if (it == __hash_map.end())
	{
		//找不到该单词
		cerr << "找不到该单词" << endl;
		return;
	}
	//找到了 *it  -- pair<string,multiset<size_t>*>
	set<size_t>lines_number(it->second->begin(), it->second->end());//把行号去重一下
	ContextResults cr(this->_sentences, it->first, lines_number, it->second->size());
	print_every_sentence(cout, cr);
}
void FileQuery::Replace(const string& oldstr, const string& newstr)
{
	bool flag = false;//是否发生替换
	//在哈希表中查找 -- 复杂度为O(1)
	auto it = __hash_map.find(oldstr);
	if (it == __hash_map.end())
	{
		cout << "找不到该单词，无法替换！" << endl;
		return;
	}
	auto ptr = __hash_map[oldstr];
	__hash_map.erase(oldstr);
	__hash_map.insert({ newstr,ptr });//把新的单词重新插入哈希表
	//难点：现在还要维护优先队列和存句子的vector
	__init_heap();//有限队列重新调用一下初始化就行了，记得在__init_heap里面先clear()一下
	__update_vector(oldstr, newstr);
	cout << "替换成功!" << endl;
}