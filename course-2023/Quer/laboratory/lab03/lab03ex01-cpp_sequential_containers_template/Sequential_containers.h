//
// Created by pepperide on 17/04/23.
//

#ifndef LAB03EX01_CPP_SEQUENTIAL_CONTAINERS_TEMPLATE_SEQUENTIAL_CONTAINERS_H
#define LAB03EX01_CPP_SEQUENTIAL_CONTAINERS_TEMPLATE_SEQUENTIAL_CONTAINERS_H

#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::string;
using std::vector;

class Queue{
public:
    void add_back(string s);
    string remove_back();
    void visit();
    int getSize();
    bool empty();
private:
    list<string> queue={};
};

class Stack {
private:
    vector<int> v;
public:
    void add_back(int value);
    int remove_back();
    void visit();
    int getSize();
    bool empty();
};

template<typename T>
int getSize(T& cont){
    return cont.getSize();
}

template<typename T>
bool empty(T& cont){
    return cont.empty();
}

template<typename T>
void visit(T& cont){
    cont.visit();
}

template<typename T, typename Z>
void add_back(T& cont, const Z& value){
    cont.add_back(value);
}

template<typename T, typename R>
R remove_back(T& cont){
    return cont.remove_back();
}

#endif //LAB03EX01_CPP_SEQUENTIAL_CONTAINERS_TEMPLATE_SEQUENTIAL_CONTAINERS_H
