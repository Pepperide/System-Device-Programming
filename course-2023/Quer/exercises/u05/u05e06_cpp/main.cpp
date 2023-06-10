#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#define N 10

int best_rank = -1;
int best_id = -1;
int n_votes = 0;
std::mutex m;

void vote(int id, int rank){
    bool voted = false;
    while(n_votes < N){
        if(!voted){
            m.lock();
            if(rank > best_rank) {
                best_rank = rank;
                best_id = id;
            }
            voted = true;
            n_votes++;
            m.unlock();
        }
    }
    if(best_id == id){
        std::cout<<"Im the leader with id "<<id<<" and rank "<<rank<<std::endl;
    }
}

int main() {
    std::vector<std::thread> thread_pool;

    for(int i=0; i<N;i++){
        srand(i);
        thread_pool.emplace_back(vote, i, rand()%10);
    }

    for(auto &it: thread_pool)
        it.join();

    return 0;
}
