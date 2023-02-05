# 0908第二次上机
# 第二题

class Solution_0908_2:
    """
    1)	定义名为tup的元组使1,2,3,4,5,6,7为其中元素。
    2)	输出tup的长度，并将tup转为list类型。
    3)	创建一个包含字符串字母的元组
    4)	创建一个元组，其中包含字符串的全部字母，但不包含其首字母
    5)	反转上面创建的元组
    """
    def __init__(self):
        print("0908人工智能编程语言第二次上机 第二题")

    def test(self):
        # 1)
        tup=(1,2,3,4,5,6,7)
        # 2)
        print(len(tup))
        print("现在的类型是：",type(tup))
        tup=list(tup)
        print("强转之后的类型是：",type(tup))
        # 3)
        str="Hello Python"
        tup=tuple(str)
        print(tup)
        # 4)
        tup=tuple(str[1:])
        print(tup)
        # 5)
        tup=list(tup)
        tup.reverse()
        tup=tuple(tup)
        print(type(tup))
        print(tup)


s = Solution_0908_2()
s.test()