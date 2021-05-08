#include "BoardHeuristic.h"
#include "BoardHeuristicHelper.h"
#include "Game.h"

BoardHeuristic::BoardHeuristic(Game *game, int heuristic) {
	_game = game;
	_heuristic = heuristic;
}

int heuristic1(Board* board){
	if (board->_playerKing.second + board->_playerMen.second == 0) {
		return INT_MIN;
	}
	else if (board->_opponentKing.second + board->_opponentMen.second == 0) {
		return INT_MAX;
	}

	return board->_playerKing.second * 2 + board->_playerMen.second - (board->_opponentKing.second * 2 + board->_opponentMen.second);
}

int heuristic2(BoardProperties *boardProperties, Board* board) {
	if (board->_playerKing.second + board->_playerMen.second == 0) {
		return INT_MIN;
	}
	else if (board->_opponentKing.second + board->_opponentMen.second == 0) {
		return INT_MAX;
	}

	return heuristic2BoardCost(boardProperties, board)
		+ board->_playerKing.second * 10 + board->_playerMen.second * 5
			- (board->_opponentKing.second * 10 + board->_opponentMen.second * 5);
}

int BoardHeuristic::heuristic(Board* board) {
	switch (_heuristic){
		case 1:
			return heuristic1(board);
		case 2:
			return heuristic2(_game->_boardProperties, board);
	}
	return 0;
}