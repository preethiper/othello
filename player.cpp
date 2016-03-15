#include "player.h"
#include <vector>
#include <stdlib.h>
#include <cmath>
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
	if  (side == BLACK) {
		theirSide = WHITE;
	} else {
		theirSide = BLACK;
	}
	moveCount = 1;
    //cerr << "Move Count " << moveCount << endl;
	alpha = INT_MIN;
	beta = INT_MAX;
	weightArr[63] = 5;
	
	weight[0][0]=140;
	weight[0][1]=-20;
	weight[0][2]=20;
	weight[0][3]=5;
	weight[0][4]=5;
	weight[0][5]=20;
	weight[0][6]=-20;
	weight[0][7]=140;

	weight[1][0]=-20;
	weight[1][1]=-40;
	weight[1][2]=-5;
	weight[1][3]=-5;
	weight[1][4]=-5;
	weight[1][5]=-5;
	weight[1][6]=-40;
	weight[1][7]=-20;

	weight[2][0]=20;
	weight[2][1]=-5;
	weight[2][2]=15;
	weight[2][3]=3;
	weight[2][4]=3;
	weight[2][5]=15;
	weight[2][6]=-5;
	weight[2][7]=20;

	weight[3][0]=5;
	weight[3][1]=-5;
	weight[3][2]=3;
	weight[3][3]=3;
	weight[3][4]=3;
	weight[3][5]=3;
	weight[3][6]=-5;
	weight[3][7]=5;
	
	weight[4][0]=5;
	weight[4][1]=-5;
	weight[4][2]=3;
	weight[4][3]=3;
	weight[4][4]=3;
	weight[4][5]=3;
	weight[4][6]=-5;
	weight[4][7]=5;
    
	weight[5][0]=20;
	weight[5][1]=-5;
	weight[5][2]=15;
	weight[5][3]=3;
	weight[5][4]=3;
	weight[5][5]=15;
	weight[5][6]=-5;
	weight[5][7]=20;

	weight[6][0]=-20;
	weight[6][1]=-20;
	weight[6][2]=-5;
	weight[6][3]=-5;
	weight[6][4]=-5;
	weight[6][5]=-5;
	weight[6][6]=-40;
	weight[6][7]=-20;

	weight[7][0]=140;
	weight[7][1]=-20;
	weight[7][2]=20;
	weight[7][3]=5;
	weight[7][4]=5;
	weight[7][5]=20;
	weight[7][6]=-20;
	weight[7][7]=140;

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

bool Player::isCorner(int x, int y) {
	if ((x == 0 && y == 0) || (x == 0 && y == 7) || (x == 7 && y == 0)
													|| (x == 7 && y == 7)) {
		return true;
	}
	return false;
}

int Player::getPositionScore(int x,int y) {
    if  (isCorner(x,y)) {
		return 10;
	}
	if  (isEdge(x,y)) {
		return 5;
	}
	if  ((x == 1 && y == 1) || (x == 1 && y == 6) || (x == 6 && y == 1) || (x == 6 && y == 6)) {
		return -5;
	}	
    if  ((x == 1) || (x== 6) || (y == 1) || (y == 6)) {
		return -1;
	}
	return 1;

}

bool Player::isEdge(int x, int y) {
	if ((x == 0) || (y == 0) || (x == 7) || (y == 7)) {
		return true;
	}
	return false;
}

int Player::getScore(Board board) {
	Side theirSide;
	if  (true) {
		if (ourSide == BLACK) {
			// take care of wipeouts (i.e., if the opponent is wrecking us
            // and we have literally 0 coins, multiply the white count by 1000
            // to minimize the score and make it super negative so the computer
            // has a sense of how screwed we are.
			if  (board.countBlack() == 0) {
				return 1000 * board.countWhite();
			}
			return board.countBlack() - board.countWhite();
		}
		// Same, but if we are WHITE.
		if  (board.countWhite() == 0) {
			return 1000 * board.countBlack();
		}
		return board.countWhite() - board.countBlack();
	}
	int score = 0;
    for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if  (board.get(ourSide, i, j)) {
				score += getPositionScore(i, j);
  			} else if (board.get(theirSide, i, j)) {
				score -= getPositionScore(i, j);
			}
		}
	}
	return score;
}



