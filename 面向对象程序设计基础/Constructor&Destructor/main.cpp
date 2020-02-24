
#include <iostream>
#include <string>
#include "MyAnswer.h"
using namespace std;

#define Option_A auto testA = f1(move(b));
#define Option_B auto testB = f2(b);
#define Option_C auto testC = f3(move(b));
#define Option_D auto testD = f3(move(b));
#define Option_E auto& testE = f4(f);
#define Option_F auto testF = f5(move(b));

class A {
public:
    string name;
    A(const char* n){
        name = string(n);
        cout << "A constructing..."  << name << endl;
    }
    A(string n){
        name = n;
        cout << "A constructing..." << name << endl;
    }
    A(const A &a){
        name = a.name;
        cout << "A copy constructing..." << name << endl;
    }
    A(A&& a){
        name = a.name;
        cout << "A move constructing..." << name <<endl; 
    }
    ~A(){
        cout << "A destructing..." << name << endl;
    }
};

class B {
private:
    static A data1;
    A data2;
    string name;

public:
    B(const char* n) : data2(n+string(".data2")){
        name = string(n);
        cout << "B constructing..." << name << endl;
    }
    ~B(){
        cout << "B destructing..." <<name << endl;
    }
};

A B::data1("B::data1");

A f1(A b) { //A:5 
    cout << "------after call------" << endl;
    A f = move(b);
    cout << "------before return------" << endl;
    return f;
}

A* f2(A& b) {//B:6
    cout << "------after call------" << endl;
    A* f = &b;
    cout << "------before return------" << endl;
    return f;
}


A f3(A b) {//C:1 //D:3
    cout << "------after call------" << endl;
    static A f("f");
    cout << "------before return------" << endl;
    return f;
}

A& f4(A* b) {//E:2
    cout << "------after call------" << endl;
    A *f = b;
    cout << "------before return------" << endl;
    return *f;
}

A f5(A&& b) {//F:4
    cout << "------after call------" << endl;
    A f = b;
    cout << "------before return------" << endl;
    return f;
}

void work()
{
    cout << "=======entering work=======" << endl;
    A b("b");
    B t("t");
    
    A f[2] = {A("f[0]"), A("f[1]")};

    cout << "------before call------" << endl;
    Answer1 // (1)C
    cout << "------after return------" << endl << endl;
    
    cout << "------before call------" << endl;
    Answer2 //(2)E
    cout << "------after return------" << endl << endl;
    
    cout << "------before call------" << endl;
    Answer3 //(3)D
    cout << "------after return------" << endl << endl;
    
    cout << "------before call------" << endl;
    Answer4 //(4)F
    cout << "------after return------" << endl << endl;
    
    cout << "------before call------" << endl;
    Answer5 //(5)A
    cout << "------after return------" << endl << endl;
    
    cout << "------before call------" << endl;
    Answer6 //(6)B
    cout << "------after return------" << endl << endl;
    
    cout << "=======exiting work=======" << endl;
}

int main() {
    cout << "=======entering main=======" << endl;
    work();
    cout << "=======exiting main=======" << endl;
    return 0;
}
