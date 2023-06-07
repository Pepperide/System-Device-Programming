#include <iostream>
int a = 10;
int c = 0;
int main() {
    int& b=a, a;
    int c;
    a=0;
    b++;
    std::cout << b << std::endl;
    return 0;
}
/*
 * I'm assigning to b the reference to a which is global.
 * Then I defined another variable a which is local to the main(). It is not related to the global one. They are different
 * a=0 means that I'm assigning 0 to the LOCAL variable a.
 * b++ increase the value referenced by b which is a variable GLOBALGS
 * */