#include <iostream>
#include <vector>

using namespace std;
using std::vector;

class Stack{
private:
    vector <int> v;

public:
    void push(int value){
        v.push_back(value);
        return;
    }

    int pop(){
        int value = v[v.size()-1];
        v.pop_back();
        return value;
    };

    void visit(){
        for(int i=0;i<v.size();i++)
            cout<<v[i]<<" ";
        cout<<endl;
    }

    int getSize(){
        return v.size();
    }

    bool empty(){
        return v.empty();
    }
};

int main() {
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout<<stack.getSize()<<endl;

    stack.visit();
    stack.pop();
    stack.visit();
    cout<<stack.empty()<<endl;
    return 0;
}
