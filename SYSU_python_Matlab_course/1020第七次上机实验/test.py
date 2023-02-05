


import numpy as np
import time

class Solution:
    def __init__(self) -> None:
        print("第七次上机实验")
    def test1(self):
        arr=[]
        for i in range(0,10):
            if i==0 or i==9:
                tmp=np.ones(10,dtype='uint8').tolist()
                arr.append(tmp)
            else:
                tmp=np.zeros(10,dtype='uint8').tolist()
                tmp[0],tmp[9]=1,1
                arr.append(tmp)
        print()
    def test2(self):
        arr=np.zeros(16).reshape(4,4)
        for i in range(0,4):
            arr[i][i]=i+1
        print()
    def test3(self):
        arr = np.random.randint(0,10,(5,5)) # 生成一个0-10，5*5的矩阵
        arr_normalization = (arr-arr.min())/(arr.max()-arr.min())
        print()
    def test4(self):
        arr =np.random.randint(0,30,30)
        print(arr.mean())
        print()
    def test5(self):
        arr=np.zeros(10)
        arr[4]=1
        print(arr)
    def test6(self):
        arr=np.arange(10,50)
        print(arr)
    def test8(self):
        arr=[]
        for i in range(0,5):
            tmp=[i for i in range(0,5)]
            arr.append(tmp)
        print(arr)
    def test9(self):
        arr=np.linspace(0,1,12)
        print(arr)
    def test10(self):
        arr=np.random.randint(0,10,10)
        print(arr)
        arr_sorted = np.sort(arr)
        print(arr_sorted)
    def test11(self):
        arr=np.random.randint(0,10,10)
        print(arr)
        arr[np.argmax(arr)]=0
        print(arr)
    def test12(self):
        # 生成一个5*5的随机矩阵
        arr=np.random.randint(0,20,(5,5))
        print(arr)
        arr_sorted = arr[np.argsort(arr[:,2])] # 按照第三列排序
        print(arr_sorted)
    def test13(self):
        arr=np.random.randint(0,10,(2,2,2,2))
        ax2=np.sum(arr,axis=2)
        ax3=np.sum(arr,axis=3)
        print(ax2+ax3)
    def test14(self):
        arr=np.random.random(size=100000)
        # 方法1
        begin=time.time()
        b=[]
        for i in range(0,len(arr)):
            b.append(arr[i]**3)
        end=time.time()
        print(end-begin)

        # 方法2
        begin=time.time()
        b=arr**3
        end=time.time()
        print(end-begin)
    def test15(self):
        arr=np.random.randint(0,10,(5,5))
        for i in range(0,len(arr)):
            arr[i,:]=arr[i,:]-arr[i,:].mean()
        print(arr)
    def test17(self):
        arr1=np.random.randint(0,10,(5,3))
        arr2=np.random.randint(0,10,(3,2))
        print()
        print(arr1@arr2)
    
    def test18(self):
        arr1=np.random.randint(0,10,(5,5))
        i=1
        j=3
        arr1[[i, j], :] = arr1[[j, i], :]
        print(arr1)

    def test19(self):
        arr=[1,2,3,4,5]
        arr_inserted=[]
        for i in range(0,len(arr)):
            arr_inserted.append(arr[i])
            for j in range(3):
                arr_inserted.append(0)
        print(arr_inserted)

s=Solution()
# s.test1()
# s.test2()
# s.test3()
# s.test4()
# s.test5()
# s.test6()
# s.test8()
# s.test9()
# s.test10()
# s.test11()
# s.test12()
# s.test13()
# s.test14()
# s.test15()
# s.test3()
# s.test17()
# s.test18()
s.test19()