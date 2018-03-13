#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    vector<int> alphabeta(Board *curBoard, int depth, int alpha, int beta, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *playBoard;
    Side opponentSide;
    Side playerSide;
};

#endif
