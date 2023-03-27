#include <iostream>
#include <list>

using std::list;
using namespace std;

class Queue{
private:
    list<string> queue={};
public:
    void enqueue(string s){
        queue.push_back(s);
        return;
    }

    string dequeue(){
        string s = queue.front();
        queue.pop_front();
        return s;
    }

    void visit(){
        auto it = queue.begin();
        while(it!=queue.end()){
            cout<<*it<<endl;
            it++;
        }
        return;
    }

    int getSize(){
        return queue.size();
    }

    bool empty(){
        return queue.empty();
    }
};
int main() {
    Queue queue;

    queue.enqueue("Ciao");
    queue.enqueue("Pepperide");
    queue.enqueue("LOL");
    queue.visit();
    queue.dequeue();
    queue.visit();
    cout<<queue.getSize()<<endl;
    cout<<queue.empty()<<endl;
    return 0;
}
