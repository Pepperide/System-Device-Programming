#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <unistd.h>

using std::mutex;
using std::thread;
using std::vector;
using std::cout;
using std::endl;

mutex mutex_ta;
mutex mutex_tb;
int n;

void TA(int id){
    sleep(rand()%3);
    mutex_ta.lock();
    cout<<"TA{"<<id<<"}";
    n++;
    mutex_tb.unlock();
}
void TB(int id){
    sleep(rand()%5);
    mutex_tb.lock();
    cout<<"TB{"<<id<<"}";
    n++;
    if(n>=3){
        cout<<endl;
        n=0;
        mutex_ta.unlock();
    }else{
        mutex_tb.unlock();
    }
}

int main(int argc, char **argv) {
    vector<thread> threadPool_ta;
    vector<thread> threadPool_tb;
    int K;
    srand(time(NULL));

    if(argc != 2){
        std::cerr<<"ERROR: Wrong number of parameters!"<<endl;
        exit(0);
    }
    K= atoi(argv[1]);
    for(int i = 0; i<K; i++){
        threadPool_ta.emplace_back([i]{ TA(i); });
    }

    for(int i = 0; i<2*K; i++){
        threadPool_tb.emplace_back([i]{ TB(i); });
    }

    for(auto& t: threadPool_ta)
        t.join();

    for(auto& t: threadPool_tb)
        t.join();

    return 0;
}
