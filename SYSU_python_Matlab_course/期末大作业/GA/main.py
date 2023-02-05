

from turtle import color
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib.gridspec as gridspec


from base64 import encode
from cmath import exp, sin
from email.header import decode_header
from os import X_OK
import random
import re
from typing_extensions import Self
from xml.dom.minidom import ReadOnlySequentialNamedNodeMap
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cv2
import imageio.v2 as imageio
from functools import cmp_to_key


# 遗传算法


class GeneticAlgorithm:
    def __init__(self, P0, pc, pm, Gen,P) -> None:
        self.P0 = P0  # 初始种群数
        self.P = P
        self.pc = pc  # 交叉概率
        self.pm = pm  # 变异概率
        self.iterator = Gen  # 迭代次数
        self.img_list = []  # 用于生成gif
        self.x_true = 1.23 # 函数真实的极大值点
        self.label = f'Gen={Gen}_P={P}_P0={P0}_pc={pc}_pm={pm}'

    def fun(self, x):  # 定义要求的函数
        # return x*np.sin(10*np.pi*x)+2
        # return x*(np.sin(x))*np.exp(np.sin(x)+1)
        # return -(x-2)*(x-2)
        return x*np.sin(x*x)*np.exp(np.cos(x))

    def plot_the_function_2d(self):
        xs = np.linspace(-1, 2, 100)
        plt.plot(xs, self.fun(xs))
        plt.show()

    def __ori_popular(self, num, _min=0, _max=4):  # 初始化种群
        return np.random.uniform(_min, _max, num)  # 范围[0,4]

    def __encodeFun(self, popular, _min=0, _max=4, scale=2**18, bin_len=18):  # 二进制编码
        '''bin_len 染色体序列长度'''
        norm_data = (popular - _min)/(_max-_min)*scale  # 把种群标准化变换
        bin_data = np.array([np.binary_repr(x, width=bin_len)
                            for x in norm_data.astype(int)])
        return bin_data
    def __decodeFun(self, popular_gene, _min=0, _max=4, scale=2**18):
        return np.array([(np.int(x, base=2)/scale*3)+_min for x in popular_gene])

    def __crossover(self, chroms):
        assert(len(chroms) == self.P0)
        prob = self.pc
        # 此时chroms的长度应该是P0
        times = self.P-self.P0
        # 先把chroms改成list 方便append
        chroms = chroms.tolist()
        for i in range(0,times):
            ran_size = int(self.P0*prob) # 要随机生成的整数个数
            sz = len(chroms)
            if len(chroms)%2==1:
                sz = len(chroms)-1
            ran = random.sample(range(0,len(chroms)),sz)
            ran = np.array(ran).reshape(-1,2)
            # 此时要确定交叉的范围
            start_idx = random.randint(1,12) 
            cross_len = random.randint(3,len(chroms[0])-start_idx-1)
            end_idx = start_idx + cross_len
            # 此时ran应该是一个拥有两列的矩阵
            X_to_choose = []
            for i,j in ran:
                # 此时要把下标为i,j的染色体进行交叉操作
                newX1 = chroms[i][:start_idx]+chroms[j][start_idx:end_idx]+chroms[i][end_idx:]
                newX2 = chroms[j][:start_idx]+chroms[i][start_idx:end_idx]+chroms[j][end_idx:]
                X_to_choose.append(newX1);X_to_choose.append(newX2)
            # 在 X_to_choose 里面挑选 fit最大的进入种群
            X_to_choose_fit = self.fun(self.__decodeFun(X_to_choose)).tolist()
            idx = X_to_choose_fit.index(max(X_to_choose_fit))
            chroms.append(X_to_choose[idx])
        chroms = np.array(chroms)
        return chroms  # 此时的种群已经扩充到P了

    def __mutate(self, chroms):
        assert(len(chroms) == self.P)
        prob = self.pm
        clen = len(chroms[0])
        m = {'0': '1', '1': '0'}  # 用一个字典，方便反转染色体上的基因
        newchroms = []
        each_prob = np.random.uniform(size=len(chroms))
        for i, chrom in enumerate(chroms):
            if each_prob[i] < prob:
                pos = np.random.randint(clen-1)
                chrom = chrom[:pos]+m[chrom[pos]]+chrom[pos+1:]  # 把pos位置的基因反转
            newchroms.append(chrom)
        return np.array(newchroms)
    def __select(self,chroms):
        assert(len(chroms) == self.P)
        # 挑选出chroms中fit前P0大的，其它的淘汰
        fit = self.fun(self.__decodeFun(chroms))
        Number_of_eliminated = self.P-self.P0 # 要淘汰的个数
        def comp(e1,e2):
            if e1[1]<e2[1]:return -1
            elif e1[1]>e2[1]:return 1
            else:return 0      
        pair_list = []
        for i in range(0,len(chroms)):
            pair_list.append((chroms[i],fit[i]))
        pair_list.sort(key = cmp_to_key(comp))
        pair_list = np.array(pair_list)
        newX = pair_list[:,0]
        newX = newX[Number_of_eliminated:]
        np.random.shuffle(newX)
        assert(len(newX) == self.P0)
        return newX
    def __get_best_sample(self,chroms):
        population_final = self.__decodeFun(chroms)
        fitness = self.fun(population_final).tolist()
        idx = fitness.index(min(fitness))
        return population_final[idx]
    def plot_res(self, chroms1, fitfun, epoch):
        xs = np.linspace(0, 4, 1000)

        dechroms = self.__decodeFun(chroms1)
        fitness = fitfun(dechroms)
        plt.plot(xs, fitfun(xs),label='Function image')
        plt.plot(dechroms, fitness, 'o',label='Particle swarm')
        plt.grid(True)
        plt.xlabel(f'epoch:{epoch}', fontsize=15, fontname="Times New Roman")
        plt.title('Genetic process',fontsize=15, fontname="Times New Roman")
        plt.savefig('save.png', dpi=400)
        img = imageio.imread('save.png')
        self.img_list.append(img)
        plt.close()  # 这里要关闭，不然图像会重叠！
        # plt.show()

    def train(self):
        # np.random.seed(0)
        population = self.__ori_popular(self.P0)  # 100个样本点
        chroms = self.__encodeFun(population)
        diff_true_pred_list = []
        for i in range(self.iterator):
            fitness = self.fun(self.__decodeFun(chroms))
            fitness = fitness - fitness.min() + 0.000001
            newchroms = self.__mutate(
                self.__crossover(chroms))
            # 现在的newchroms的大小是P，现在要选择好的种群，把大小重新回到P0
            newchroms = self.__select(newchroms)
            if i % 1 == 0:  # 每1个epoch打印一次
                self.plot_res(newchroms, self.fun, i)
                x_pred = self.__get_best_sample(newchroms)
                diff_true_pred_list.append(np.abs(x_pred-self.x_true))
            chroms = newchroms  # 迭代
        self.plot_res(newchroms, self.fun, self.iterator)
        imageio.mimsave(f"test_{self.label}.gif", self.img_list, fps=1)
        # 现在要返回最优个体
        return self.__get_best_sample(chroms),diff_true_pred_list
        


