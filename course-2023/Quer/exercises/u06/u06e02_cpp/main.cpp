#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

std::vector<int> v;
int command = -1;
std::mutex m;
std::mutex rw;
std::condition_variable cv;
bool running = true;

void writer_fun(){
    srand(time(nullptr));
    while(running){
        std::unique_lock<std::mutex> writer_lock{rw};
        v.emplace_back(rand()%10 +1);
        writer_lock.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

}

void ui_fun(){
    int temp;
    while(running){
        std::cout<<"Enter a value (0,1,2,3): ";
        std::cin>>temp;

        //Update the command variable
        std::unique_lock<std::mutex> ui_lock{m};
        if(temp == 0){
            running = false;
        }
        command=temp;
        cv.notify_one(); // Notify the worker that a new command has been received
        ui_lock.unlock();
    }

}

void worker_fun(){

    while(running){
        std::unique_lock<std::mutex> worker_lock{m};

        //Wait for the first command
        while(v.empty() || command==-1){
            cv.wait(worker_lock);
        }

        std::unique_lock<std::mutex> w_lock{rw};
        switch(command){
            case 0:
                break;
            case 1:
                for(auto &it: v)
                    std::cout<<it<<" ";
                std::cout<<std::endl;
                break;
            case 2:
                std::cout<<v.at(v.size()-1)<<std::endl;
                break;
            case 3:
                v.erase(v.begin(),v.end());
                break;
            default:
                std::cout<<"Wrong command"<<std::endl;
                break;
        }
        w_lock.unlock();

        cv.wait(worker_lock);
    }
}

int main() {
    std::thread writer{writer_fun};
    std::thread ui{ui_fun};
    std::thread worker{worker_fun};

    writer.join();
    ui.join();
    worker.join();
    return 0;
}
