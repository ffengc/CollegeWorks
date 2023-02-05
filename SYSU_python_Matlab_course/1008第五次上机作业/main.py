
import pandas as pd
from itertools import permutations


class Solution:
    def __init__(self):
        print("1008上机实验")
    def get_fib(self,x):
        if x==1 or x==2:
            return 1
        ans=[]
        ans.append(1)
        ans.append(1)
        for i in range(2,x):
            ans.append(ans[i-1]+ans[i-2])
        return ans[x-1]
    def get_fib_R(self,x):
        if x==1 or x==2:
            return 1
        return self.get_fib_R(x-1)+self.get_fib_R(x-2)
    def test1(self):
        '''
        1. 用 普通函数 实现斐波拉契数列，打印前100个值，以列表格式输出。
            例：1，1，2，3，5，8，13，21，34，55，89...
            （这个数列从第3项开始，每一项都等于前两项之和）
        '''
        fib_list=[]
        fib_list.append(1)
        fib_list.append(1)
        for i in range(3,101):
            fib_list.append(self.get_fib_R(i))
        print(fib_list)
    def info_to_dict(self,name,number,**kwargs):
        dict_name_num={}
        dict_name_num['name']=name
        dict_name_num['number']=number
        dict_name_num.update(kwargs)
        return dict_name_num
    def test2(self):
        '''
        3. 编写一个函数，将学生信息储存在字典中。
            该函数总是接受姓名和学号，还可接受任意数量的关键字实参。
            使用如下方法调用：提供必备的信息，以及其他名称值对，
            包括性别、身高、籍贯、选课、爱好（可以只录入部分信息）。
            完成10人的信息统计，打印返回的字典，确保信息正确性。
        '''
        student_info_list=[]
        sz=int(input("请输入要录入的人数:"))
        for i in range(0,sz): 
            # 存储10个学生的信息
            print(f"请输入第{i+1}个人的信息")
            name=input("请输入名字:")
            number=input("请输入学号:")
            _sex=input("请输入性别:")
            _height=input("请输入身高:")
            _local=input("请输入籍贯:")
            _class_choose=input("请输入选课:")
            _hobby=input("请输入爱好:")
            student_info_list.append(self.info_to_dict(name,number,sex=_sex,height=_height,\
                local=_local,class_choose=_class_choose,hobby=_hobby))
        print(student_info_list)
        df=pd.DataFrame(student_info_list) # 返回的是字典列表，转化成DataFrame类型打印更为美观
        print(df)
    def is_Valid(self,x):
        sq_x=x**2
        x=str(x)
        sq_x=str(sq_x)
        if x in sq_x:
            return True
        else: 
            return False
    def test3(self):
        '''
        4. 自守数判断：
            自守数是指一个数的平方的尾数等于该数自身的自然数。
            例如：25^2 = 625，76^2 = 5776，9376^2 = 87909376。
            请求出n(包括n)以内的自守数的个数（1≤n≤10000）
        '''
        n=int(input("请输入n的数值:"))
        cnt=0
        for i in range(1,n+1):
            if self.is_Valid(i):
                cnt+=1
        print(cnt)
    def get_max_length(self,x):
        max_length=0
        length=0
        for i in range(0,32):
            if (x>>i)&1==1:
                # 说明当前位是1
                length+=1
                if max_length<length: max_length=length
            else:
                # 说明当前位是0
                length=0
        return max_length
    def test4(self):
        '''
        求一个int类型数字对应的二进制数字中1的最大连续数，例如3的二进制为00000011，最大连续2个1
        '''
        n=int(input("请输入一个int类型整数:"))
        print(self.get_max_length(n))
    def get_Permutation(self,my_list):
        # 现在要得到四个数的所有排列
        ret=[]
        path=[]
        def dfs(list):
            if len(path)==len(my_list):
                ret.append(tuple(path))
                return
            
        dfs(my_list)

        
    def test5(self):
        '''
        （附加题，注意使用递归）24点判断：给出4个1-10的数字，通过加减乘除运算，
        得到数字为24就算胜利。除法指实数除法运算,运算符仅允许出现在两个数字之间,本题对数字选取顺序无要求，
        但每个数字仅允许使用一次。
            例：输入：7 2 1 10
            输出：true
            输入：1 2 2 3
            输出：false
        '''
        a = int(input("请输入第1个数字:"))
        b = int(input("请输入第2个数字:"))
        c = int(input("请输入第3个数字:"))
        d = int(input("请输入第4个数字:"))
        my_list = [a, b, c, d]
        # 对4个整数随机排列的列表
        result = [c for c in permutations(my_list, 4)]
        # 此时的result里面有四个数所有的排列元组
        symbols = ["+", "-", "*", "/"]
        
        list2 = []  # 算出24的排列组合的列表
        
        flag = False
        
        for one, two, three, four in result:
            for s1 in symbols:
                for s2 in symbols:
                    for s3 in symbols:
                        if s1 + s2 + s3 == "+++" or s1 + s2 + s3 == "***":
                            express = ["{0}{1}{2}{3}{4}{5}{6}".format(one, s1, two, s2, three, s3, four)]  # 全加或者乘时，括号已经没有意义。
                        else:
                            express = ["(({0}{1}{2}){3}{4}){5}{6}".format(one, s1, two, s2, three, s3, four),
                                    "({0}{1}{2}){3}({4}{5}{6})".format(one, s1, two, s2, three, s3, four),
                                    "(({0}{1}({2}{3}{4})){5}{6})".format(one, s1, two, s2, three, s3, four),
                                    "{0}{1}(({2}{3}{4}){5}{6})".format(one, s1, two, s2, three, s3, four),
                                    "{0}{1}({2}{3}({4}{5}{6}))".format(one, s1, two, s2, three, s3, four)]
        
                        for e in express:
                            try:
                                if eval(e) == 24:
                                    list2.append(e)
                                    flag = True
                            except ZeroDivisionError:
                                pass
        
        list3 = set(list2)  # 去除重复项
        if len(list3)>0:
            print("True")
        else:
            print("False")
        # for c in list3:
        #     print("YES：", c)
        
        # if not flag:
        #     print("NO！")

def main():
    s=Solution()
    # s.test1()
    # s.test2()
    # s.test3()
    # s.test4()
    s.test5()
    


if __name__=='__main__':
    main()