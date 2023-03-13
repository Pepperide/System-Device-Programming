#include <iostream>
using namespace std; //You can avoid using std:: since compiler will check the function in the default namespace

int main(int argc, char** argv) {
    int v1, v2;

    std::cout << "Enter two values:";
    std::cin >> v1 >> v2;
    std::cout <<"Sum: " << v1+v2 << std::endl; //
    return 0;
}
