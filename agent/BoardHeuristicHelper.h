#include "Board.h"
#include "BoardProperties.h"

int VULNERABLE = 0;
int PROTECTED = 0;
int MIDDLE_CENTER = 4;
int MIDDLE_CORNER = 0;
int CROSS_BORDER = 3;
int CAN_CUT = 0;

bool canCut(BoardProperties *bp, Board* board, pair<int, int> cord) {
	if (board->player(cord)) {
		return bp->playerJumpPossible(board, cord);
	}
	else if (board->opponent(cord)) {
		return bp->opponentJumpPossible(board, cord);
	}

	return false;
}

bool isVulnerable(BoardProperties *bp, Board* board, pair<int, int> cord) {
	if (board->player(cord)) {
		return
			board->opponent(bp->dir1(cord)) && board->empty(bp->dir4(cord)) ||
			board->opponent(bp->dir2(cord)) && board->empty(bp->dir3(cord)) ||
			board->opponentKing(bp->dir3(cord)) && board->empty(bp->dir2(cord)) ||
			board->opponentKing(bp->dir4(cord)) && board->empty(bp->dir1(cord));
	}
	else if (board->opponent(cord)) {
		return
			board->player(bp->dir3(cord)) && board->empty(bp->dir2(cord)) ||
			board->player(bp->dir4(cord)) && board->empty(bp->dir1(cord)) ||
			board->playerKing(bp->dir1(cord)) && board->empty(bp->dir4(cord)) ||
			board->playerKing(bp->dir2(cord)) && board->empty(bp->dir3(cord));
	}
	return false;
}

bool border(pair<int, int> cord) {
	return (cord.first == 0 || cord.first == 7 || cord.second == 0 || cord.second == 7);
}

bool backedUp(BoardProperties *bp, Board *board, pair<int, int> cord) {
	if (board->player(cord)) {
		return
			board->player(bp->dir1(cord)) && board->player(bp->dir2(cord)) ||
			board->player(bp->dir2(cord)) && board->player(bp->dir4(cord)) ||
			board->player(bp->dir4(cord)) && board->player(bp->dir3(cord)) ||
			board->player(bp->dir3(cord)) && board->player(bp->dir1(cord));
	}
	else if (board->opponent(cord)) {
		return
			board->opponent(bp->dir1(cord)) && board->opponent(bp->dir2(cord)) ||
			board->opponent(bp->dir2(cord)) && board->opponent(bp->dir4(cord)) ||
			board->opponent(bp->dir4(cord)) && board->opponent(bp->dir3(cord)) ||
			board->opponent(bp->dir3(cord)) && board->opponent(bp->dir1(cord));
	}
	return false;
}

bool middleCenter(pair<int, int> cord) {
	return cord.first >= 3 && cord.first <= 4 && cord.second >= 2 && cord.second <= 5;
}

bool middleCorner(pair<int, int> cord) {
	return cord.first >= 3 && cord.first <= 4 && (cord.second <= 1 || cord.second >= 6);
}

bool crossBorder(Board* board, pair<int, int> cord) {
	if (board->player(cord)) {
		return cord.first <= 3;
	}
	else if (board->opponent(cord)) {
		return cord.first >= 4;
	}
	return false;
}

int heuristic2BoardCost(BoardProperties *boardProperties, Board* board) {
	int cost = 0;
	for (pair<int, int> e : board->cordinates(board->_playerKing)) {
		cost -= isVulnerable(boardProperties, board, e) * VULNERABLE;
		cost += (border(e) || backedUp(boardProperties, board, e)) * PROTECTED;
		cost += middleCenter(e) * MIDDLE_CENTER;
		cost += middleCorner(e) * MIDDLE_CORNER;
		cost += crossBorder(board, e) * CROSS_BORDER;
		cost += canCut(boardProperties, board, e) * CAN_CUT;
	}
	for (pair<int, int> e : board->cordinates(board->_playerMen)) {
		cost -= isVulnerable(boardProperties, board, e) * VULNERABLE;
		cost += (border(e) || backedUp(boardProperties, board, e)) * PROTECTED;
		cost += middleCenter(e) * MIDDLE_CENTER;
		cost += middleCorner(e) * MIDDLE_CORNER;
		cost += crossBorder(board, e) * CROSS_BORDER;
		cost += canCut(boardProperties, board, e) * CAN_CUT;
	}
	for (pair<int, int> e : board->cordinates(board->_opponentKing)) {
		cost += isVulnerable(boardProperties, board, e) * VULNERABLE;
		cost += (border(e) || backedUp(boardProperties, board, e)) * PROTECTED;
		cost -= middleCenter(e) * MIDDLE_CENTER;
		cost -= middleCorner(e) * MIDDLE_CORNER;
		cost -= crossBorder(board, e) * CROSS_BORDER;
		cost -= canCut(boardProperties, board, e) * CAN_CUT;
	}
	for (pair<int, int> e : board->cordinates(board->_opponentMen)) {
		cost += isVulnerable(boardProperties, board, e) * VULNERABLE;
		cost += (border(e) || backedUp(boardProperties, board, e)) * PROTECTED;
		cost -= middleCenter(e) * MIDDLE_CENTER;
		cost -= middleCorner(e) * MIDDLE_CORNER;
		cost -= crossBorder(board, e) * CROSS_BORDER;
		cost -= canCut(boardProperties, board, e) * CAN_CUT;
	}

	return cost;
}