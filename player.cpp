#include "player.h"
#include <vector>
using namespace std;

/* I MADE A CHANGE!! I ADDED A COMMENT. THAT STILL COUNTS AS A CHANGE, RIGHT???
 * :D :D :D :D :D*/

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

	ourSide = side;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

bool Player::isCorner(Move *move) {
	int x = (*move).getX();
	int y = (*move).getY();
	if ((x == 0 && y == 0) || (x == 0 && y == 7) || (x == 7 && y == 0)
													|| (x == 7 && y == 7)) {
		return true;
	}
	return false;
}

bool Player::isEdge(Move *move) {
	int x = (*move).getX();
	int y = (*move).getY();
	if ((x == 0) || (y == 0) || (x == 7) || (y == 7)) {
		return true;
	}
	return false;
}

int Player::getScore(Board board) {
	if (ourSide == BLACK) {
		return board.countBlack() - board.countWhite();
	}
	return board.countWhite() - board.countBlack();
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
	Side opponentSide;
	if (ourSide == BLACK) {
		opponentSide = WHITE;
	} else {
		opponentSide = BLACK;
	}
	board.doMove(opponentsMove, opponentSide);
	vector<Move *> possibleMoves;
	Move *nextMove;
	int maxScore = 0;
	
	// Get all possible valid moves
	// If any of the corners are free, return a corner
	possibleMoves = board.getPossibleMoves(ourSide);
	if (possibleMoves.size() == 0) {
		return NULL;
	}
		
	for (unsigned int i = 0; i < possibleMoves.size(); i++) {
		Move *move = possibleMoves[i];
		
		if (isCorner(move)) {
			nextMove = move;
		} else if (isEdge(move)) {
			nextMove = move;
		} else {
			maxScore = getScore(board);
			Board copy = *(board.copy());
			copy.doMove(move, ourSide);
			int copyScore = getScore(copy);
			if (maxScore < copyScore) {
				maxScore = copyScore;
				nextMove = move;
			}
		}
	}
	board.doMove(nextMove, ourSide);
    return nextMove;
}
