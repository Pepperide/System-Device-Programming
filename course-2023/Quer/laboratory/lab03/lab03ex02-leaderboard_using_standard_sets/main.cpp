#include <iostream>
#include "Leaderboard.h"

int main() {
    Leaderboard l;

    l.addPlayer("Giuseppe",100);
    l.addPlayer("Alessandro",100);
    l.addPlayer("Mario",55);
    l.addPlayer("Luca",104);
    l.addPlayer("Giacomo",99);

    l.removePlayer("Mario");
    l.updateScore("Giuseppe",105);

    l.printTopPlayers(5);

    return 0;
}