def plot_the_function_3d():
    fig = plt.figure(figsize=(5, 5))  # 设置画布大小
    ax = Axes3D(fig)
    x = np.arange(-4, 4, 0.01)
    y = np.arange(-4, 4, 0.01)
    # 生成x,y网络坐标矩阵
    x, y = np.meshgrid(x, y)
    z = x-(1./9)*x**3-(1./2)*y**2
    # 设置配色风格
    ax.plot_surface(x, y, z, cmap='viridis')
    plt.show()

def print_difference_change_trend(arr):
    # 打印差值变化的趋势
    x = []
    for i in range(0,len(arr)):
        x.append(i)
    assert(len(x)==len(arr))
    fig,ax = plt.subplots(figsize=(7,5),dpi=400)
    ax.plot(x,arr,marker='o')
    ax.grid(True)
    
    plt.xlabel('epoch', fontsize=15, fontname="Times New Roman")
    plt.title('diff_change_trend',fontsize=15, fontname="Times New Roman")
    plt.xlim(0,len(arr))
    plt.ylim(0,1)
    plt.savefig('trend.png', dpi=400)
    plt.close()
    
def print_all_difference_change_trend(arr_all):
    # color_list = ['magenta','blue','green','black','red','yellow']
    # color_list = ['red','blue']
    # assert(len(color_list)==len(arr_all))
    fig,ax = plt.subplots(figsize=(7,5),dpi=400)
    ax.grid(True)
    for i in range(0,len(arr_all)):
        arr = arr_all[i][0] # diff_list
        label_ = arr_all[i][1]  # 要打印的标签
        # 打印差值变化的趋势
        x = []
        for j in range(0,len(arr)):
            x.append(j)
        assert(len(x)==len(arr))
        ax.plot(x,arr,label = label_ ,marker='o')# ,color = color_list[i])
        ax.legend()
        
    plt.xlabel('epoch', fontsize=15, fontname="Times New Roman")
    plt.title('diff_change_trend',fontsize=15, fontname="Times New Roman")
    plt.xlim(0,len(arr))
    # plt.ylim(0,1)
    plt.savefig('trend.png', dpi=400)
    plt.close()
    
def main():
    '''
    def __init__(self, P0, pc, pm, Gen,P):
    '''
    diff_list_arr = []
    ga = GeneticAlgorithm(10, 0.6, 0.2,10,15)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=10,P0=10,P=15,pc=0.6,pm=0.2'))
    # print_difference_change_trend(diff_list)
    ga = GeneticAlgorithm(10, 0.6, 0.2,20,15)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=10,P=15,pc=0.6,pm=0.2'))
    ga = GeneticAlgorithm(10, 0.6, 0.1,20,15)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=10,P=15,pc=0.6,pm=0.1'))
    ga = GeneticAlgorithm(10, 0.6, 0.5,20,15)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=10,P=15,pc=0.6,pm=0.5'))
    ga = GeneticAlgorithm(10, 0.2, 0.2,20,15)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=10,P=15,pc=0.2,pm=0.2'))
    ga = GeneticAlgorithm(20, 0.6, 0.2,20,30)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=20,P=30,pc=0.6,pm=0.2'))
    ga = GeneticAlgorithm(5, 0.6, 0.2,20,7)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=5,P=7,pc=0.6,pm=0.2'))
    ga = GeneticAlgorithm(3, 0.6, 0.2,20,4)
    final_pred_x, diff_list = ga.train()
    diff_list_arr.append((diff_list,'Gen=20,P0=3,P=4,pc=0.6,pm=0.2'))
    print_all_difference_change_trend(diff_list_arr)
    print()


if __name__ == '__main__':
    # plot_the_function_3d()
    main()