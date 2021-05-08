#include <bits/stdc++.h>
#include "BoardHeuristic.h"
using namespace std;

class Game;
class MinimaxHelper {
	int _depth;
	int _heuristic;
	Game *_game;
	bool _UseAlphaBeta;
public:
	BoardHeuristic *_boardHeuristic;

	MinimaxHelper(Game *game, int depth, bool useAlphaBeta, int heuristic);
	Board* findbestBoard(Board* board);
	int minimax(Board* board, int depth, int alpha, int beta, Board* bb, list<Board*> ll);
};