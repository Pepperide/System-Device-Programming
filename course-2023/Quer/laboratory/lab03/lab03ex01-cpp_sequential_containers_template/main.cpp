#include <iostream>
#include "Sequential_containers.h"

using namespace std;

int main() {
    Queue q;
    Stack s;

    add_back(q,"Ciao");
    add_back(q,"Giuseppe");
    add_back(s,1);
    add_back(s,3);
    add_back(s,2);

    cout<<getSize(q)<<endl;
    cout<<getSize(s)<<endl;
    cout<<endl;

    cout<<remove_back<Queue, string>(q)<<endl;
    cout<<remove_back<Stack, int>(s)<<endl;
    cout<<endl;

    visit(q);
    visit(s);
    cout<<endl;

    cout<<empty(q)<<endl;
    cout<<empty(s)<<endl;

    return 0;
}
