#include "chessview.h"
#include "textobserver.h"

using namespace std;

void ChessView::run() {
	string command;
	auto board = make_shared<Board>();
	vector<shared_ptr<TextObserver>> observers;
	
	observers.push_back(make_shared<TextObserver>(board));
	ChessController controller = ChessController(board);
	while (cin >> command) {
		if (command == "game") {
			string p1;
			string p2;
			cin  >> p1 >> p2;
			controller.start(p1, p2);
		}
	}	
}
