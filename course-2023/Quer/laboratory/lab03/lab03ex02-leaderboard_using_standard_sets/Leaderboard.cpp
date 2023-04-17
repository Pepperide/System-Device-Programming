//
// Created by pepperide on 17/04/23.
//

#include <algorithm>
#include "Leaderboard.h"

void Leaderboard::addPlayer(const std::string &name, int score) {
//    players.insert(Player(name,score));
    players.emplace(name,score);
}

void Leaderboard::removePlayer(const std::string &name) {
    auto pred = [name](Player p){ return p.getName().compare(name);};
    players.erase(std::remove_if(players.begin(),players.end(),pred));
}

void Leaderboard::updateScore(const std::string &name, int newScore) {
    this->removePlayer(name);
    this->addPlayer(name,newScore);
}

void Leaderboard::printTopPlayers(int n) {
    int i=0;
    for(auto it = players.rbegin(); it!=players.rend() && i<n;it++,i++){
        Player p = *it;
        cout<<p.getName()<<" "<<p.getScore()<<endl;
    }
}