#include "Game.h"
#include "Board.h"
#include "MinimaxHelper.h"
#include "BoardProperties.h"

MinimaxHelper::MinimaxHelper(Game *game, int depth, bool useAlphaBeta, int heuristic) {
	_boardHeuristic = new BoardHeuristic(game, heuristic);
	_heuristic = heuristic;
	_game = game;
	_depth = depth;
	_UseAlphaBeta = useAlphaBeta;
}


void optionPrinter(Board* board, list<Board*> l) {
	vector<Board*> _vec(l.begin(), l.end());

	for (int i = 0; i < 8; i++) {
		for (int k = 0; k < 8; k++) {
			cout << board->at({ i, k });
		}
		cout << " :::: ";
		for (int j = 0; j < l.size(); j++) {

			for (int k = 0; k < 8; k++) {
				cout << _vec[j]->at({ i, k });
			}
			cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}
int c = 0;
int MinimaxHelper::minimax(Board* board, int depth, int alpha, int beta, Board* bb, list<Board*> ll) {
	ll.push_back(board);
	if (depth == 0 || 
		((board->_playerKing.second + board->_playerMen.second) == 0 ||
				(board->_opponentKing.second + board->_opponentMen.second) == 0)) {
		optionPrinter(bb, ll);
		/*
		if (_boardHeuristic->heuristic(board) != 0) {
			cout << "##################################" << endl;
			board->printBoard();
			cout << _boardHeuristic->heuristic(board) << endl;
			cout << "##################################" << endl;
		}		
		*/
		return _boardHeuristic->heuristic(board);
	}

	list<Board*> l = _game->_boardProperties->getNextMove(board);
	//optionPrinter(board, l);

	if (board->_isPlayerTurn) {
		int val = INT_MIN;
		for (Board *b : l) {
			val = max(val, minimax(b, depth - 1, alpha, beta, bb, ll));
			alpha = max(alpha, val);

			if (_UseAlphaBeta && alpha >= beta) {
				break;
			}
		}
		return val;
	}
	else {
		int val = INT_MAX;
		for (Board *b : l) {
			val = min(val, minimax(b, depth - 1, alpha, beta, bb, ll));
			beta = min(beta, val);

			if (_UseAlphaBeta && alpha >= beta) {
				break;
			}
		}
		return val;
	}
}

Board *MinimaxHelper::findbestBoard(Board* board) {
	int best = INT_MIN;
	Board *bestBoard = nullptr;
	c++;
	vector<Board*> _vec;
	list<Board*> l = _game->_boardProperties->getNextMove(board);
	if (l.size() == 1)return l.front();
	for (Board* e : l) {
		//e->printBoard();
		list<Board*> ll;
		int val = minimax(e, _depth, INT_MIN, INT_MAX, board, ll);
		
		if (best < val) {
			_vec.clear();
			best = val;
			_vec.push_back(e);
		}
		else if (best == val) {
			_vec.push_back(e);
		}
	}


	return _vec.empty()?nullptr:_vec[rand() % _vec.size()];
}