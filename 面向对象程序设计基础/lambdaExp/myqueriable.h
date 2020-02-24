
#pragma once
#include <vector>
#include <iostream>
#include <functional>//for std::function
using namespace std;

template<typename T>
class MyQueriable{
    vector<T> v;

public:
    template<size_t N>
    explicit MyQueriable(const T (&arr)[N]){
        for(size_t i = 0; i < N; i ++){
            v.push_back(arr[i]);
        }
    }
    explicit MyQueriable(vector<T> vec): v(vec){}
    ~MyQueriable(){}
    
    auto begin(){//c++14不需要decltype(v.begin())
        return v.begin();
    }
    auto end(){
        return v.end();
    }
    
    //使用模板实现lambda表达式的获取
    template<typename F>
    MyQueriable<T> where(F const& f){//参数是lamda表达式或者模板函数
        vector<T> vec;
        for(auto& item : v){
            if(f(item))vec.push_back(item);
        }
        return MyQueriable<T>(vec);
    }

    template<typename F>
    MyQueriable<T> apply(F const& f){
        vector<T> vec;
        for(auto& item : v){
            vec.push_back(f(item));
        }
        return MyQueriable<T>(vec);
    }
    
    /*
    //使用std::function实现lambda表达式的获取(#include <functional>)
    MyQueriable<T> where(std::function<bool (T)> const& f){//bool是返回值类型，T是参数类型
        vector<T> vec;
        for(auto& item : v){
            if(f(item))vec.push_back(item);
        }
        return MyQueriable<T>(vec);
    }
    MyQueriable<T> apply(std::function<T (T)> const& f){//T是返回值类型，T是参数类型
        vector<T> vec;
        for(auto& item : v){
            vec.push_back(f(item));
        }
        return MyQueriable<T>(vec);
    }
    */
    T sum(){
        T s = *v.begin();//使用此方法更适合泛型编程，而不是从0开始
        for(auto& item : v){
            s += item;
        }
        s -= *v.begin();
        return s;
    }
};

//const T(&)[N]作为参数，传递的参数能够保留原有数组的长度信息
//使用参数T* arr不仅会让调用者不明白是1.传数组(指针) 还是 2.传递一个int变量的地址
//使用T arr[]可以避免上述问题
//但是数组的大小依然不知道
//我们可以考虑使用一个引用形参(int arr[], int n)实现传数组
//但是推断数组大小可以交给编译器，使用非类型模板参数<size_t N>
template<typename T, size_t N>
MyQueriable<T> from(const T (&arr)[N]){
    return MyQueriable<T>(arr);
}

template<typename T>
MyQueriable<T> from(vector<T> vec){
    return MyQueriable<T>(vec);
}
