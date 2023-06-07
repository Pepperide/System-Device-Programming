//
// Created by pepperide on 05/06/23.
//

#ifndef LAB03EX03_SOCIAL_NETWORK_MANIPULATION_MAIN_H
#define LAB03EX03_SOCIAL_NETWORK_MANIPULATION_MAIN_H

#include <string>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include "Person.h"

using std::string;
using std::map;
using std::set;
using std::cerr;
using std::ifstream;
using std::endl;
using std::cout;
using std::vector;
using std::make_pair;
using std::iterator;

map<Person, set<Person> > readFile(string Filename);
void printEnrolledPeople(map<Person , set<Person>> adj);
void printFriends(map< Person, set<Person>> adj, string fullname);
bool areConnected(Person X, Person Y, map<Person, bool> mark, set<Person> nodes, map<Person, set<Person>> adj);
bool findConnection(map <Person, set<Person>> adj, Person X, Person Y);
#endif //LAB03EX03_SOCIAL_NETWORK_MANIPULATION_MAIN_H
