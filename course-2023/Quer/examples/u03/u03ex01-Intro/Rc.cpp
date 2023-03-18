//
// Created by giuseppe on 15/03/23.
//

#include "Rc.h"

using namespace std;

int Rc::get_code() {
    return code;
}
void Rc::set_code(int a) {
    code = a;
}
int Rc2::get_code(Rc c) {
    return c.code; // To access a private parameter of another class you have to define the class as friend
}