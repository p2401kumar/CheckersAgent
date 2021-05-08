#include "Game.h"
#include "Board.h"
#include "BoardProperties.h"
#include "MinimaxHelper.h"

Game::Game(string player, int depth, bool randomBest, int heuristic, bool useAlphaBeta, vector<string>& board) {
	_player = player;
	_isPlayerBlack = (_player == "BLACK");
	_protoView = false;

	_boardProperties = new BoardProperties(this);
	_initialBoard = new Board(this);
	_initialBoard->_isPlayerTurn = false;
	_minimaxHelper = new MinimaxHelper(this, depth, useAlphaBeta, heuristic);

	if (!_isPlayerBlack) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				switch (board[i][j]){
					case 'b':
						_initialBoard->insert(_initialBoard->_opponentMen, { i, j });
						break;
					case 'B':
						_initialBoard->insert(_initialBoard->_opponentKing, { i, j });
						break;
					case 'w':
						_initialBoard->insert(_initialBoard->_playerMen, { i, j });
						break;
					case 'W':
						_initialBoard->insert(_initialBoard->_playerKing, { i, j });
						break;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				switch (board[i][j]){
				case 'w':
					_initialBoard->insert(_initialBoard->_opponentMen, { 7 - i, 7 - j });
					break;
				case 'W':
					_initialBoard->insert(_initialBoard->_opponentKing, { 7 - i, 7 - j });
					break;
				case 'b':
					_initialBoard->insert(_initialBoard->_playerMen, { 7 - i, 7 - j });
					break;
				case 'B':
					_initialBoard->insert(_initialBoard->_playerKing, { 7 - i, 7 - j });
					break;
				}
			}
		}
	}
}