


from cgi import print_arguments


def test1():
    # 现在有一个列表，要把里面的元素+1
    # 1.for循环的做法
    # 2.列表生成式实现
    list_data1=[0,1,2,3,4,5]
    list_data2=[i+1 for i in list_data1]
    print(list_data2)
    # 无论是方法1和方法2，都要直接创建一个列表
    # 生成器的做法 -- 就是把生成式的[]改为()，就创建了一个generator
    list_data3=(i+1 for i in list_data1)
    print(type(list_data3)) # <class 'generator'>
    print(list_data3) # <generator object test1.<locals>.<genexpr> at 0x000001F66BD06420>
    # 如果要把生成器的元素打印出来 -- 该如何处理呢？
    # 可以使用next函数获得generator的下一个返回值

    # 如果像p111那样一个一个调用next来打印，是一个不好的习惯，正确的方式是用for循环迭代，因为generator是可迭代对象
    for i in list_data3:
        print(i)
test1()