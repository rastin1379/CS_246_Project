#include "chessview.h"
#include "textobserver.h"
#include <iostream>

using namespace std;

void ChessView::run()
{
	string command;
	auto board = make_shared<Board>();
	vector<shared_ptr<TextObserver>> observers;

	observers.push_back(make_shared<TextObserver>(board));
	ChessController controller = ChessController(board);
	while (cin >> command)
	{
		if (command == "game")
		{
			try {
				string p1;
				string p2;
				cin >> p1 >> p2;
				controller.start(p1, p2);
			} catch (GameError ge) {
                		cout << "game error: " << ge.get_message() << endl;
        		}
		}
		if (command == "move")
		{
			try {
				string move_commands;
				getline(cin, move_commands);
				controller.move(move_commands);
			} catch (GameError ge) {
                		cout << "game error: " << ge.get_message() << endl;
        		}	
		}
		if (command == "undo") {
			try {
				controller.undo();
			} catch (GameError ge) {
                                cout << "game error: " << ge.get_message() << endl;
                        }
		}
		if (command == "resign") {
			try {
				controller.resign();
			} catch (GameError ge) {
                                cout << "game error: " << ge.get_message() << endl;
                        }
		}
		if (command == "setup") {
			try {
				controller.setup();
			} catch (GameError ge) {
                                cout << "game error: " << ge.get_message() << endl;
                        }
		}
		if (command == "+") {
			try {
				char piece;
				string position;
				cin >> piece >> position;
				controller.setup_add(piece, position);
				board->notifyObservers("n");
			} catch (GameError ge) {
                                cout << "game error: " << ge.get_message() << endl;
                        }
		}
		if (command == "-") {
			try {
                                string position;
				cin >> position;
                                controller.setup_remove(position);
				board->notifyObservers("n");
                        } catch (GameError ge) {
                                cout << "game error: " << ge.get_message() << endl;
                        }
		}
		if (command == "=") {
			try {
				char color;
				cin >> color;
				controller.setup_color(color);
				board->notifyObservers("n");
			} catch(GameError ge) { 
				cout << "game error: " << ge.get_message() << endl;
			}
		}
		if (command == "done") {
			try {
				controller.setup_done();
			} catch(GameError ge) {
                                cout << "game error: " << ge.get_message() << endl;
                        }
		}
	}
}
