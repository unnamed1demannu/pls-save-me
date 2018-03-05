#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    playBoard = new Board(); // board that player keeps track of
    playerSide = side; // set side 

    if (side == BLACK)
    {
        opponentSide = WHITE;
    }
    else
    {
        opponentSide = BLACK;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete playBoard;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    playBoard->doMove(opponentsMove, opponentSide);

    vector<Move *> moves; // vector of possible moves at a given board
    Move *bestMove; //move to actually do 
    int maxScore = 0;

    if (!playBoard->hasMoves(playerSide))
    {
        return nullptr;
    }

    for (int i = 0; i < 8; i++) // populate moves vector
    {
        for (int j = 0; j < 8; j++)
        {
            Move * tempMove = new Move(i, j);
            if (playBoard->checkMove(tempMove, playerSide))
            {
                moves.push_back(tempMove);
            }
        }
    }

    // finding the heuretic score
    for (int i = 0; i < moves.size(); i++)
    {
        Board *tempBoard = playBoard->copy(); // new board for each possible move
        tempBoard->doMove(moves[i], playerSide); // do the move
        int score = 0;

        score += tempBoard->count(playerSide) - tempBoard->count(opponentSide);

        /**
        * if moves[i] == corner spot
        *  score += 10
        * if moves[i] == side spot
        *  score += 1
        * if moves[i] == one spot from corner
        *  score -= 10
        * if moves[i] == on a side, next to opposite color
        *  score -= 5
        */

        if (score > maxScore)
        {
            maxScore = score;
            bestMove = moves[i];
        }
    }

    return bestMove;
}
