// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <bits/stdc++.h>
#include "Board.h"
#include "Game.h"
#include "BoardProperties.h"
#include "MinimaxHelper.h"
using namespace std;

string gameType, player, row;
float h_time;
vector<string> b;
bool toFile = false;

void takeInput(int &count) {
	ifstream fin("D:\\workspace\\vs\\JThread\\ConsoleApplication4\\ConsoleApplication4\\input.txt");
	b.clear();
	fin >> gameType;		cout << gameType << endl;
	fin >> player;			cout << player << endl;
	fin >> h_time;			cout << h_time << endl;

	for (int i = 0; i < 8; i++) { fin >> row; b.push_back(row); }
	fin.close();
	cout << "Count:" << count << endl;
	count++;
}

void printBoardChanges(Board *x, Board* initialBoard) {
	list<Board*> list;
	while (x != initialBoard) {
		list.push_front(x);
		x = x->_parent;
	}

	ofstream fo("D:\\workspace\\vs\\JThread\\ConsoleApplication4\\ConsoleApplication4\\output.txt");
	
	char isJump = list.size() > 1?'J': 'E';
	while (!list.empty()) {
		Board* xx = list.front();

		if (toFile) fo << isJump << ' ' << xx->convert(xx->_from) << ' ' << xx->convert(xx->_to) << endl;
		else cout << isJump << ' ' << xx->convert(xx->_from) << ' ' << xx->convert(xx->_to) << endl;

		list.pop_front();
	}

	fo.close();
}

int main() {
	int count = 0;
	/*
	ofstream fo("D:\\workspace\\vs\\JThread\\ConsoleApplication4\\ConsoleApplication4\\input.txt");
	fo << "SINGLE\nBLACK\n100.0\n";
	fo << ".b.b.b.b\nb.b.b.b.\n.b.b.b.b\n........\n........\nw.w.w.w.\n.w.w.w.w\nw.w.w.w.\n";
	fo.close();*/
	

	bool playerBlack = false;
	while (1) {
		takeInput(count);
		Game *_game = new Game(player, 8, true, 1, true, b);
		_game->_initialBoard->printBoard();

		Board *x = _game->_minimaxHelper->findbestBoard(_game->_initialBoard);
		while (!x->isEnd() && !x->_becameKing && x->_stepWasAJump && _game->_boardProperties->playerJumpPossible(x, x->_to)) {
			x = _game->_minimaxHelper->findbestBoard(x);
		}

		x->printBoard();
		if (x->isEnd())break;
		//x->printToFile();		
		//printBoardChanges(x, _game->_initialBoard);
		playerBlack = !playerBlack;
		cin >> playerBlack;
		//break;
	}

	return 0;
}

