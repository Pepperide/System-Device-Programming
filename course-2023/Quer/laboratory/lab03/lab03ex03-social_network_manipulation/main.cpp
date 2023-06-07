#include <iostream>
#include <fstream>
#include "main.h"

int main(int argc, char **argv) {
    if(argc != 2){
        cerr << "Error: Wrong number of parameters" <<endl;
        exit(EXIT_FAILURE);
    }
    string filename(argv[1]);

    map<Person,set<Person>> adj = readFile(filename);
    printEnrolledPeople(adj);

    printFriends(adj, "Leopardi_Giacomo");

    bool ok = findConnection(adj, Person("Leopardi_Giacomo"), Person("Rossi_Mario"));
    cout<<"RELATIONSHIP"<<endl;
    cout<<ok<<endl;

    ok = findConnection(adj, Person("Leopardi_Giacomo"), Person("Verdi_Giuseppe"));
    cout<<ok<<endl;
    return 0;
}

map<Person , set<Person> > readFile(string filename){
    // Using C++ IO Library
    map<Person, set<Person> > m;
    ifstream inputFile(filename);
    string s;

    if(!inputFile.is_open()){
        cerr << "Error: Unable to ope the file "<<filename<<endl;
        exit(EXIT_FAILURE);
    }

    while(getline(inputFile, s)){
        int space = s.find(' ');
        Person p1 = Person(s.substr(0,space));
        Person p2 = Person(s.substr(space+1,s.size()-space));

        if(m.find(p1) == m.end()) // p1 does not exist in the map
            m[p1] = set<Person>{};

        if(m.find(p2) == m.end()) // p2 does not exist in the map
            m[p2] = set<Person>{};

        m[p1].insert(p2);
        m[p2].insert(p1);
    }
    return m;
}

void printEnrolledPeople(map<Person , set<Person>> adj) {
    cout<<endl;
    cout<<"ENROLLED PEOPLE"<<endl;
    for(auto it= adj.begin(); it != adj.end(); it++){
        Person p = it->first;
        cout<<p.getName()<<' '<<p.getSurname()<<endl;
    }
}

void printFriends(map< Person, set<Person>> adj, string fullname){
    Person p(fullname);
    set<Person> friends = adj.at(p);
    cout<<endl;
    cout<<"FRIENDS OF: "<< p.getName()<<' '<<p.getSurname()<<endl;
    for(auto it = friends.begin(); it != friends.end(); it++){
        Person s = *it;
        cout << s.getName() <<' '<<s.getSurname()<<endl;
    }
}

bool findConnection(map <Person, set<Person>> adj, Person X, Person Y){
    map<Person, bool> mark;
    for(auto it = adj.begin(); it!=adj.end(); it++){
        mark[it->first]=false;
    }

    return areConnected(X,Y,mark,adj[X],adj);
}

bool areConnected(Person X, Person Y, map<Person, bool> mark, set<Person> nodes, map<Person, set<Person>> adj) {
    bool connected = false;

    if(X==Y){
        connected = true;
    }else{
        if(!mark[X]){
            mark[X]=true;
            for(auto it = nodes.begin(); it != nodes.end(); it++){
                connected = areConnected(*it, Y, mark, adj[*it], adj);
                if(connected) break;
            }
        }
    }
    return connected;
}