int Player::findMinimaxScore(Board myBoard, Move* move, Side side, int level) {
	if  ((level == 0) || (alpha > beta)) {
		Board *copy = myBoard.copy();
		if  (level != 0) {
                	//cerr << "Not going down any further "  << endl;
		}
		copy->doMove(move,side);
		int score = getScore(*copy);
		delete copy;
		return score;
	}
	vector<Move *> possibleMoves = myBoard.getPossibleMoves(side);
	int minmaxScore;
	if  (side == theirSide) {
		minmaxScore = INT_MAX;
	} else {
		minmaxScore = INT_MIN ;
	}
	for (unsigned int i=0;i<possibleMoves.size();i++) {
		map<long long,int> scoreMap = getScoreMap(level);
//		cerr << "Here 1" << endl;
		if  (scoreMap.find(get_hash(myBoard)) != scoreMap.end()) {
//			cerr << "Here r" << endl;
			cerr << "Hash hit " << endl;
			return scoreMap[get_hash(myBoard)];
		}
//		cerr << "Here 3" << endl;
	    Board *copy = myBoard.copy();
		int score = findMinimaxScore(*copy,possibleMoves[i], side == BLACK ? WHITE : BLACK, level -1);
		// cerr << "*** Weight *** (" << possibleMoves[i]->x << "," << possibleMoves[i]->y << ")" << weight[possibleMoves[i]->x][possibleMoves[i]->y] << endl;
        if  (side == theirSide) {
			score -= weight[possibleMoves[i]->x][possibleMoves[i]->y];
		} else {
			score += weight[possibleMoves[i]->x][possibleMoves[i]->y];
		}
		if  (side == theirSide) {
			if   (score < minmaxScore) {
				minmaxScore = score;
				beta = score;
			}	
		} else {
			if  (score > minmaxScore) {
				minmaxScore = score;
				alpha = score;
			}
		}
		scoreMap[get_hash(*copy)] = minmaxScore;
		delete copy;
		delete possibleMoves[i];
	}
	
	return minmaxScore;
}

map<long long,int> Player::getScoreMap(int level) {
	return scores0;

	if (level == 0) { 
	//	cerr << "Returning 0 " << endl; 
		return scores0; 
	}
	if (level == 1) { 
	//	cerr << "Returning 0 " << endl; 
		return scores1; 
	}
	if (level == 2) { 
	//	cerr << "Returning 0 " << endl; 
		return scores2; 
	}
	if (level == 3) { 
	//	cerr << "Returning 0 " << endl; 
		return scores3; 
	}
	if (level == 4) { 
	//	cerr << "Returning 0 " << endl; 
		return scores4; 
	}
	if (level == 5) { 
	//	cerr << "Returning 0 " << endl; 
		return scores5; 
	}
	return scores0;
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
    //cerr << "In doMove Move Count " << moveCount << endl;
    if  (opponentsMove != NULL) {
		board.doMove(opponentsMove, theirSide);
    }
    // cerr << "1 In doMove Move Count " << moveCount << endl;
	vector<Move *> possibleMoves;
	
	// Get all possible valid moves
	possibleMoves = board.getPossibleMoves(ourSide);
    // cerr << "2 In doMove Move Count " << moveCount << endl;
	if (possibleMoves.size() == 0) {
		return NULL;
	}

	if  (testingMinimax) {
        return playMinMax(msLeft);
    }
	moveCount++;

	Move * minimaxMove;
	int minimaxScore = INT_MIN;
	alpha = INT_MIN;
	beta = INT_MAX;
    // cerr << "In doMove  1Move Count " << moveCount << endl;
	for (unsigned int i = 0; i < possibleMoves.size(); i++) {
		// look ahead less the further in the game you are or running out of time
		// cerr << " MoveCount " << moveCount << endl;
        int lookAhead = 7 - (moveCount / 10);
		// cerr << "Lookahead " << lookAhead << " MoveCount " << moveCount << endl;
		if  ((lookAhead < 2) || (msLeft != 0 && msLeft < 1000)  ) {
			lookAhead = 2;
		}
		// cerr << "1 Lookahead " << lookAhead << " MoveCount " << moveCount << endl;
		lookAhead = 5;
		int min = findMinimaxScore(board, possibleMoves[i], ourSide,lookAhead);
		min += weight[possibleMoves[i]->x][possibleMoves[i]->y];
        // cerr << "Min Score : " << min << endl;
		if  (min > minimaxScore) {
			minimaxScore = min;
			minimaxMove = possibleMoves[i];
    			// cerr << "Assigning (" << minimaxMove->x << "," << minimaxMove->y << ") Score : " << minimaxScore << endl;
		}
		// delete possibleMoves[i];
	}
    // cerr << "Moving (" << minimaxMove->x << "," << minimaxMove->y << ") Score : " << minimaxScore << endl;
        cerr << "I picked (" << minimaxMove->x << "," << minimaxMove->y << ")" << endl;
	board.doMove(minimaxMove, ourSide);
    return minimaxMove;
}


