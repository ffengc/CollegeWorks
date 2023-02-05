
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

def test(self):
    xs = np.linspace(-1, 2, 100)
    np.random.seed(0)  # 设置随机种子
    population = self.__ori_popular(self.P0)  # 给十个种群
    for pop, fit in zip(population, self.fun(population)):
        print("x=%5.2f, fit=%.2f" % (pop, fit))
    # plt.plot(xs,self.fun(xs))
    # plt.plot(population,self.fun(population),"*")
    # plt.show()
    chroms = self.__encodeFun(population)
    for pop, chrom, fit in zip(population, chroms, self.fun(population)):
        print("x=%.2f, chorm=%s, fit=%.2f" % (pop, chrom, fit))
    fitness = self.fun(self.__decodeFun(chroms))
    for pop, chorm, dechrom, fit in zip(population, chroms, self.__decodeFun(chroms), fitness):
        print("x=%5.2f, chrom=%s, dechrom=%.2f, fit=%.2f" %
                (pop, chorm, dechrom, fit))
    # 保证所有的都为正
    # 将最小的适应度调整到0.000001，防止负数的出现
    fitness = fitness - fitness.min() + 0.000001

    chorms = self.__select_and_crossover(chroms, fitness)  # 得到交叉后的基因
    dechroms = self.__decodeFun(chorms)  # 把交叉后的基因解码
    fig, (axs1, axs2) = plt.subplots(1, 2, figsize=(14, 5))
    axs1.plot(xs, self.fun(xs))
    axs1.plot(population, self.fun(population), 'o')
    axs2.plot(xs, self.fun(xs))
    axs2.plot(dechroms, self.fun(dechroms), 'o')
    plt.show()
    print()