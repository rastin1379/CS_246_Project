#include "chessview.h"
#include "textobserver.h"

using namespace std;

ChessView::run() {
	string command;
	board = make_shared<Board>();
	observers.push_back(make_shared<TextObserver>(board));
	controller = ChessController(board);
	while (cin >> command) {
		if (command == "game") {
			string p1;
			string p2;
			cin  >> p1 >> p2;
			controller.start(p1, p2);
		}
	}	
}