long long Player::get_hash(Board &b)
{
    long long  board_hash = 0;
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
			int val;	
	    	if  (b.get(ourSide,i,j)) {
		 		val = 1;
			} else if  (b.get(theirSide,i,j)) {
				val = 2;
			} else {
				val = 3;
			}
            board_hash |= val << ((i * 8 + j) *2);
        }
    }
    return board_hash;
}



Move *Player::playMinMax(int msLeft) {
	Side theirSide;
	if (ourSide == BLACK) {
		theirSide = WHITE;
	} else {
		theirSide = BLACK;
	}
    vector<Move *> possibleBoardMoves;
    vector<Move *> possibleOpponentMoves;
    vector<Move *> possibleCounterMoves;
    vector<Move *> bestMoves;

    possibleBoardMoves = board.getPossibleMoves(ourSide);
    if  (possibleBoardMoves.size() == 0) {
		return NULL;
	}
	Move *maxMinMove;
	int maxMinScore = -200;
	for (int i = possibleBoardMoves.size() -1; i > -1; i--) {
		Move *myMove = possibleBoardMoves[i];
	    Board mycopy = *(board.copy());
		mycopy.doMove(myMove,ourSide);
		int minScore = getScore(mycopy);
		// cerr << "Mine (" << myMove->x << "," << myMove->y << ") Score: " << minScore << endl;	
    	possibleOpponentMoves = mycopy.getPossibleMoves(theirSide);
		for (unsigned int j = 0; j < possibleOpponentMoves.size(); j++) {
			Move *theirMove = possibleOpponentMoves[j];
	    	Board theircopy = *(mycopy.copy());
			theircopy.doMove(theirMove,theirSide);
			int score = getScore(theircopy);
			score += getPositionScore(theirMove->x, theirMove->y);
			// cerr << "\t Their(" << theirMove->x << "," << theirMove->y << ") Score: " << score  << endl;	
			if  (score < minScore) {
				minScore = score;
			}
    		possibleCounterMoves = theircopy.getPossibleMoves(ourSide);
			for (unsigned int k = 0; k < possibleCounterMoves.size(); k++) {
				Move *counterMove = possibleCounterMoves[k];
	    		Board countercopy = *(theircopy.copy());
				countercopy.doMove(counterMove,ourSide);
			 	score = getScore(countercopy);
				score += getPositionScore(counterMove->x, counterMove->y);
				// cerr << "\t\tCounter (" << counterMove->x << "," << counterMove->y << ") Score: " << score  << endl;	
				if  (score > minScore) {
					minScore = score;
				}
			}
		}
		if  (minScore > maxMinScore) {
			maxMinScore = minScore;
			maxMinMove = myMove;
		}
		if  (minScore == maxMinScore) {
			if  (isCorner(myMove->x,myMove->y)) {
				maxMinMove = myMove;
			} 
			bestMoves.push_back(myMove);
		}
        // cerr << "Minimum of all possibilities " << minScore << endl;
	}
        // Move *chooseRandom = bestMoves[(rand() % bestMoves.size())];
	board.doMove(maxMinMove,ourSide);
    // cerr << "CHOOOOOSINNNNGG ---- (" << maxMinMove->x << "," << maxMinMove->y << ")" << endl;
	return maxMinMove;
}
