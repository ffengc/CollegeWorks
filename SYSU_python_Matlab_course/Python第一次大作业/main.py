

# python第一次大作业
"""
题目：输入学生成绩信息序列，获得成绩从高到低、
    从低到高、按某一门成绩的排列,相同成绩都按先录入排列在前的规则处理。
数据如下：(数据规则：学生姓名 高数成绩 英语成绩 大物成绩)
    SanZhang 70 80 61
    SiLi 86 77 81
    WuWang 88 90 77
    MingLi 60 77 81
    MiWang 71 70 60
    HaiLi 88 78 89
    HeWang 70 90 80
    LiWang 67 71 70
输出：利用字典容器，完成对于每个学生成绩数据的储存，并将所有学生储存于列表中；在此基础上，
    按照总分从高到低的学生名单，总分从低到高的学生名单，三门课成绩从高到低的学生名单。
    给出具体的排序结果、涉及的代码，以及简要介绍自己设计的排序算法原理
"""

import sys
import pandas as pd

if False:
    class Student_score_info():
        def __init__(self, name, Advanced_Mathematics, English, College_Physics) -> None:
            self.name = name
            self.Advanced_Mathematics = Advanced_Mathematics
            self.College_Physics = College_Physics
            self.English = English
            self.total_score = Advanced_Mathematics+College_Physics+English

        def print_student_info(self):
            pass
else:
    pass

if False:
    # 快排是不稳定排序 -- 不能直接用 -- 否则会打乱原有的顺序
    class My_QuickSort_By_Student_score:
        def __init__(self, dict_list, sort_method, sort_method_type, Seq):
            self.key = sort_method[sort_method_type]  # key是str类型，决定按照什么排序
            self.Seq = Seq  # 决定升序还是降序
            self.dict_list = dict_list  # 待排序的字典序列

        def _PartSort(self, begin, end):
            key = self.dict_list[begin][self.key]
            piti = begin  # 第一个坑
            left = begin
            right = end
            while left < right:
                # 右边找小，填到左边的坑
                while left < right and self.dict_list[right][self.key] >= key:
                    right -= 1
                self.dict_list[piti][self.key] = self.dict_list[right][self.key]
                piti = right  # 自己变成坑
                while left < right and self.dict_list[left][self.key] <= key:
                    left += 1
                self.dict_list[piti][self.key] = self.dict_list[left][self.key]
                piti = left
            # 一定会在坑的位置相遇
            self.dict_list[piti][self.key] = key
            return piti

        def _QuickSort(self,begin, end):
            if begin >= end:
                return
            keyi = self._PartSort(begin, end)
            # 递归实现快速排序
            self._QuickSort(begin, keyi-1)
            self._QuickSort(keyi+1, end)

        def sortArray(self):
            # python3实现快速排序
            begin = 0
            end = len(self.dict_list)-1
            self.QuickSort(begin,end)
            if self.Seq == 0:  # 降序 -- 把序列反转一下
                self.dict_list=self.dict_list[-1::-1]
            return self.dict_list
    class My_HeapSort_By_Student_score:
        def __init__(self, dict_list, sort_method, sort_method_type, Seq):
            self.key = sort_method[sort_method_type]  # key是str类型，决定按照什么排序
            self.Seq = Seq  # 决定升序还是降序
            self.dict_list = dict_list  # 待排序的字典序列
        def heapify(self,nums,start,end):
            # 递归法
            dad=start
            son=dad*2+1
            if son>end: return
            if (son+1<=end) and (nums[son][self.key]<nums[son+1][self.key]):
                son+=1
            if nums[dad][self.key]>nums[son][self.key]:
                return # 不需要下沉了
            nums[dad],nums[son]=nums[son],nums[dad]
            self.heapify(nums,son,end)
            return
        def sortArray(self):
            nums=self.dict_list
            sz=len(nums)
            i=0
            for i in range(int((sz-1)/2),-1,-1):
                self.heapify(nums,i,len(nums)-1) # heapify 元素下沉函数
            # 2.把第一个元素和堆最后一个元素进行交换，然后重新调整，直到排序完毕
            for i in range(sz-1,0,-1): # 注意，这里i循环到i即可:
                nums[0],nums[i]=nums[i],nums[0]
                self.heapify(nums,0,i-1)
            if self.Seq==1:
                nums=nums.reverse()
            return nums
