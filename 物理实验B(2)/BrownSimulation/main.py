# 布朗运动批量测试
# CopyRight @ LiuHongzun at THU.CST 2020.5
# 文件结构:
# |--main.py
# |--brown.cpp
# |--results/...
import os
import matplotlib.pyplot as plt
import time
import numpy as np
import math
from scipy import optimize, stats
from scipy.stats import norm  # 用于拟合正态分布曲线
import seaborn as sns

T = 293.0  # K
gamma = 3.0 * math.pi * 0.1  # 3pi * 0.0001 Pa.s * 10^-6 m = 3pi*10^-10
R = 8.314  # J.mol.K^-1
tau = 30


def compile():
    if 0 != os.system('g++ brown.cpp -o brown.exe'):
        print('compile failed!')


def run(times):
    for t in range(times):
        if 0 != os.system('brown > results/out_%d.txt' % (t)):
            print('run batch %d failed' % (t))
        print('running program id:%d' % t, end='\r')
        time.sleep(2)


def linear(x, A):
    return A * x


def static_1(n):
    mat = np.zeros((n, 60))
    for t in range(n):
        with open('results/out_%d.txt' % (t), 'r', errors='ignore') as f:
            for i, line in enumerate(f.readlines()[2:]):
                mat[t][i] = float(line.strip().split()[1])
    array = np.mean(mat**2, axis=0)
    mean_array = np.arange(0, 1800, 30)
    # print(mean_array)
    A = optimize.curve_fit(linear, mean_array, array)[0][0]
    D = A / 2
    k_b = gamma * D / T
    N_a = R / k_b / 100.0
    print('A', A, 'D', D, 'k_b', k_b, 'NA', N_a)
    plt.figure()
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文标签
    plt.rcParams['axes.unicode_minus'] = False   # 这两行需要手动设置
    plt.scatter(mean_array, array, s=20)
    pred = A * mean_array
    plt.plot(mean_array, pred, color='red')
    plt.legend(['y = {:.4f}t'.format(A)], loc='lower right')
    plt.title('微粒位移平均平方偏差 (N=%d)' % (n))
    plt.savefig('curve_%d.pdf' % (n), dpi=300)


def plot_distribution(distribution, n):
    sns.set_style('white')
    plt.figure()
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文标签
    plt.rcParams['axes.unicode_minus'] = False   # 这两行需要手动设置
    plt.grid(True)
    sns.distplot(distribution, fit=norm, color='red')
    (mu, sigma) = norm.fit(distribution)
    plt.legend(['Gaussian: $\mu=$ {:.2f}, $\sigma=$ {:.2f}'. \
               format(mu, sigma)], loc='upper right')
    plt.title('△x分布拟合图 (N=%d)' % n)
    plt.xlabel('△x (um)')
    plt.savefig('dis_%d.pdf' % (n), dpi=300)


def static_2(n):
    mat = np.zeros((n, 60))
    for t in range(n):
        with open('results/out_%d.txt' % (t), 'r', errors='ignore') as f:
            for i, line in enumerate(f.readlines()[2:]):
                mat[t][i] = float(line.strip().split()[2])
    distribution = mat.flatten()
    plot_distribution(distribution, n)
    array = np.mean(mat**2, axis=1)
    delta_x_square = np.mean(array)  # 10^-12 m
    D = delta_x_square / (2*tau)  # 10^23
    k_b = gamma * D / T
    N_a = R / k_b
    print('delta_x^2', delta_x_square, 'D', D, 'k_b', k_b, 'N_A:', N_a/100)
    mean_array = np.arange(0, n, 1)
    plt.figure()
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文标签
    plt.rcParams['axes.unicode_minus'] = False   # 这两行需要手动设置
    plt.title('dt内微粒位移平方平均值 (N=%d)' % (n))
    plt.xlabel('N')
    plt.ylabel('△x (um)')
    plt.scatter(mean_array, array, s=10)
    # print(mean_array, array)
    plt.savefig('curve2_%d.pdf' % (n), dpi=300)


def plot():
    # read x, y
    x, y = [], []
    with open('results/out_0.txt', 'r', errors='ignore') as f:
        for line in f.readlines()[1:]:
            x.append(float(line.strip().split()[1]))
    with open('results/out_500.txt', 'r', errors='ignore') as f:
        for line in f.readlines()[1:]:
            y.append(float(line.strip().split()[1]))
    # print(x, y)
    plt.figure()
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文标签
    plt.rcParams['axes.unicode_minus'] = False   # 这两行需要手动设置
    plt.title(r'布朗运动轨迹')
    plt.xlabel('x (um)')
    plt.ylabel('y (um)')
    plt.plot(x, y, color='red')
    plt.scatter(x, y, s=10)
    plt.savefig('plot_brown.pdf', dpi=300)


def main():
    os.makedirs('results', exist_ok=True)
    t = 10
    #compile()
    #run(times=t)
    plot()
    static_1(n=t)
    static_2(n=t)


if __name__ == '__main__':
    main()
