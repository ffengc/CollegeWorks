#pragma once


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<memory.h>


//表示一个链表的节点
enum Administration
{
	Take_orally, //内服
	external	//外用
};
struct ListNode //结构体内部的成员都应该使用一个__作为开头，这是良好的习惯
{
	//如果是认真想写好，其实所有的字符数组都应该malloc出来 -- 而不是开空间到栈上
	char __drug_name[20];
	size_t __id;
	Administration adm_type;//服用方式 -- 这里用一个枚举
	char __effect[20];
	char __side_effect[20];
	struct ListNode* __next;
};

typedef struct ListNode Med_Node;

Med_Node* CreatList(Med_Node* head)
{
	//初始化链表
}
void DestroyList(Med_Node* head)
{
	//销毁链表
}
void modify_info(Med_Node* head)
{
	//修改药物信息
	//可以循环修改
	//思路：
	//先输入药品名称 -- 在链表中查找(查找可以复用下面find系列的函数)是否存在，如果不存在，打印“不存在...”，如果存在，修改

	//打印：修改成功！
}
void input_info(Med_Node* head)
{
	//输入药物信息
	//可以循环输入


	//输入成功！
}

//输出
Med_Node* find_by_name(Med_Node* head)
{
	//通过药品名字输出
}
Med_Node* find_by_id(Med_Node* head)
{
	//通过药品编号查找
}
Med_Node* find_by_classes(Med_Node* head)
{
	//通过药品分类进行查找
}
Med_Node* find_by_effect(Med_Node* head)
{
	//通过主/副作用查找
}
void print_info(Med_Node* node)
{

}
void print(Med_Node* head)
{

}