//
// Created by pepperide on 17/04/23.
//

#include "Sequential_containers.h"

using namespace std;

void Queue::add_back(string s) {
    queue.push_back(s);
    return;
}

string Queue::remove_back() {
    string s = queue.front();
    queue.pop_front();
    return s;
}

void Queue::visit() {
    auto it = queue.begin();
    while(it!=queue.end()){
        cout<<*it<<endl;
        it++;
    }
    return;
}

int Queue::getSize() {
    return queue.size();
}

bool Queue::empty() {
    return queue.empty();
}

void Stack::add_back(int value) {
    v.push_back(value);
    return;
}

int Stack::remove_back() {
    int value = v[v.size() - 1];
    v.pop_back();
    return value;
};

void Stack::visit() {
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

int Stack::getSize()  {
    return v.size();
}

bool Stack::empty() {
    return v.empty();
}
