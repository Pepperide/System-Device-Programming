//
// Created by pepperide on 17/04/23.
//

#ifndef LAB03EX02_LEADERBOARD_USING_STANDARD_SETS_LEADERBOARD_H
#define LAB03EX02_LEADERBOARD_USING_STANDARD_SETS_LEADERBOARD_H

#include <iostream>
#include <set>
#include "Player.h"

class Leaderboard {
private:
    set<Player> players;
public:
    void addPlayer(const std::string& name, int score);
    void removePlayer(const std::string& name);
    void updateScore(const std::string& name, int newScore);
    void printTopPlayers(int n);
};


#endif //LAB03EX02_LEADERBOARD_USING_STANDARD_SETS_LEADERBOARD_H
