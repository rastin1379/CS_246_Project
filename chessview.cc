#include "chessview.h"
#include "textobserver.h"
#include "graphicsobserver.h"
#include <iostream>

using namespace std;

void ChessView::run()
{
	string command;
	auto board = make_shared<Board>();
	vector<shared_ptr<TextObserver>> observers;
	vector<shared_ptr<GraphicsObserver>> graphic_observers;

	observers.push_back(make_shared<TextObserver>(board));
	graphic_observers.push_back(make_shared<GraphicsObserver>(board));
	ChessController controller = ChessController(board);
	while (cin >> command)
	{
		if (command == "game")
		{
			try
			{
				string p1;
				string p2;
				cin >> p1 >> p2;
				controller.start(p1, p2);
			}
			catch (GameError ge)
			{
				cout << "game error: " << ge.get_message() << endl;
			}
		}
		if (command == "move")
		{
			try
			{
				string move_commands;
				getline(cin, move_commands);
				controller.move(move_commands);
			}
			catch (GameError ge)
			{
				cout << "game error: " << ge.get_message() << endl;
			}
		}
		if (command == "undo")
		{
			try
			{
				controller.undo();
			}
			catch (GameError ge)
			{
				cout << "game error: " << ge.get_message() << endl;
			}
		}
		if (command == "resign")
		{
			// TO DO: find which player concedes defeat
			// std::cout << "the #COLOUR player concedes defeat. #OPPONENT_COLOUR wins"
			return;
		}
	}
}
