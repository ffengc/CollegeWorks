

## FileQuery实现思路

## 特点
	用哈希表存储单词信息 -- 可以支持快速多次查找
	重点优化了查找的效率
	用优先队列存储单词信息 -- 支持快速解决topK问题

### 系统框架
`vector<pair<string,int>>_sentences;`
	使用vector来存放所有句子（已滤除标点和缩进）
	其中pair<string,int>
	string存放的是句子
	int存放的是该句子所在的行号

`unordered_map<string, multiset<size_t>*>__hash_map`;
	用哈希表存放所有句子和所有句子行号的集合（由于一行中可能存在相同的单词，所以考虑使用multiset而不是set）此时multiset->size()就是单词出现的次数
	是用哈希表可以让查找复杂度降为O(1)
`priority_queue<pair<string, multiset<size_t>*>, deque<pair<string, multiset<size_t>*>>, cmp> __string_heap;`
	使用一个优先队列存放`pair<string, multiset<size_t>*`
	可以降低topK问题的时间复杂度

## 对外接口
### print_sentences()接口
	直接打印_sentences的信息即可
### print_sentences_ascend()接口
	构造一个临时对象sort_v，并提供一个仿函数sort_cmp，调用std::sort排序
	排序后打印信息
### print_word_count()
	遍历__hash_map直接打印即可
### print_top_world_context()
	构造一个临时对象tmp为__string_heap的拷贝 -- 复杂度为O(n) n为单词个数
	对tmp进行3次pop()操作 -- 复杂度为O(logn)
	对于每次top()得到的结构 分别构造ContextResults对象进行打印
### Find()
	哈希表查找 -- O(1)
	找到的结果构造ContextResults对象进行打印
### Replace()
	哈希表查找 -- O(1)
	找到后直接对哈希表erase和insert
	然后重新初始化__string_heap和__hash_map（分别调用__init_heap()和__update_vector()接口）

## 对内接口和属性
### struct cmp{};
	优先队列所需要的仿函数
### processing_sentences()
	切割每一行的字符串 -- 把句子切出来放到vector里面
### __print_sentences()
	打印句子信息
### __init_hash_table()
	初始化哈希表
	用句子构造istringstream对象 -- 切割出每个单词即可
### __init_heap()
	初始化优先队列
	该接口不止是构造函数时调用 -- 因此一开始要先要清空当前堆
### __replace_word()
	把句子中的单词新老替换
	通过构造istringstream对象切割出单词即可
### __update_vector()
	Replace接口时要调用的接口
	循环对vector<>里面的字符串分别进行__replace_word()操作即可

## ContextResults类
### 类属性
	vector<pair<string, int>> _sen; 使用vector来存放所有句子（已滤除标点和缩进）
	string _word;//目标单词
	set<size_t>_lines_number;//出现的行号
	size_t _times;//本单词在全文的出现次数

## 其它接口
### clearup_the_string()
	对字符串进行标点缩进的滤除
### print()
	打印上下文，通过调用get_context()获得上下文的单词
### print_every_sentence()
	打印一整个句子
### get_context()
	获得一个单词的上下文