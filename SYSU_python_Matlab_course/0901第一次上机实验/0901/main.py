
# 21312780 俞沣城
class Solution_0901():
    # 构造
    def __init__(self):
        print("0901人工智能编程语言上机")
    # 题目1：循环输出hello world
    def test1(self,_input):
        for i in range(_input):
            print("hello world")


    # 题目2：
    def test2(self):
        a = b = c = 2  # 给三个变量赋一样的值
        print(a, b, c)
        x, y, z = 1, 2, 3  # 给三个变量赋值
        print(x, y, z)
        # 给一个五位正整数，逆序输出
        num=input("请输入一个五位的正整数：")
        print(num[::-1])

    # 题目三
    def test3(self):
        ###
        str1=input("请输入第一个字符串：")
        str2=input("请输入第二个字符串")
        print("字符串拼接后的结果为：",str1+str2)
        ###
        str=str1+str2
        print("字符串拼接后的长度为",len(str))
        ###
        print("字符串转大写：",str.upper())
        ###
        str3=input("请输入一个字符串")
        str3=str3.lower() # 全部转化为小写
        ch=input("请输入一个字符：")
        ch=ch.lower() # 全部转化成小写
        # 遍历字符串
        cnt=0
        for i in range(len(str3)):
            if(str3[i]==ch):
                cnt+=1
        print("字符在字符串中出现的次数为",cnt,"次")

    # 题目4
    def test4(self):
        # 类型转化练习
        str1="abcd"
        num=1
        arr=[1,2,3]
        arr_null=[]
        print(bool(str1),bool(num),bool(arr),bool(arr_null))

        dict={'1':'123'}
        num=1
        arr=[1,2,3]
        print(str(num),str(dict),str(arr))

    # 题目5
    # list可以修改，tuple不能修改，dict本质是哈希表，key一定要能可哈希，集合元素需要可哈希



s=Solution_0901()
# _input = input("请输入要循环的次数：")
# s.test1(int(_input))
# s.test2()
# s.test3()
s.test4()
