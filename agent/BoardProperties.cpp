#include "BoardProperties.h"
#include "Board.h"

BoardProperties::BoardProperties(Game *game) {
	_game = game;
}

pair<int, int> BoardProperties::dir1(pair<int, int> cord) {
	return{ cord.first - 1, cord.second - 1 };
}
pair<int, int> BoardProperties::dir2(pair<int, int> cord) {
	return{ cord.first - 1, cord.second + 1 };
}
pair<int, int> BoardProperties::dir3(pair<int, int> cord) {
	return{ cord.first + 1, cord.second - 1 };
}
pair<int, int> BoardProperties::dir4(pair<int, int> cord) {
	return{ cord.first + 1, cord.second + 1 };
}

pair<int, int> BoardProperties::dir(int dir, pair<int, int> cord) {
	switch (dir) {
	case 1:
		return dir1(cord);
	case 2:
		return dir2(cord);
	case 3:
		return dir3(cord);
	case 4:
		return dir4(cord);
	}
	return{ -1, -1 };
}

bool BoardProperties::playerJumpPossible(Board *board, pair<int, int> cord) {
	if (cord.first != INT_MIN) { // check only for given cord

		if (board->playerKing(cord)) {
			for (int i = 1; i <= 4; i++) { // check jump for player king
				if (board->opponent(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) return true;
			}
		}
		else if (board->playerMen(cord)) {
			for (int i = 1; i <= 2; i++) { // check jump for player Men
				if (board->opponent(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) return true;
			}
		}
		return false;
	}
	else { // check for all cord
		for (pair<int, int> e : board->cordinates(board->_playerKing)) {  // check jump for player king
			if (playerJumpPossible(board, e))return true;
		}
		for (pair<int, int> e : board->cordinates(board->_playerMen)) { // check jump for player Men
			if (playerJumpPossible(board, e))return true;
		}
		return false;
	}	
}

bool BoardProperties::opponentJumpPossible(Board *board, pair<int, int> cord) {
	if (cord.first != INT_MIN) {	// check only for given cord

		if (board->opponentKing(cord)) {
			for (int i = 4; i >= 1; i--) {
				if (board->player(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) return true;
			}
		}
		else if (board->opponentMen(cord)){
			for (int i = 4; i >= 3; i--) {
				if (board->player(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) return true;
			}
		}
		return false;
	}
	else {							// check for all cord
		for (pair<int, int> e : board->cordinates(board->_opponentKing)) {
			if (opponentJumpPossible(board, e)) return true;
		}
		for (pair<int, int> e : board->cordinates(board->_opponentMen)) {
			if (opponentJumpPossible(board, e)) return true;
		}
		return false;
	}	
}

list<Board*> BoardProperties::playerJumpList(Board *board, pair<int, int> cord) {
	list<Board*> list;
	if (cord.first != INT_MIN) {

		if (board->playerKing(cord)) {     // check jump for player king            
			for (int i = 1; i <= 4; i++) { 
				if (board->opponent(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) {
					Board* J = board->deepCopy();
					J->erase(J->_playerKing, cord);
					J->insert(J->_playerKing, dir(i, dir(i, cord)));

					if (J->opponentKing(dir(i, cord))) {
						J->erase(J->_opponentKing, dir(i, cord));
					}
					else {
						J->erase(J->_opponentMen, dir(i, cord));
					}

					J->_parent = board;
					J->_from = cord;
					J->_to = dir(i, dir(i, cord));
					J->_stepWasAJump = true;

					J->_isPlayerTurn = true;
					list.push_back(J);
				}
			}
		}
		else if (board->playerMen(cord)) {// check jump for player Men
			for (int i = 1; i <= 2; i++) { 
				if (board->opponent(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) {
						Board* J = board->deepCopy();
						J->erase(J->_playerMen, cord);
						J->insert(J->_playerMen, dir(i, dir(i, cord)));

						if (J->opponentKing(dir(i, cord))) {
							J->erase(J->_opponentKing, dir(i, cord));
						}
						else {
							J->erase(J->_opponentMen, dir(i, cord));
						}

						J->_parent = board;
						J->_from = cord;
						J->_to = dir(i, dir(i, cord));
						J->_stepWasAJump = true;

						J->_isPlayerTurn = true;

						if (dir(i, dir(i, cord)).first == 0) {      // CONVERT TO KING
							J->erase(J->_playerMen, dir(i, dir(i, cord)));
							J->insert(J->_playerKing, dir(i, dir(i, cord)));
							J->_stepWasAJump = false;
							J->_becameKing = true;
						}
						list.push_back(J);
				}	
			}
		}
	}
	else {
		for (pair<int, int> e : board->cordinates(board->_playerKing)) {
			for (Board* l : playerJumpList(board, e)) {
				list.push_back(l);
			}
		}
		for (pair<int, int> e : board->cordinates(board->_playerMen)) {
			for (Board* l : playerJumpList(board, e)) {
				list.push_back(l);
			}
		}
	}

	return list;
}

list<Board*> BoardProperties::opponentJumpList(Board *board, pair<int, int> cord) {
	list<Board*> list;

	if (cord.first != INT_MIN) {

		if (board->opponentKing(cord)) { // check jump for opponent king  
			for (int i = 4; i >= 1; i--) {
				if (board->player(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) {
					Board* J = board->deepCopy();
					J->erase(J->_opponentKing, cord);
					J->insert(J->_opponentKing, dir(i, dir(i, cord)));

					if (J->playerKing(dir(i, cord))) {
						J->erase(J->_playerKing, dir(i, cord));
					}
					else {
						J->erase(J->_playerMen, dir(i, cord));
					}

					J->_parent = board;
					J->_from = cord;
					J->_to = dir(i, dir(i, cord));
					J->_stepWasAJump = true;

					J->_isPlayerTurn = false;
					list.push_back(J);
				}
			}
		}
		else if (board->opponentMen(cord)) { // check jump for opponent men
			for (int i = 4; i >= 3; i--) {
				if (board->player(dir(i, cord)) && board->empty(dir(i, dir(i, cord)))) {
					Board* J = board->deepCopy();
					J->erase(J->_opponentMen, cord);
					J->insert(J->_opponentMen, dir(i, dir(i, cord)));

					if (J->playerKing(dir(i, cord))) {
						J->erase(J->_playerKing, dir(i, cord));
					}
					else {
						J->erase(J->_playerMen, dir(i, cord));
					}

					J->_parent = board;
					J->_from = cord;
					J->_to = dir(i, dir(i, cord));
					J->_stepWasAJump = true;

					J->_isPlayerTurn = false;

					if (dir(i, dir(i, cord)).first == 7) {      // CONVERT TO KING
						J->erase(J->_opponentMen, dir(i, dir(i, cord)));
						J->insert(J->_opponentKing, dir(i, dir(i, cord)));
						J->_stepWasAJump = false;
						J->_becameKing = true;
					}
					list.push_back(J);
				}
			}
		}
	}
	else {
		for (pair<int, int> e : board->cordinates(board->_opponentKing)) {
			for (Board* b : opponentJumpList(board, e)) {
				list.push_back(b);
			}
		}
		for (pair<int, int> e : board->cordinates(board->_opponentMen)) {
			for (Board* b : opponentJumpList(board, e)) {
				list.push_back(b);
			}
		}
	}

	return list;
}

list<Board*> BoardProperties::playerMove(Board *board) {
	list<Board*> list;
	for (pair<int, int> e : board->cordinates(board->_playerKing)) {
		for (int i = 1; i <= 4; i++) {
			if (board->empty(dir(i, e))) {
				Board *J = board->deepCopy();
				J->erase(J->_playerKing, e);
				J->insert(J->_playerKing, dir(i, e));

				J->_parent = board;
				J->_from = e;
				J->_to = dir(i, e);
				J->_stepWasAJump = false;

				J->_isPlayerTurn = true;
				list.push_back(J);
			}
		}
	}
	for (pair<int, int> e : board->cordinates(board->_playerMen)) {
		for (int i = 1; i <= 2; i++) {
			if (board->empty(dir(i, e))) {
				Board *J = board->deepCopy();
				J->erase(J->_playerMen, e);
				J->insert(J->_playerMen, dir(i, e));

				J->_parent = board;
				J->_from = e;
				J->_to = dir(i, e);
				J->_stepWasAJump = false;

				J->_isPlayerTurn = true;

				if (dir(i, e).first == 0) {      // CONVERT TO KING
					J->erase(J->_playerMen, dir(i, e));
					J->insert(J->_playerKing, dir(i, e));
					J->_stepWasAJump = false;
					J->_becameKing = true;
				}
				list.push_back(J);
			}			
		}
	}

	return list;
}

list<Board*> BoardProperties::opponentMove(Board *board) {
	list<Board*> list;
	for (pair<int, int> e : board->cordinates(board->_opponentKing)) {
		for (int i = 4; i >= 1; i--) {
			if (board->empty(dir(i, e))) {
				Board *J = board->deepCopy();
				J->erase(J->_opponentKing, e);
				J->insert(J->_opponentKing, dir(i, e));

				J->_parent = board;
				J->_from = e;
				J->_to = dir(i, e);
				J->_stepWasAJump = false;

				J->_isPlayerTurn = false;
				list.push_back(J);
			}
		}
	}

	for (pair<int, int> e : board->cordinates(board->_opponentMen)) {
		for (int i = 4; i >= 3; i--) {
			if (board->empty(dir(i, e))) {
				Board *J = board->deepCopy();
				J->erase(J->_opponentMen, e);
				J->insert(J->_opponentMen, dir(i, e));

				J->_parent = board;
				J->_from = e;
				J->_to = dir(i, e);
				J->_stepWasAJump = false;

				J->_isPlayerTurn = false;

				if (dir(i, e).first == 7) {      // CONVERT TO KING
					J->erase(J->_opponentMen, dir(i, e));
					J->insert(J->_opponentKing, dir(i, e));
					J->_stepWasAJump = false;
					J->_becameKing = true;
				}
				list.push_back(J);
			}
		}
	}
	return list;
}

list<Board*> BoardProperties::getNextMove(Board *board) {
	if (board->_isPlayerTurn) {
		if (board->_stepWasAJump && board->player(board->_to) && playerJumpPossible(board, board->_to)) {
			return playerJumpList(board, board->_to);
		}
		else {
			if (opponentJumpPossible(board, { INT_MIN, INT_MIN })) {
				return opponentJumpList(board, { INT_MIN, INT_MIN });
			}
			else {
				return opponentMove(board);
			}
		}
	}
	else {
		if (board->_stepWasAJump && board->opponent(board->_to) && opponentJumpPossible(board, board->_to)) {
			return opponentJumpList(board, board->_to);
		}
		else {
			if (playerJumpPossible(board, { INT_MIN, INT_MIN })) {
				return playerJumpList(board, { INT_MIN, INT_MIN });
			}
			else {
				return playerMove(board);
			}
		}
	}
}