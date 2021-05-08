#include <bits/stdc++.h>
using namespace std;

class Game;
class Board {
public:
	// variable
	Game *_game;
	bool _isPlayerTurn;
	Board *_parent;
	pair<int, int> _to, _from;
	bool _stepWasAJump;
	bool _becameKing;
	pair<unsigned long long int, int> _playerMen, _playerKing;
	pair<unsigned long long int, int> _opponentMen, _opponentKing;


	// functions
	Board(Game *game); 
	Board* deepCopy();
	char at(pair<int, int> cord);

	void insert(pair<unsigned long long int, int> &_presence, pair<int, int> cord);
	bool isPresent(pair<unsigned long long int, int> &_presence, pair<int, int> cord);
	void erase(pair<unsigned long long int, int> &_presence, pair<int, int> cord);
	list<pair<int, int>> cordinates(pair<unsigned long long int, int> &_presence);

	bool opponent(pair<int, int> cord);
	bool opponentMen(pair<int, int> cord);
	bool opponentKing(pair<int, int> cord);

	bool player(pair<int, int> cord);
	bool playerMen(pair<int, int> cord);
	bool playerKing(pair<int, int> cord);
	bool empty(pair<int, int> cord);

	void printBoard();
	void printToFile();
	string convert(pair<int, int> cord);
	bool isEnd();
};