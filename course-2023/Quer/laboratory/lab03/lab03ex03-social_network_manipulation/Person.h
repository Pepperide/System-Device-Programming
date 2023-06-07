//
// Created by pepperide on 05/06/23.
//

#ifndef LAB03EX03_SOCIAL_NETWORK_MANIPULATION_PERSON_H
#define LAB03EX03_SOCIAL_NETWORK_MANIPULATION_PERSON_H

#include <string>

using std::string;

class Person{
private:
    string name;
    string surname;

public:
    Person(){}; // Default constructor
    Person(string fullname); //Custom constructor
    Person( const Person& p); //Copy constructor
    Person& operator= (const Person& other); //Copy assignment
    bool operator<(const Person& other) const; //less operator for Person
    bool operator!=(const Person& other) const; //less operator for Person
    bool operator==(const Person& other) const;
    string getName();
    string getSurname();
};

#endif //LAB03EX03_SOCIAL_NETWORK_MANIPULATION_PERSON_H
