

### FileQuery实现思路

用vector存所有句子

用哈希表存<单词,set单词所有的行号>
所以此时set->size()就是单词出现的次数 -- 此时的问题：
	如果一个单词一行出现多次 -- 会被去重
	1.考虑使用multiset
	而课堂上的TestQuery好像没有这个问题 -- 因此可以使用set
	但是multiset在打印行号的时候不方便 -- 又要去重
	2.考虑用一个pair<set,size_t>
	set用来存放行号集合，size_t用来存放出现次数

用一个优先队列解决TopK问题

打印上下文用一个ContextualResults类处理
	封装处理可以为了让提取上下文的过程更加清晰
	在ContextualResults类中调用get_context和print接口来进行结果的打印
	get_context()接口用来提取每一句中目标单词的上下文
	print()接口用来打印结果

查询单词
	在哈希表中O(1)查询，查询到该单词的行号集合
	用行号集合的multiset构造一个set
	调用ContextualResults类
	调用print_every_sentence接口

Replace