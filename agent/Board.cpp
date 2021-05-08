#include "Board.h"
#include "Game.h"

#define GREEN   "\033[32m"      /* Green */
#define WHITE   "\033[37m"      /* White */


Board::Board(Game *game) {
	_game = game;
	_parent = nullptr;
	_isPlayerTurn = false;

	_stepWasAJump = false;
	_becameKing = false;
	_to = _from = { -1, -1 };
	_playerMen = _playerKing = _opponentMen = _opponentKing = { 0LL, 0 };
}

Board* Board::deepCopy() {
	Board *b = new Board(_game);
	b->_parent = _parent;
	b->_to = _to;
	b->_from = _from;
	b->_isPlayerTurn = _isPlayerTurn;

	b->_opponentKing = _opponentKing;
	b->_opponentMen = _opponentMen;
	b->_playerKing = _playerKing;
	b->_playerMen = _playerMen;

	b->_stepWasAJump = _stepWasAJump;
	b->_becameKing = _becameKing;
	return b;
}

char Board::at(pair<int, int> cord) {
	if (cord.first < 0 || cord.second < 0 || cord.first > 7 || cord.second > 7)return 0;
	if (isPresent(_opponentMen, cord)) return 'b';
	else if (isPresent(_opponentKing, cord)) return 'B';
	else if (isPresent(_playerMen, cord)) return 'w';
	else if (isPresent(_playerKing, cord)) return 'W';
	else return '.';
}

void Board::insert(pair<unsigned long long int, int> &_presence, pair<int, int> cord) {
	unsigned long long int e = 1;
	_presence.first = _presence.first | (e << (cord.first * 8 + cord.second));
	_presence.second++;
}

bool Board::isPresent(pair<unsigned long long int, int> &_presence, pair<int, int> cord) {
	unsigned long long int e = 1;
	return (_presence.first & (e << (cord.first * 8 + cord.second))) != 0LL;
}

void Board::erase(pair<unsigned long long int, int> &_presence, pair<int, int> cord) {
	if (isPresent(_presence, cord))_presence.second--;

	unsigned long long int e = 1;
	_presence.first = _presence.first & ~(e << (cord.first * 8 + cord.second));
}

list<pair<int, int>> Board::cordinates(pair<unsigned long long int, int> &_presence) {
	unsigned long long int l = _presence.first;
	list<pair<int, int>> q;
	while (l) {
		unsigned long long int r = (unsigned long long int)(log(l) / log(2));
		l = l % ((unsigned long long int)pow(2LL, r));
		q.push_back(make_pair((int)(r / 8), (int)(r % 8)));
	}
	return q;
}


bool Board::opponent(pair<int, int> cord) {
	return opponentMen(cord) || opponentKing(cord);
}
bool Board::opponentMen(pair<int, int> cord) {
	return at(cord) == 'b';
}
bool Board::opponentKing(pair<int, int> cord) {
	return at(cord) == 'B';
}

bool Board::player(pair<int, int> cord) {
	return playerMen(cord) || playerKing(cord);
}

bool Board::playerMen(pair<int, int> cord) {
	return at(cord) == 'w';
}

bool Board::playerKing(pair<int, int> cord) {
	return at(cord) == 'W';
}

bool Board::empty(pair<int, int> cord) {
	return at(cord) == '.';
}

void Board::printBoard() {
	if (!_game->_isPlayerBlack || _game->_protoView) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				cout << at({ i, j }) << ' ';
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				switch (at({ 7 - i, 7 - j })){
				case 'b':
					cout << "w ";
					break;
				case 'B':
					cout << "W ";
					break;
				case 'w':
					cout << "b ";
					break;
				case 'W':
					cout << "B ";
					break;
				default:
					cout << ". ";
				}
			}
			cout << endl;
		}
	}
	
	cout << "-------------------------------------" << endl;
}

void Board::printToFile() {
	ofstream fo("D:\\workspace\\vs\\JThread\\ConsoleApplication4\\ConsoleApplication4\\input.txt");

	if (_game->_isPlayerBlack) fo << "SINGLE\nWHITE\n100.0\n";
	else fo << "SINGLE\nBLACK\n100.0\n";

	if (!_game->_isPlayerBlack) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				fo << at({ i, j });
			}
			fo << endl;
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				switch (at({ 7 - i, 7 - j })){
				case 'b':
					fo << 'w';
					break;
				case 'B':
					fo << 'W';
					break;
				case 'w':
					fo << 'b';
					break;
				case 'W':
					fo << 'B';
					break;
				default:
					fo << '.';
				}
			}
			fo << endl;
		}
	}
	fo.close();
}

string Board::convert(pair<int, int> cord) {
	char e1 = (cord.second + 'a');
	char e2 = ('1' + 7 - cord.first);
	string x;
	x.push_back(e1);
	x.push_back(e2);
	return x;
}

bool Board::isEnd() {
	return (_playerKing.second + _playerMen.second == 0) || (_opponentKing.second + _opponentMen.second == 0);
}