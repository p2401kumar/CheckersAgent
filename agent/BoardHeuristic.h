#include <bits/stdc++.h>
using namespace std;

class Board;
class Game;
class BoardHeuristic {
	Game *_game;
	int _heuristic;
public:
	BoardHeuristic(Game *game, int heuristic);
	int heuristic(Board* board);
};