else:
    pass
class My_MergeSort_By_Student_score:
    def __init__(self, dict_list, sort_method, sort_method_type, Seq):
        self.key = sort_method[sort_method_type]  # key是str类型，决定按照什么排序
        self.Seq = Seq  # 决定升序还是降序
        self.dict_list = dict_list  # 待排序的字典序列
    def mergeSort(self,arr,arrtmp,start,end):
        if start>=end: return
        mid=start+int((end-start)/2)
        istart1=start
        iend1=mid

        istart2=mid+1
        iend2=end
        self.mergeSort(arr,arrtmp,istart1,iend1)
        self.mergeSort(arr,arrtmp,istart2,iend2)
        # 开始归并
        i = start
        while istart1 <= iend1 and istart2 <= iend2:
            if arr[istart1][self.key]<arr[istart2][self.key]:
                arrtmp[i]=arr[istart1]
                istart1+=1
            else:
                arrtmp[i]=arr[istart2]
                istart2+=1
            i+=1
        while istart1<=iend1:
            arrtmp[i]=arr[istart1]
            i+=1
            istart1+=1
        while istart2<=iend2:
            arrtmp[i]=arr[istart2]
            i+=1
            istart2+=1
        # 把原来的数据拷贝回去
        for i in range(start,end+1):
            arr[i]=arrtmp[i]
    def sortArray(self):
        nums=self.dict_list
        if len(nums)<2:return nums
        arrtmp=[]
        for i in range(0,len(nums)):
            arrtmp.append(0)
        self.mergeSort(nums,arrtmp,0,len(nums)-1)
        print(nums)
        if self.Seq==0:
            nums=nums[-1::-1]
        return nums

