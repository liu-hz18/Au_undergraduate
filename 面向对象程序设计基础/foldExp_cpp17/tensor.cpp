
#include <iostream>
#include <assert.h>
using namespace std;

template<class T, size_t ...Ns>
class VectorDelegate;

template<class T, size_t N>
class VectorDelegate<T, N>{
    T* data;
public:
    VectorDelegate(T* d): data(d){}
    VectorDelegate(){}
    constexpr T& operator[](const size_t idx){
        assert(idx < N);
        return data[idx];
    }
    constexpr void size()const {
        cout << ", " << N << "])" << endl;
    }
    constexpr void print(){
        cout << "[" << data[0];
        for(size_t i = 1; i < N; i++){
            cout << ", " << data[i];
        }
        cout << "]";
    }
};

template<class T, size_t N, size_t... Ns>
class VectorDelegate<T, N, Ns...>{
    T* data;
    static constexpr size_t total = (1 * ... * Ns);
    
public:
    VectorDelegate(T* d): data(d){}
    VectorDelegate(){}
    constexpr auto operator[](const size_t idx){
        assert(idx < N);
        return VectorDelegate<T, Ns...>(data + idx * total);
    }
    constexpr void size()const {
        cout << ", " << N;
        VectorDelegate<T, Ns...>().size();
    }
    constexpr void print(){
        cout << "[";
        VectorDelegate<T, Ns...>(data).print();
        for(size_t i = 1; i < N; i++){
            cout << ", ";
            VectorDelegate<T, Ns...>(data + i * total).print();
        }
        cout << "]";
    }
};

template<class T, size_t N, size_t... Ns>
class Tensor{
    T data[(N * ... * Ns)] = {0};//数组扁平化
    static constexpr size_t total = (1 * ... * Ns);

public:
    constexpr T* getData(){return data;}
    constexpr auto operator[](const size_t idx){
        assert(idx < N);
        return VectorDelegate<T, Ns...>(data + idx * total);
    }
    constexpr void size()const {
        cout << "tensor([" << N ;
        VectorDelegate<T, Ns...>().size();
    }
    constexpr void print(){
        cout << "[";
        VectorDelegate<T, Ns...>(data).print();
        for(size_t i = 1; i < N; i++){
            cout << ", ";
            VectorDelegate<T, Ns...>(data + i * total).print();
        }
        cout << "]" << endl;
    }
    constexpr void add(const Tensor& t){
        for(size_t i = 0; i < (N * ... * Ns); i++){
            data[i] += t.data[i];
        }
    }
};

int main(){
    Tensor<int, 4, 5, 6> mytensor;
    Tensor<double, 4, 4, 4, 4> tetradic;
    Tensor<int, 4, 5, 6> atensor;

    mytensor[0][0][0] = 12;
    cout << mytensor[0][0][0] << endl;
    
    tetradic[1][1][1][1] = 3.14;
    cout << tetradic[1][1][1][1] << endl;
    
    tetradic.size();
    mytensor.size();

    mytensor.print();
    tetradic.print();

    atensor[0][0][0] = 10;
    mytensor.add(atensor);
    mytensor.print();
    atensor.print();

    return 0;
}
