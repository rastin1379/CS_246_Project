#include <iostream>
#include "observer.h"
#include "textobserver.h"

using namespace std;

TextObserver::TextObserver(shared_ptr<Board> board) : board{board}
{
  board->attach(this);
}

TextObserver::~TextObserver()
{
  board->detach(this);
}

void TextObserver::notify() {
	std::vector<std::vector<std::shared_ptr<Piece>>> board_array 
		= board->get_board();
	for (int i = 0; i < board_size; ++i) {
		cout << board_size - i << ' ';
		for (int j = 0; j < board_size; ++j) {
			if (board_array[i][j] == nullptr){
				if (j % 2 == 1) { cout << '_'; }
				else { cout << ' '; }
			}
			else {
				cout << board_array[i][j]->get_type();
			}
		}
		cout << endl;
	}	
	cout << endl << "  abcdefgh" << endl;
}