class Student_score_info_list():
    def __init__(self, stu_info_list=[]):  # 提供缺省的参数，如果已有学生成绩 -- 可导入此类
        self.stu_info_list = stu_info_list  # 学生的列表
        self.sort_method = ['Advanced_Mathematics', 'English', 'College_Physics',
                            'total_score']
    def menu(self):
        print("*********************")
        print("------- 目录 --------")
        print("------ 1.add --------")
        print("------ 2.del --------")
        print("------ 3.search -----")
        print("------ 4.modify -----")
        print("------ 5.print ------")
        print("*********************")
        # print(self.stu_info_list)
        print("现在已经有",len(self.stu_info_list),"位学生的成绩")
    def start_working(self):  # 学生成绩管理系统开始运行
        while True:
            self.menu()
            sec=int(input("请输入:>"))
            if sec==1:
                # 添加学生信息
                person={}
                name=input("请输入名字:>")
                person['name']=name
                Advanced_Mathematics=int(input("请输入高数成绩:>"))
                person['Advanced_Mathematics']=Advanced_Mathematics
                English=int(input("请输入英语成绩:>"))
                person['English']=English 
                College_Physics=int(input("请输入大学物理成绩:>"))
                person['College_Physics']=College_Physics 
                person['total_score']=Advanced_Mathematics+English+College_Physics
                print("添加成功！")
                print()
                self.add_student_info(person)
            elif sec==2:
                # 删除学生成绩
                name=input("请输入要删除学生的名字:>")
                self.del_student_info(name)
                print()
            elif sec==3:
                name=input("请输入要查找学生的名字:>")
                self.search_student_info(name)
                print()
            elif sec==4:
                name=input("请输入要修改学生的名字:>")
                self.modify_student_info(name)
                print()
            elif sec==5:
                print("------- 打印方式 --------")
                print("---- 0.按照高数成绩降序 ----")
                print("---- 1.按照英语成绩降序 ----")
                print("---- 2.按照大物成绩降序 ----")
                print("---- 3.按照总分成绩降序 ----")
                print("---- 4.按照总分成绩升序 ----")
                sec=int(input("请选择:>"))
                self.print_info_list_by_method(sec)
                print()
            else:
                print("选择错误 -- 程序退出!")
                sys.exit()
    def print_list(self):
        print("------------- 学生成绩 -------------")
        # 利用DataFrame打印会更好看一些
        df=pd.DataFrame(self.stu_info_list)
        print(df)
        print("------------- 学生成绩 -------------")
    def print_info_list_by_method(self, sort_method_type):
        if sort_method_type == 0:
            class_sort = My_MergeSort_By_Student_score(
                self.stu_info_list, self.sort_method, 0, 0)
            self.stu_info_list = class_sort.sortArray()
            self.print_list()
            # 按照高数排序
            pass
        elif sort_method_type == 1:
            class_sort = My_MergeSort_By_Student_score(
                self.stu_info_list, self.sort_method, 1, 0)
            self.stu_info_list = class_sort.sortArray()
            self.print_list()
            # 按照英语排序
            pass
        elif sort_method_type == 2:
            class_sort = My_MergeSort_By_Student_score(
                self.stu_info_list, self.sort_method, 2, 0)
            self.stu_info_list = class_sort.sortArray()
            self.print_list()
            # 按照大学物理排序
            pass
        elif sort_method_type == 3:
            class_sort = My_MergeSort_By_Student_score(
                self.stu_info_list, self.sort_method, 3, 0)
            self.stu_info_list = class_sort.sortArray()
            self.print_list()
            # 按照总分排序 -- 降序
            pass
        elif sort_method_type == 4:
            class_sort = My_MergeSort_By_Student_score(
                self.stu_info_list, self.sort_method, 3, 1)
            self.stu_info_list = class_sort.sortArray()
            self.print_list()
            # 按照总分排序 -- 升序
            pass

    def add_student_info(self, person):  # 按照题目要求，此时的person应该是dict对象
        self.stu_info_list.append(person)

    def del_student_info(self, name):  # 删除名为name的学生成绩
        # 暴力查找名字
        for i in range(0, len(self.stu_info_list)):
            if self.stu_info_list[i]['name'] == name:
                self.stu_info_list.remove(self.stu_info_list[i])
                print("successfully removed!")
                if_removed = True
                return
        print("err,No information about the student!")

    def search_student_info(self, name):  # 查找名为name的学生成绩
        for i in range(0, len(self.stu_info_list)):
            if self.stu_info_list[i]['name'] == name:
                print("name:", self.stu_info_list[i]['name'])
                print("Advanced_Mathematics",
                      self.stu_info_list[i]['Advanced_Mathematics'])
                print("English", self.stu_info_list[i]['English'])
                print("College_Physics",
                      self.stu_info_list[i]['College_Physics'])
                print("total_score", self.stu_info_list[i]['total_score'])
                break
        print("err,No information about the student!")

    def modify_student_info(self, name):  # 修改名为name的学生成绩
        for i in range(0, len(self.stu_info_list)):
            if self.stu_info_list[i]['name'] == name:
                print("please modify the score info:")
                # 只允许修改分数，不允许修改名字
                new_total_score = 0
                new_score = int(input("Advanced_Mathematics:"))
                new_total_score += new_score
                self.stu_info_list[i]['Advanced_Mathematics'] = new_score
                new_score = int(input("English:"))
                new_total_score += new_score
                self.stu_info_list[i]['English'] = new_score
                new_score = int(input("College_Physics:"))
                new_total_score += new_score
                self.stu_info_list[i]['College_Physics'] = new_score
                # 更新总成绩
                self.stu_info_list[i]['total_score'] = new_total_score
                break


# ============================================ main ============================================== #
# 本成绩管理系统所有方法由 <Student_score_info_list> 类提供

# main函数


def main():
    s=Student_score_info_list()
    s.start_working()


if __name__ == '__main__':
    main()
