#include <bits/stdc++.h>
using namespace std;

class Board;
class BoardProperties;
class MinimaxHelper;

class Game {
public:
	string _gameType;
	string _player;
	float _time;
	bool _isPlayerBlack;
	bool _protoView;

	Board *_initialBoard;
	BoardProperties *_boardProperties;
	MinimaxHelper *_minimaxHelper;
	Game(string player, int depth, bool randomBest, int heuristic, bool useAlphaBeta, vector<string>& initialBoard);
};