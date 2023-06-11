#include <iostream>
#include <future>

int take(){
    int num;
    std::cout<<"Write a number: ";
    std::cin>>num;
    return num;
}
bool check(int num){
    if(num == 0 || num == 1){
        return false;
    }

    for(int i=2;i<num/2;i++){
        if(num%i == 0)
            return false;
    }

    return true;
}
void give(int num, bool isPrime){
    if(isPrime)
        std::cout<<"The number "<<num<<" is a prime number"<<std::endl;
    else
        std::cout<<"The number "<<num<<" is not a prime number"<<std::endl;
}
int main() {
    auto num_promise = std::promise<int>();
    auto num_future = num_promise.get_future();

    auto check_promise = std::promise<bool>();
    auto check_future = check_promise.get_future();

    auto take_t = std::thread([&num_promise]{ num_promise.set_value(take()); });
    int num = num_future.get();

    auto check_t = std::thread( [&check_promise, num]{ check_promise.set_value(check(num));} );
    bool isPrime = check_future.get();

    auto give_t = std::thread( [isPrime, num]{ give(num, isPrime);} );

    take_t.join();
    check_t.join();
    give_t.join();

    return 0;
}
