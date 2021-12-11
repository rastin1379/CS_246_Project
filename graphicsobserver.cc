#include <iostream>
#include "observer.h"
#include <string>
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
  } else {

  // the x position starts from 0, from left
  // the y position starts from 0, from top

  Move last_move = board->get_last_move();
  Position from = last_move.get_from();
  Position to = last_move.get_to();

  // 1. Clear the "to" position
  // 2. clear the "from" position

  int from_x = from.get_x();
  int from_y = from.get_y();

  if((from_x % 2 == 0) && (from_y % 2 == 0)){
  //if x % 2 == 0 and y % 2 == 0
    // prints white
    xw->fillRectangle(from_x * 10, from_y * 10, 10, 10, 0);

  } else if ((from_x % 2 == 0) && (from_y % 2 != 0)){
  // if x % 2 == 0 and y % 2 != 0
    // prints black
    xw->fillRectangle(from_x * 10, from_y * 10, 10, 10, 1);

  } else if ((from_x % 2 != 0) && (from_y % 2 == 0)){
  // if x % 2 != 0 y % 2 == 0
    // prints black
    xw->fillRectangle(from_x * 10, from_y * 10, 10, 10, 1);

  } else {
  // else 
    // prints white
    xw->fillRectangle(from_x * 10, from_y * 10, 10, 10, 0);
  }
  
  // 3. get the piece (move.get_piece()) 

  // 4. add the piece to the "to" position
  std::string p;
  p += last_move.get_piece()->get_type();

  xw->fillRectangle(to.get_x() * 10, to.get_y() * 10, 10, 10, 0);
  xw->drawString(to.get_x() * 10 + 3, to.get_y() * 10 + 9, p);
  }
}
