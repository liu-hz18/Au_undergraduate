
import math
import numpy as np
import matplotlib.pyplot as plt

number = [
4.979,4.980,4.987,4.978,4.978,4.977
]

x = [1.96,3.92,5.88,7.84,9.8,11.76,13.72,15.68,17.64,19.6]
y = [0.531,
0.825,
1.062,
1.321,
1.59,
1.881,
2.115,
2.41,
2.63,
2.935
]

def aver_sigma(numbers):
	Sigma = 0
	sigma = 0
	aver = 0
	summary = 0
	for i in numbers:
		summary += i
	aver = summary / len(numbers)
	for i in numbers:
		Sigma += (i - aver)**2

	Sigma /= (len(numbers) - 1)
	sigma = math.sqrt(Sigma)
	aver_sig = sigma / math.sqrt(len(numbers))
	print("\n期望: " + str(aver))
	print("方差(除以n - 1): " + str(Sigma))
	print("标准偏差(不是标准差): " + str(sigma))
	print("平均值的标准偏差：S_\\overline_x = " + str(aver_sig))


def huigui(list_x, list_y):
    if (len(list_x) != len(list_y)) or (len(list_x) == 0):
        return
    sum_x = 0
    sum_y = 0
    sum_xy = 0
    sum_x2 = 0
    for x in list_x:
        sum_x += x
        sum_x2 += x*x;
    aver_x = sum_x / len(list_x)
    for y in list_y:
        sum_y += y
    aver_y = sum_y / len(list_y)
    for i in range(len(list_x)):
        sum_xy += list_x[i]*list_y[i]

    a = (sum_x*sum_y - len(list_x)*sum_xy) / (sum_x*sum_x - len(list_x)*sum_x2)
    b = aver_y - a * aver_x

    print("\ny = " + str(a) + "x+ " + str(b))

    sum_delta_x = 0
    sum_delta_y = 0
    sum_delta_xy = 0
    for i in range(len(list_x)):
        sum_delta_x += (list_x[i] - aver_x)**2
        sum_delta_y += (list_y[i] - aver_y)**2
        sum_delta_xy += (list_x[i] - aver_x)*(list_y[i] - aver_y)
    r = sum_delta_xy / (math.sqrt(sum_delta_x) * math.sqrt(sum_delta_y))
    #print(sum_delta_x, sum_delta_y)
    print("r = " + str(r))

    # 一次曲线拟合
    x = np.array(list_x)
    y = np.array(list_y)
    f1 = np.polyfit(x, y, 1)
    new_x = np.arange(min(x), max(x), 0.1)
    yvals = np.polyval(f1, x)#拟合y值
    y_curve = np.polyval(f1, new_x)
    plot1 = plt.plot(x, y, 's', label='original values')
    plot3 = plt.plot(x, yvals, 's', label='predicted values')
    plot2 = plt.plot(new_x, y_curve, 'r', label='polyfit function')
    plt.text(1.7, 1.8, "r="+str(r)[:6])
    plt.text(1.7, 2.0, "y="+str(a)[:5]+"x+"+str(b)[:5])
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend(loc=4)#指定legend的位置右下角
    plt.title('polyfitting')
    plt.show()




#请在此输入关联矩阵
matrix = [ [367, 342, 266, 329],
		   [56, 40, 20, 16],
		 ]


def getkafang(matrix):
	s = 0
	rowsum = []#对行求和
	coloumsum = []#对列求和
	for row in matrix:
		s0 = 0
		for coloum in row:
			s += coloum
			s0 += coloum
		rowsum.append(s0)

	print('总和: ' + str(s))
	print('行和: ' + str(rowsum))
	row = len(rowsum)
	coloum = len(matrix[0])
	for i in range(coloum):
		s1 = 0
		for j in range(row):
			s1 += matrix[j][i]
		coloumsum.append(s1)
	print('列和: ' + str(coloumsum))
	print('自由度: ' + str((row - 1) * (coloum - 1)))
	coloum = len(coloumsum)
	kafang = 0.0
	for i in range(row):
		for j in range(coloum):
			kafang += (s * matrix[i][j] - rowsum[i] * coloumsum[j])**2 / (s * rowsum[i] * coloumsum[j])
	print('卡方: ' + str(kafang))
	
	phi = math.sqrt(kafang / s)
	print('phi系数: ' + str(phi))
	
	CramerV = math.sqrt(kafang / (s * (min(row, coloum) - 1)))
	print('CramerV系数: ' + str(CramerV))
	
	leilian = math.sqrt(kafang / (kafang + s))
	print('列联系数: '+str(leilian))
	return kafang



if __name__ == '__main__':
    huigui(x, y)
	#aver_sigma(number)
	#getkafang(matrix)


