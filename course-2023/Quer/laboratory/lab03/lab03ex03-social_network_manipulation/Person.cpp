//
// Created by pepperide on 05/06/23.
//

#include "Person.h"

Person::Person(std::string fullname) {
    int del = fullname.find('_');
    this->surname = fullname.substr(0, del);
    this->name = fullname.substr(del+1, fullname.size()-del);
}
Person::Person(const Person &p) {
    this->name = p.name;
    this->surname = p.surname;
}

bool Person::operator<(const Person &other) const {
    string other_fullName = other.name+'_'+other.surname;
    string fullname = this->name+'_'+this->surname;
    return fullname.compare(other_fullName) < 0;
}

bool Person::operator!=(const Person &other) const {
    string other_fullName = other.name+'_'+other.surname;
    string fullname = this->name+'_'+this->surname;
    return fullname.compare(other_fullName) != 0;
}
bool Person::operator==(const Person &other) const {
    string other_fullName = other.name+'_'+other.surname;
    string fullname = this->name+'_'+this->surname;
    return fullname.compare(other_fullName) == 0;
}

Person &Person::operator=(const Person &other) {
    name = other.name;
    surname = other.surname;
    return *this;
}

string Person::getName() {
    return this->name;
}
string Person::getSurname() {
    return this->surname;
}