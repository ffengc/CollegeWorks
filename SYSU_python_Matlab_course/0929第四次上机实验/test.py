import sys


class Solution:
    def __init__(self):
        print("0929第四次上机")

    def test1(self):
        """
        1. 实现功能：
        1）用户输入一个字符串，实现该该字符串的倒序输出；
        2）用户输入两个参数，第一个参数为一个字符串，第二个参数为一个数字，
            输出字符串在该数字后全部字符（注意判断输入的数字是否合法）。
        :return:
        """
        str = input("请输入一串字符串：")
        print(str[::-1])
        str = input("请输入一串字符串:")
        num = int(input("请输入一个数字:"))
        while num >= len(str):
            print("err:输入不合法，请重新输入")
            num = int(input("请输入一个数字:"))

        print(str[num:])

    def print_string(self):
        str = input("请输入一串长度不小于16的字符串：")
        str_list = []
        path = ''
        i = 0
        while i < len(str):
            end = 0
            if 8 + i < len(str):
                end = 8 + i
            else:
                end = len(str)
            for j in range(i, end):
                path += str[j]
            str_list.append(path)
            path = ''
            i += 8
        # print(str_list)
        # 处理list的最后一个元素
        if len(str_list[len(str_list) - 1]) < 8:
            while len(str_list[len(str_list) - 1]) < 8:
                str_list[len(str_list) - 1] += '0'
        print(str_list)

    def test2(self):
        '''
        写一个函数print_string,连续输入长度不小于16的字符串，
        请按长度为8拆分每个字符串，并输出到新的字符串数组。
        长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
        :return:
        '''
        self.print_string()

    def test3(self):
        '''
        3. 实现功能：用户输入两个字符串，一长一短，
            判断用户输入的短字符串中的所有字符是否在另一个
            由用户输入的长字符串中全部出现。
        :return:
        '''
        str1 = input("请输入第一个字符串:")
        str2 = input("请输入第二个字符串:")
        if len(str1) > len(str2):
            str1, str2 = str2, str1
        # 令str1为短的字符串
        i = 0
        while i < len(str1):
            if str1[i] not in str2:
                print("false")
                sys.exit()
            i += 1
        print("true")

    def is_prime(self, x):
        # 判断一个数是不是质数
        for i in range(2, x):
            if x % i == 0: return False
        return True

    def prime_factors(self, x):
        ret = []
        i = 2
        while i <= x:
            if self.is_prime(i) == False:
                i += 1
                continue
            if x % i == 0:
                ret.append(i)
                x /= i
            else:
                i += 1
        return ret

    def test4(self):
        '''
        4. 写一个函数prime_factors，使得其输入一个正整数，
        按照从小到大的顺序输出它的所有质数的因子（如180的质数因子为2 2 3 3 5 ）,
        最后一个数后面也要以换行符结尾。
        :return:
        '''
        num = int(input("请输入一个整型："))
        print(self.prime_factors(num))

    def bubble_sort(self, num):
        sz = len(num)
        for i in range(0, sz - 1):
            for j in range(0, sz - 1 - i):
                if num[j] > num[j + 1]:
                    num[j], num[j + 1] = num[j + 1], num[j]

    def test5(self):
        '''
        5. 写一个函数bubble_sort对用户任意输入的10个数字实现冒泡排序算法。
        :return:
        '''
        num=[]
        sz=int(input("请输入你要输入的数字的个数："))
        for i in range(0,sz):
            tmp=int(input())
            num.append(tmp)
        print(num)
        self.bubble_sort(num)
        print(num)


def main():
    s = Solution()
    # s.test1()
    # s.test2()
    # s.test3()
    # s.test4()
    s.test5()


if __name__ == '__main__':
    main()
