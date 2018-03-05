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

    //std::cerr << bestMove->getX() << ", " << bestMove->getY() << std::endl;

    // finding the heuretic score
    for (int i = 0; i < moves.size(); i++)
    {
        Board *tempBoard = playBoard->copy(); // new board for each possible move
        tempBoard->doMove(moves[i], playerSide); // do the move
        int score = 0;

        score += tempBoard->count(playerSide) - tempBoard->count(opponentSide);

        // for ease of writing
        int x = moves[i]->getX();
        int y = moves[i]->getY();

        // corner position weighed extremely heavily
        if ((x == 0 || x == 7) && (y == 0 || y == 7)) 
        {
            score += 50;
        }

        // side position weighed somewhat
        if (x == 0 || x == 7 || y == 0 || y == 7)
        {
            score += 10;
        }

        // one spot from corner is very bad
        
        if ((x == 0 && (y == 1 || y == 6)) || (x == 7 && (y == 1 || y == 6)) ||
            (y == 0 && (x == 1 || x == 6)) || (y == 7 && (x == 1 || x == 6)) ||
            (x == 1 && y == 1) || (x == 1 && y == 6) || (x == 6 && y == 1) || (x == 6 && y == 6))
        {
            score -= 10;
        }

        //one spot from edge is bad
        if (x == 1 || x == 6 || y == 1 || y == 6)
        {
            score -= 5;
        }

        // being on the side next to an opposite color is bad

        // since it's possible that every single move results in a negative result
        if (i == 0 || score > maxScore)
        {
            maxScore = score;
            bestMove = moves[i];
        }
    }
    //std::cerr << bestMove->getX() << ", " << bestMove->getY() << std::endl;

    playBoard->doMove(bestMove, playerSide);

    return bestMove;
}
