


import matplotlib.pyplot as plt
import numpy as np


def test1():
    # plot的各种操作 -- 查ppt
    
    # 直方图
    pop = np.random.randint(0,100,100)
    plt.hist(pop,bins=20)
    plt.show()
    
    # 条形图
    index = [0,1,2,3,4]
    values=[5,7,3,4,6]
    plt.bar(index,values)
    plt.show()

    # 水平条形图
    index = np.arange(5)
    values1=[5,7,3,4,6]
    std1=[0.8,1,0.4,0.9,1.3]
    plt.barh(index,values1,xerr=std1,error_kw={'ecolor':'0.1','capsize':6},alpha=0.7,label='First')
    plt.yticks(index,['A','B','C','D','E'])
    plt.show()

def test2():
    # 饼图
    labels=['Nokia','Samsung','Apple','Lumia']
    values=[10,30,45,15]
    colors=['yellow','green','red','blue']
    plt.pie(values,labels=labels,colors=colors)
    plt.axis('equal')
    plt.show()

    # 等值线图
    def f(x,y):
        return (1-y**5+x**5)*np.exp(-x**2-y**2)
    x = np.arange(-2.0,2.0,0.01)
    y = np.arange(-2.0,2.0,0.01)
    X,Y=np.meshgrid(x,y)
    C=plt.contour(X,Y,f(X,Y),8,colors='black')
    plt.contourf(X,Y,f(X,Y),8)
    plt.clabel(C,inline=1,fontsize=10)
    plt.show()

from mpl_toolkits.mplot3d import Axes3D
def test3():
    def f(x,y):
        return (1-y**5+x**5)*np.exp(-x**2-y**2)
    fig = plt.figure()
    ax = Axes3D(fig)
    X = np.arange(-2.0,2.0,0.1)
    Y = np.arange(-2.0,2.0,0.1) 
    X,Y = np.meshgrid(X,Y)
    ax.plot_surface(X,Y,f(X,Y),rstride=1,cstride=1)
    plt.show()

test3()