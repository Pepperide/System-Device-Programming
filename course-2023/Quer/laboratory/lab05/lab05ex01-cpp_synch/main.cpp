#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;

int main(int argc, char **argv) {
    int parking_size;
    int simulation_time;
    int parking = 0;

    srand(time(NULL));

    if(argc!=3){
        std::cerr<<"Error! Wrong number of parameters!\n";
        exit(1);
    }
    parking_size=atoi(argv[1]);
    simulation_time=atoi(argv[2]);

    std::thread t1 ([&parking,simulation_time, parking_size]{
        // Every [1,3] seconds a car enter to the parking
        int time_passed = 0;
        while(simulation_time > time_passed){
            m.lock();
            if(parking < parking_size){
                parking++;
                std::cout<<"A car is arrived."<<std::endl;
                std::cout<<"Park size: "<< parking <<"/"<<parking_size<<std::endl<<std::endl;
            }else{
                std::cout<<"The parking is full. The car will search for another parking"<<std::endl;
                std::cout<<"Park size: "<< parking <<"/"<<parking_size<<std::endl<<std::endl;
            }
            m.unlock();

            int wait_for = rand()%3 + 1; // A car arrives every [1,3] seconds
            std::this_thread::sleep_for (std::chrono::seconds(wait_for));
            time_passed += wait_for;

        }
    });

    std::thread t2([&parking,simulation_time, parking_size]{
        // Every [4,7] seconds a car leaves the parking
        int time_passed = 0;
        while(simulation_time > time_passed){
            m.lock();
            if(parking > 0){
                parking --; // A car leaves the parking
                std::cout<<"A car leaves the parking."<<std::endl;
                std::cout<<"Park size: "<< parking <<"/"<<parking_size<<std::endl<<std::endl;
            }else{
                std::cout<<"The parking is empty. No cars are present"<<std::endl;
                std::cout<<"Park size: "<< parking <<"/"<<parking_size<<std::endl<<std::endl;
            }
            m.unlock();

            int wait_for = rand()%4 + 4; // A car arrives every [1,3] seconds
            std::this_thread::sleep_for (std::chrono::seconds(wait_for));
            time_passed += wait_for;
        }
    });

    t1.join();
    t2.join();
    return 0;
}
