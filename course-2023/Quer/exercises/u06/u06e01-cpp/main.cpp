#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int var = 0;
std::mutex m;
std::condition_variable adder_cv;
std::condition_variable admin_cv;

void admin_fun(){
    std::unique_lock<std::mutex> admin_lock{m};

    var = 10;
    std::cout<<"Variable has been initialized to 10"<<std::endl;

    adder_cv.notify_all(); // Notify all adder threads that the variable has been initialized

    //wait the adder threads
    while(var < 15){
        //If the variable is less than 15 the admin thread will wait on its condition variable waiting for an
        //adder thread that will wake up it
        admin_cv.wait(admin_lock);
        break; //Need to exit from the while loop
    }
    std::cout<<"Final value of var: "<<var<<std::endl;
}

void adder_fun(){
    srand(time(NULL));
    std::unique_lock<std::mutex> adder_lock{m};

    // Wait for global variable var initialization
    while(var == 0){
        // Wait on the condition variable until the admin thread initializes the global variable
        adder_cv.wait(adder_lock);
    }

    // variable has been initialized
    if(var >= 15){
        admin_cv.notify_one(); // Wake up the admin thread
        return;
    }
    else{
        int n = rand() % 6;
        var += n; //Add a value between 0 and 5

        std::cout<<"Added "<<n<<" --> var = "<<var<<std::endl;
        return;
    }
}

int main() {
    std::thread admin{admin_fun};
    std::thread adder1{adder_fun};
    std::thread adder2{adder_fun};
    std::thread adder3{adder_fun};

    adder1.join();
    adder2.join();
    adder3.join();

    //Notify to the admin that all the adder threads are finished. It must be stopped.
    admin_cv.notify_one();
    admin.join();
    return 0;
}
