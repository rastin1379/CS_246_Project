#include <iostream>
#include "observer.h"
#include "textobserver.h"

using namespace std;

TextObserver::TextObserver(Board * board) : board{board}
{
	board->attach(this);
}

TextObserver::~TextObserver(){
	map<string, int> scores = board->get_scores();
        cout << endl << "Final Score:" << endl;
        map<string, int>::iterator it;
        for (it = scores.begin(); it != scores.end(); it++) {
                cout << it->first << ": " << it->second << endl;
	}
	board->detach(this);
}

void TextObserver::notify(string result) {
	std::vector<std::vector<std::shared_ptr<Piece>>> board_array 
		= board->get_board();
	for (int i = 0; i < board_size; ++i) {
		cout << board_size - i << ' ';
		for (int j = 0; j < board_size; ++j) {
			if (board_array[i][j] == nullptr){
				if ((j + i) % 2 == 1) { cout << '_'; }
				else { cout << ' '; }
			}
			else {
				cout << board_array[i][j]->get_type();
			}
		}
		cout << endl;
	}	
	cout << endl << "  abcdefgh" << endl;
	cout << endl << endl;
	if (result == "eb") {
		cout << "Checkmate! Black wins!" << endl;
	}
	else if (result == "ew") {
		cout << "Checkmate! White wins!" << endl;
	}
	else if (result == "cw") {
		cout << "White is in check." << endl;
	}
	else if (result == "cb") {
		cout << "Black is in check." << endl;
	}
	else if (result == "s") {
		cout << "Stalemate!" << endl;
	}
	else if (result == "rw") {
		cout << "White wins!" << endl;
	}
	else if (result == "rb") {
		cout << "Black wins!" << endl;
	}
	if (result == "s" || result == "ew" || result == "eb") {
		map<string, int> scores = board->get_scores();
		cout << endl << "Final Score:" << endl;
		map<string, int>::iterator it;
		for (it = scores.begin(); it != scores.end(); it++) {
			cout << it->first << ": " << it->second << endl;
		}
	}
}
