
#pragma once
#include "util.h"
#include <stdio.h>

bool Judge(double x){
	return x > -1e-7 && x < 1e-7;
}

template<typename T>
class Matrix{
	int n, m;
	T** mat;

public:
	//(N, M)矩阵
	Matrix(int _n, int _m):n(_n+1), m(_m+1){
		assert(1 < n && 1 < m);
		mat = new T*[n];
		for(int i = 1; i < n; i++){
			mat[i] = new T[m];
			for(int j = 1; j < m; j++)mat[i][j] = 0;
		}
	}
	//注意传入的矩阵序从1开始
	Matrix(int _n, int _m, T** ma):n(_n+1), m(_m+1){
		assert(1 < n && 1 < m);
		mat = new T*[n];
		for(int i = 1; i < n; i++){
			mat[i] = new T[m];
			for(int j = 1; j < m; j++)mat[i][j] = ma[i][j];
		}
	}
	~Matrix(){
		for(int i = 1; i < n; i++)delete[] mat[i];
		delete[] mat;
	}
	void set(int i, int j, T value){
		assert(1 <= i && 1 <= j && i < n && j < m);
		mat[i][j] = value;
	}
	T get(int i, int j)const{
		assert(1 <= i && 1 <= j && i < n && j < m);
		return mat[i][j];
	}
	T det(){
		assert(n == m);
		//创建副本
		double** a = new double*[n];
		for(int i = 1; i < n; i++){
			a[i] = new double[n];
			for(int j = 1; j < n; j++)a[i][j] = double(mat[i][j]);
		}
		//高斯消元计算行列式, O(n^3)
		double ans = 1; int i, j, k;
		for(i = 1; i < n; i++){
			for(j = i; Judge(a[j][i]) && j < n; j++);
			if(j >= n){
				puts("empty");return 0;
			}
			if(i ^ j)
				for(ans = -ans,k = i; k < n; k++)
					util::swap<double>(a[i][k], a[j][k]);
			for(j = i + 1; j < n;j ++){
				if(!Judge(a[j][i])){
					long double tmp = a[j][i] / a[i][i];
					for(k = i; k < n; k++) a[j][k] -= tmp * a[i][k];
				}
			}
		}
		for(i = 1;i < n; i++)ans *= a[i][i];
		for(int i = 1; i < n; i++)delete[] a[i];
		delete[] a;
		return T(ans);
	}
	void print(){
		for(int i = 1; i < n; i++, putchar(10)){
			for(int j = 1; j < n; j++){
				printf("%5.3f ", double(mat[i][j]));
			}
		}
	}

};
