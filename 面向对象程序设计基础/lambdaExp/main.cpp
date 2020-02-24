
#include <iostream>
#include <vector>
#include <cmath>
#include "myqueriable.h"

using namespace std;

//二维数组的传递,编译器自动捕获长度
template<typename T, size_t M, size_t N>
void test(const T (&arr)[M][N]){
    for(size_t i = 0 ; i < M; i++, putchar(10)){
        for(size_t j = 0; j < N; j++){
            cout<< arr[i][j] << ' ';
        }
    }
}

//一维数组的传递,编译器自动捕获长度
template<typename T, size_t N>
void test(const T (&arr)[N]){
    for(size_t i = 0; i < N; i++){
        cout<< arr[i] << ' ';
    }
    cout<<endl;
}

//对于建立在堆上的数组，编译器无法获取长度，所以传参必须带 维度个size 信息，同时传入指针

int main(){
    int arr[] = {1, 4, 6, 2, 10};//编译器自动推断大小
    auto out = from(arr)
        .where([](int x){return x > 2 && x < 10;})//lambda表达式
        .apply([](int x){return x * 2;})
        .sum();
    cout << out << endl;

    vector<float> vec = {2.0, 3.0, 4.0, 5.0};
    auto it = from(vec)
        .apply([](float x){return sqrt(x);});
    for(auto x: it){
        cout << x << endl;
    }

    int array[][3] = {{1,2,3},{4,5,6}};//只能有一维缺省值
    test(array);

    return 0;
}
