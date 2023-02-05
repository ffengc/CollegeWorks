# 0908第二次上机
# 第一题

class Solution_0908_1:
    def __init__(self):
        print("0908人工智能编程语言第二次上机 第一题")

    def test1(self):
        """
        1)	有如下一个列表list=[2, 5, 6, 7, 8, 9, 2, 9, 9], 请写程序完成以下操作：
            a)	在列表的末尾增加元素15
            b)	在列表的中间位置插入元素20
            c)	将列表[2, 5, 6]合并到list中
            d)	移除列表中索引为3的元素
            e)	翻转列表里的所有元素
            f)	对列表里的元素进行排序，从小到大一次，从大到小一次
        """
        arr=[2,5,6,7,8,9,2,9,9]
        arr.append(15)
        print(arr)
        arr.insert(int(len(arr)/2),20)
        print(arr)
        arr2=[2,5,6]
        arr.extend(arr2)
        print(arr)
        arr.pop(3)
        print(arr)
        arr.reverse()
        print(arr)
        arr.sort(reverse=False)
        print(arr)
        arr.sort(reverse=True)
        print(arr)
    def My_double(self,ListOrTuple):
        for i in range(len(ListOrTuple)):
            ListOrTuple[i]=ListOrTuple[i]*2
        return ListOrTuple
    def test2(self):
        """
        2)	list = [1, [4, 6], True]，请将列表里所有数字修改成原来的两倍。
        """
        a=1 # 建立一个整形
        b=[] # 建立一个list
        c=(1,) # 建立一个tuple
        list = [1, [4, 6], True]
        for i in range(len(list)):
            if(type(list[i])==type(a)):
                # 说明是整型
                list[i]=list[i]*2
            elif (type(list[i])==type(b) or type(list[i])==type(c)):
                # 说明是list 或者是 tuple
                # 调用My_double()函数
                list[i]=self.My_double(list[i])
        print(list)

    def test3(self):
        """
        3)	创建名为Names的空列表，向列表中添加如下元素: ZhangSan, LiSi, WangWu, XiaoMing。
            a)	在3)的列表中XiaoMing前面插入”LiLi”
            b)	将列表中的ZhangSan改为“张三”
            c)	创建新列表[1,2,3,4,5,6]，合并到Names列表中
            d)	取出names列表中索引2-5的元素
            e)	循环Names列表，打印每个元素的索引值和元素
            f)	循环Names列表，打印每个元素的索引值和元素，当索引值为偶数时，把对应的元素改成-1
        """
        Names = []
        Names.extend(['ZhangSan', 'LiSi', 'WangWu', 'XiaoMing'])
        print(Names)
        # a
        idx = Names.index('XiaoMing')  # 这个是我要插入的节点的位置
        Names.insert(idx, "LiLi")
        print(Names)
        # b
        idx = Names.index('ZhangSan')  # 这个是我要插入的节点的位置
        Names[idx] = "张三"
        print(Names)
        # c
        list = [1, 2, 3, 4, 5, 6]
        Names.extend(list)
        print(Names)
        # d
        print(Names[2:5])
        # e
        for i in range(len(Names)):
            print("索引为:", i, "的元素为:", Names[i])
        # f
        for i in range(len(Names)):
            if i % 2 == 0:
                Names[i] = -1
            print("索引为:", i, "的元素为:", Names[i])


s = Solution_0908_1()
# s.test1()
# s.test2()
s.test3()
