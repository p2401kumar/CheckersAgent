#include <bits/stdc++.h>
using namespace std;

class Game;
class Board;
class BoardProperties {
	Game *_game;
public:
	vector<int> _params;
	BoardProperties(Game *game);

	pair<int, int> dir1(pair<int, int> cord);
	pair<int, int> dir2(pair<int, int> cord);
	pair<int, int> dir3(pair<int, int> cord);
	pair<int, int> dir4(pair<int, int> cord);
	pair<int, int> dir(int dir, pair<int, int> cord);

	bool playerJumpPossible(Board *board, pair<int,int> cord);
	list<Board*> playerJumpList(Board *board, pair<int, int> cord);
	
	bool opponentJumpPossible(Board *board, pair<int, int> cord);
	list<Board*> opponentJumpList(Board *board, pair<int, int> cord);

	list<Board*> playerMove(Board *board);
	list<Board*> opponentMove(Board *board);

	list<Board*> getNextMove(Board *board);
};