

'''
4. 基于『人工智能编程语言学生名单.txt』，开发学生信息系统，定义student类，并仅引用os模块
需求一，信息查找和定位：输入学号，可以查找打印其姓名、性别、班级、学院等相关信息；
需求二，打印考场安排表：需要将学生顺序打乱排列，打印输出『考场安排表.txt』，包含考场顺序号（1-10）、姓名、学号；
需求三，打印准考证号：根据考场安排信息，对每个同学分别打印其准考证号放置于『准考证号』文件夹，
        用考场顺序号命名其准考证文件
        『01.txt』、『02.txt』 ... 『10.txt』，其中包含信息：考场顺序号、姓名、学号。
'''

import numpy as np
import os
import pandas as pd
import random

class Student:
    def __init__(self,file_path) -> None:
        print("学生信息系统")
        self.fp=open(file_path,'r',encoding='utf-8')
        self.stu_info={}
        self.stu_info_list=self.fp.readlines()
        for i in range(0,len(self.stu_info_list)):
            self.stu_info_list[i]=self.stu_info_list[i].rstrip()
        # 现在要将这些数据存到字典列表里面去
        self.info_list=[]
        for i in range(0,len(self.stu_info_list)):
            tmp=self.stu_info_list[i].split(' ')
            tmp_dict={}
            tmp_dict['学号']=tmp[1]
            tmp_dict['姓名']=tmp[2]
            tmp_dict['性别']=tmp[3]
            self.info_list.append(tmp_dict)
    def menu(self):
        print("============ 学生信息系统 ============")
        print("*            1.查找学生              *")
        print("*            2.打印考场安排表        *")
        print("*            3.打印准考证号          *")
        print("*            0.退出                  *")
        print("======================================")
    def start_sys(self):
        self.menu()
        choose = int(input("请输入需要的操作:>"))
        if choose==1:
            num_str=input("请输入学生的学号:(按:!wq退出)")
            while num_str!='!wq':
                ret = self.search(num_str)
                if ret==False:
                    print("请重新输入！")
                    num_str=input("请输入学生的学号:(按:!wq退出)")
                else:
                    break
            return
        elif choose==2:
            self.print_examination_room_arrangement()
            return
        elif choose==3:
            self.print_the_examination_permit_number()
            return
        elif choose==0:
            return
        else:
            print("err!请重新输入!")
    def Print_info(self,_dict):
        s=pd.Series(_dict)
        print(s)
    def search(self,num_str):
        for i in range(0,len(self.info_list)):
            if self.info_list[i]['学号']==num_str:
                self.Print_info(self.info_list[i])
                return True
        print("找不到该学生信息！")
        return False
    def print_examination_room_arrangement(self):
        self.info_list
        random.shuffle(self.info_list)
        df=pd.DataFrame(self.info_list).drop('性别',axis=1,inplace=False)
        df.index=df.index+1
        print("顺序打乱后输出的考场安排表结果为：")
        print(df)
        # fp=open('test.txt','w',encoding='utf-8')
        df.to_csv('test.txt')
    def print_the_examination_permit_number(self):
        random.shuffle(self.info_list)
        for i in range(0,len(self.info_list)):
            line = str(self.info_list[i])
            line = f'序号:{i+1}  信息:' + line
            num=str(i+1).zfill(2)
            path=f"Admission_certificate_Number/{num}.txt"
            fp=open(path,'w',encoding='utf-8')
            fp.writelines(line)
        