#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <climits>
#include<map>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *playMinMax(int msLeft);
	int getScore(Board board);
	int getPositionScore(int x, int y);
	bool isCorner(int x, int y);
	bool isEdge(int x, int y);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
	Board board;
	Side ourSide;
	Side theirSide;
private:
	int findMinimaxScore(Board myBoard, Move *move, Side side, int level) ;
	int weight[10][10];
	int weightArr[64];
	int alpha;
	int beta;
	long long  get_hash(Board &board);
	map<long long,int> getScoreMap(int level);

	map<long long,int> scores0;
	map<long long,int> scores1;
	map<long long,int> scores2;
	map<long long,int> scores3;
	map<long long,int> scores4;
	map<long long,int> scores5;
	int moveCount;
/*	map<long long,int> scores6;
	map<long long,int> scores7;
	map<long long,int> scores8;
	map<long long,int> scores9;
*/

};

#endif
