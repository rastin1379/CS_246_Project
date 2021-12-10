#include <iostream>
#include "observer.h"
#include "window.h"
#include "graphicsobserver.h"

using namespace std;

GraphicsObserver::GraphicsObserver(shared_ptr<Board> board) : board{board}, 
  xw{new Xwindow(480, 480)}
{
  board->attach(this);
}

GraphicsObserver::~GraphicsObserver()
{
  board->detach(this);
}

void GraphicsObserver::notify(string result)
{
  if (board->get_move_size() == 0)
  {
    // render the board from scratch
    xw->drawString(5, 10, "r");
    xw->drawString(15, 10, "n");
    xw->drawString(25, 10, "b");
    xw->drawString(35, 10, "q");
    xw->drawString(45, 10, "k");
    xw->drawString(55, 10, "b");
    xw->drawString(65, 10, "n");
    xw->drawString(75, 10, "r");

    xw->drawString(5, 20, "p");
    xw->drawString(15, 20, "p");
    xw->drawString(25, 20, "p");
    xw->drawString(35, 20, "p");
    xw->drawString(45, 20, "p");
    xw->drawString(55, 20, "p");
    xw->drawString(65, 20, "p");
    xw->drawString(75, 20, "p");


    for (int i = 2; i < 6; i++)
    {
      for (int j = 0; j <= 7; j++)
      {
        if ((i % 2 == 0) && (j % 2 == 0))
        {
          //prints white
          xw->fillRectangle(j * 10 + 5, i * 10, 10, 10, 0);
        }
        else if ((i % 2 == 0) && (j % 2 != 0))
        {
          // prints black
          xw->fillRectangle(j * 10, i * 10, 10, 10, 1);
        }
        else if ((i % 2 != 0) && (j % 2 == 0))
        {
          // prints black
          xw->fillRectangle(j * 10, i * 10, 10, 10, 1);
        }
        else
        {
          // prints white
          xw->fillRectangle(j * 10, i * 10, 10, 10, 0);
        }
      }
    }

    xw->drawString(2, 70, "P");
    xw->drawString(12, 70, "P");
    xw->drawString(22, 70, "P");
    xw->drawString(32, 70, "P");
    xw->drawString(42, 70, "P");
    xw->drawString(52, 70, "P");
    xw->drawString(62, 70, "P");
    xw->drawString(72, 70, "P");

    xw->drawString(2, 80, "R");
    xw->drawString(12, 80, "N");
    xw->drawString(22, 80, "B");
    xw->drawString(32, 80, "Q");
    xw->drawString(42, 80, "K");
    xw->drawString(52, 80, "B");
    xw->drawString(62, 80, "N");
    xw->drawString(72, 80, "R");
  }

}
