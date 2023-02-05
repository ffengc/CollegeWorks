


import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from pylab import *
mpl.rcParams['font.sans-serif'] = ['SimHei']

class Solution:
    def __init__(self) -> None:
        print("1027第九次上机实验")
    def test1(self):
        '''课上内容 -- 见课上内容dir'''
    def test2(self):
        x = np.linspace(-10,10,100)
        y = 2*x+1
        plt.plot(x,y)
        plt.show()
    def test3(self):
        # y = x2 - 2x + 1
        x = np.linspace(-10,10,100)
        y=x**2-2*x+1
        plt.plot(x,y)
        plt.show()
    def test4(self):
        # 一张画布中画多张图
        x = np.linspace(-10,10,100)
        y1=np.sin(x)
        y2=np.exp(x)
        y3=np.log(x)
        y4=np.abs(x)
        plt.subplot(2,2,1)
        plt.plot(x,y1)
        plt.subplot(2,2,2)
        plt.plot(x,y2)
        plt.subplot(2,2,3)
        plt.plot(x,y3)
        plt.subplot(2,2,4)
        plt.plot(x,y4)
        plt.show()
    def test5(self):
        # 画出10个随机的离散点（scatter方法）
        arr = np.random.randint(-10,10,(10,2))
        plt.scatter(arr[:,0],arr[:,1])
        plt.show()
    def test6(self):
        a = ["战狼2","速度与激情8","功夫瑜伽","西游伏妖篇","变形金刚5：最后的骑士",
            "摔跤吧！爸爸","加勒比海盗5：死无对证","金刚：骷髅岛","极限特工：终极回归",
            "生化危机6：终章","乘风破浪","神偷奶爸3","智取威虎山","大闹天竺",
            "金刚狼3：殊死一战","蜘蛛侠：英雄归来","悟空传","银河护卫队2","情圣","新木乃伊"]
        b = [56.01, 26.94,17.53,16.49,15.45,12.96,11.8,11.61,
            11.28,11.12,10.49,10.3,8.75,7.55,7.32,6.99,6.88,6.86,
            6.58,6.23]
        # 直方图
        plt.bar(a,b)
        plt.show()
    def test7(self):
        '''
        knn预测鸢尾花种类
        :return:
        '''
        # 1.获取数据
        iris = np.array(pd.read_csv('data.csv')[:-1,:])

        # 2.数据集划分
        x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.2, random_state=6)

        # 3.特征工程（标准化）
        transfer = StandardScaler()
        # x_train,x_test的标准差、平均值得一样
        x_train = transfer.fit_transform(x_train)
        x_test = transfer.transform(x_test)

        # 4.KNN算法预估器（n_neighbors就是K）
        estimator = KNeighborsClassifier(n_neighbors=3)
        estimator.fit(x_train,y_train) # 完成训练

        # 5.模型评估
        # 5.1 方法1：直接对比真实值与预测值
        y_predict = estimator.predict(x_test)
        print('y_predict:\n', y_predict)


s = Solution()
# s.test2()
# s.test3()
# s.test4()
# s.test5()
s.test6()