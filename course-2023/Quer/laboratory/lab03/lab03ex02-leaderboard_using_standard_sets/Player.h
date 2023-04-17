//
// Created by pepperide on 17/04/23.
//

#ifndef LAB03EX02_LEADERBOARD_USING_STANDARD_SETS_PLAYER_H
#define LAB03EX02_LEADERBOARD_USING_STANDARD_SETS_PLAYER_H

#include <iostream>

using namespace std;
using std::string;

class Player {
private:
    string name;
    int score;
public:
    Player(string name, int score){
        this->name = name;
        this->score = score;
    }
    string getName();
    int getScore();
    void updateScore(int new_score);
    bool operator<(const Player& other) const;
    bool operator=(const Player& other) const;
};


#endif //LAB03EX02_LEADERBOARD_USING_STANDARD_SETS_PLAYER_H
