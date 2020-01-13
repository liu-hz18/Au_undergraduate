
import numpy as np
from sklearn.decomposition import PCA
from matplotlib import pyplot as plt
from sklearn.datasets import load_digits
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn import datasets

X = np.array([[-1, -1, 1], [-2, -1, 0], [-3, -2, 1], [1, 1, 0], [2, 1, 1], [3, 2, 0]])
pca = PCA(n_components=2)
newX = pca.fit_transform(X)
print(X)
print(newX)
print(pca.explained_variance_ratio_)

iris = datasets.load_iris()
x = iris.data
y = iris.target
print(y)
X_pca = pca.fit_transform(x)
color = ['red', 'green', 'blue']
print(x)
print(X_pca)

for i, targetname in enumerate(iris.target_names):
    plt.scatter(X_pca[y == i, 0], X_pca[y == i, 1], label=targetname, color=color[i])

print(X_pca[y==0])# 列表生成式，表示y==i的对应坐标。等价于X_pca[y.index(yi) for yi in y if yi == 0]

'''
fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(1, 1, 1)

for point in newX:
    ax.scatter(point[0], point[1])

ax.grid()
'''
plt.legend()
plt.title('PCA of IRIS dataset')
plt.show()
