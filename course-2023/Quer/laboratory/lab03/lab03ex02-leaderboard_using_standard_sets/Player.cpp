//
// Created by pepperide on 17/04/23.
//

#include "Player.h"
#include <string.h>
string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

void Player::updateScore(int new_score) {
    score = new_score;
}

bool Player::operator<(const Player &other) const {
    if(score==other.score)
        return name.compare(other.name)<0?false:true;
    else
        return score<other.score;
}

bool Player::operator=(const Player &other) const {
    return name.compare(other.name);
}