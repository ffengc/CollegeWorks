

from base64 import encode
from email.header import decode_header
import random
from typing_extensions import Self
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cv2
import imageio

# 遗传算法


class GeneticAlgorithm:
    def __init__(self, P0, pc, pm, Gen) -> None:
        self.P0 = P0  # 初始种群数
        self.pc = pc  # 交叉概率
        self.pm = pm  # 变异概率
        self.iterator = Gen  # 迭代次数
        self.img_list = []  # 用于生成gif
        self.label = f'Gen={Gen},P={P}'

    def fun(self, x):  # 定义要求的函数
        return x*np.sin(10*np.pi*x)+2

    def plot_the_function_2d(self):
        xs = np.linspace(-1, 2, 100)
        plt.plot(xs, self.fun(xs))
        plt.show()

    def __ori_popular(self, num, _min=-1, _max=2):  # 初始化种群
        return np.random.uniform(_min, _max, num)  # 范围[-1,2)

    def __encodeFun(self, popular, _min=-1, _max=2, scale=2**18, bin_len=18):  # 二进制编码
        '''bin_len 染色体序列长度'''
        norm_data = (popular - _min)/(_max-_min)*scale  # 把种群标准化变换
        bin_data = np.array([np.binary_repr(x, width=bin_len)
                            for x in norm_data.astype(int)])
        return bin_data

    def __decodeFun(self, popular_gene, _min=-1, _max=2, scale=2**18):
        return np.array([(np.int(x, base=2)/scale*3)+_min for x in popular_gene])

    def __select_and_crossover(self, chroms, fitness):
        prob = self.pc
        probs = fitness/np.sum(fitness)  # 各个个体被选择的概率
        probs_sum = np.cumsum(probs)  # 概率累加分布
        # 产生均匀分布的伪随机
        each_rand = np.random.uniform(size=len(fitness))
        # 根据随机概率选择出新的基因编码
        newX = np.array([chroms[np.where(probs_sum > rand)[0][0]]
                        for rand in each_rand])
        # 随机配对，概率为prob
        pairs = np.random.permutation(int(len(newX)*prob//2*2)).reshape(-1, 2)
        center = len(newX[0])//2
        for i, j in pairs:
            # 在中间位置交叉
            x, y = newX[i], newX[j]
            newX[i] = x[:center] + y[center:]
            newX[j] = y[:center] + x[center:]
        return newX

    def __mutate(self, chroms):
        prob = self.pm
        clen = len(chroms[0])
        m = {'0': '1', '1': '0'}  # 用一个字典，方便反转染色体上的基因
        newchroms = []
        each_prob = np.random.uniform(size=len(chroms))
        for i, chrom in enumerate(chroms):
            if each_prob[i] < prob:
                pos = np.random.randint(clen)
                chrom = chrom[:pos]+m[chrom[pos]]+chrom[pos+1:]  # 把pos位置的基因反转
            newchroms.append(chrom)
        return np.array(newchroms)

    def plot_res(self, chroms1, fitfun, epoch):
        xs = np.linspace(-1, 2, 1000)

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
        np.random.seed(0)
        population = self.__ori_popular(self.P0)  # 100个样本点
        chroms = self.__encodeFun(population)
        
        for i in range(self.iterator):
            fitness = self.fun(self.__decodeFun(chroms))
            fitness = fitness - fitness.min() + 0.000001
            newchroms = self.__mutate(
                self.__select_and_crossover(chroms, fitness))
            if i % 2 == 0:  # 每10个epoch打印一次
                self.plot_res(newchroms, self.fun, i)
            chroms = newchroms  # 迭代
        self.plot_res(newchroms, self.fun, self.iterator)
        imageio.mimsave("test.gif", self.img_list, fps=1)
        print()


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


def main():
    ga = GeneticAlgorithm(10, 0.6, 0.1, 20)
    # ga.plot_the_function_2d()
    ga.train()


if __name__ == '__main__':
    # plot_the_function_3d()
    main()
