# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import random


class Solution_0915_1:
    def __init__(self):
        print("0915人工智能编程语言第三次上机 -- python的基本操作")
        print()

    def test1(self):
        """
        1. 有如下两个列表l1,l2=[1,2,1,3,4,6,9],[1,2,5,6,7]：
            1)	将两个列表分别转换为元组、集合
            2)	输出两个列表的交集，输出交集的元素遍历
            3)	输出两个列表的并集(去除重复元素)，并输出并集中元素的数目
            4)	输出两个列表的分别的差集
        :return:
        """
        l1 = [1, 2, 1, 3, 4, 6, 9]
        l2 = [1, 2, 5, 6, 7]
        # 1
        tup1 = tuple(l1)
        tup2 = tuple(l2)
        print(tup1, tup2, type(tup1), type(tup2))
        set1 = set(l1)
        set2 = set(l2)
        print(set1, set2, type(set1), type(set2))
        # 2
        list3 = list(set1 & set2)
        print(list3)
        for i in list3:  # 遍历输出
            print(i)
        # 3
        list4 = list(set1 | set2)
        print(list4, "元素个数为：", len(list4))
        # 4
        list5 = list(set1 - set2)
        list6 = list(set2 - set1)
        print(list5, list6)

    def test2(self) -> bool:
        """
        2. 判断一个用户输入的短字符串中的所有字符是否在另一个由用户输入的长字符串中全部出现。
        :return:
        """
        str_short = input("请输入一个短字符串:")
        str_long = input("请输入一个长字符串:")
        for i in range(len(str_short)):
            if (str_short[i] not in str_long):
                return False
        return True

    def test3(self):
        """
        3. 在计算机随机生成的N个1～100之间的随机整数(N<=100)，
        N是用户输入的，对于其中重复的数字，只保留一个，
        把其余相同的数字去掉，然后再把这些数从小到大排序并输出最后结果。
        :return:
        """
        arr = []
        N = int(input("请输入N的值:"))
        for i in range(0, N):
            arr.append(random.randint(1, 100))
        print(arr)
        set_arr = list(set(arr))
        set_arr.sort()
        print(set_arr)


s = Solution_0915_1()
# s.test1()
# print(s.test2())
s.test3()
