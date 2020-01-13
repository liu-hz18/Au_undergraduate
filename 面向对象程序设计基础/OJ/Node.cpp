#include"Node.h"
int main(){
    List<int> listA;
    List<int> listB;
    int num_this;
    while(cin>>num_this){
        listA.push_back(num_this);
    }
    while(cin>>num_this){
        listB.push_back(num_this);
    }
    listA = listA + listB;
    listA.display();
    //del_val = num_this;
    //cout<<list.size()<<endl;
    //list.display();
    //list.del_by_val(del_val);
    //list.del_by_index(del_val);
    //list.insert(12,3);
    //list.set(1,1);
    //list.sort();
    //list.display();
    return 0;
}
