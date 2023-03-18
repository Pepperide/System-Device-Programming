#include <iostream>
#include <vector>
#include "Rc.h"
using namespace std; //You can avoid using std:: since compiler will check the function in the default namespace

void sumExample(){
    int v1, v2;

    std::cout << "Enter two values:";
    std::cin >> v1 >> v2;
    std::cout <<"Sum: " << v1+v2 << std::endl;
}

void reference(){
    int i=42;
    int & ref = i;

    cout<<"i is: "<<i<<" ref is: "<<ref<<endl;
    i=25;
    cout<<"i is: "<<i<<" ref is: "<<ref<<endl; //ref will alway point to i. If i changes also ref changes
}

void casting(){
    int i=42;
    void *p=&i;
    cout<<*static_cast<int*>(p)<<endl;

    char *p2 =reinterpret_cast<char*>(&i);
    cout<<*p2<<endl; //It will print the char value associated to the corresponding int

}

void vectorExample(){
    vector<int> vet = {0,3,4,6,4,2,4,45};
    for(vector<int>::iterator it=vet.begin();it!=vet.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;

    for(auto it:vet){
        cout<<it<<" ";
    }
    cout<<endl;

    for(auto &it:vet){
        // In this case I will change the original value of the vector since I used the reference &
        cout<<++it<<" ";
    }
    cout<<endl;

    for(auto it:vet){
        cout<<it<<" ";
    }
    cout<<endl;
}

void classExample(){
    Rc r;
    Rc2 p;

    r.set_code(15);
    cout<<r.get_code()<<endl;
    cout<<"From the friend class: "<<p.get_code(r)<<endl;
}
int main(int argc, char** argv) {

    // sumExample();
    // reference();
    // casting();
    // vectorExample();

    classExample();

    return 0;
}
