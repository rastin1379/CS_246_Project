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
    xw->drawString(25, 25, "r");
    xw->drawString(75, 25, "n");
    xw->drawString(125, 25, "b");
    xw->drawString(175, 25, "q");
    xw->drawString(225, 25, "k");
    xw->drawString(275, 25, "b");
    xw->drawString(325, 25, "n");
    xw->drawString(375, 25, "r");

    xw->drawString(25, 75, "p");
    xw->drawString(75, 75, "p");
    xw->drawString(125, 75, "p");
    xw->drawString(175, 75, "p");
    xw->drawString(225, 75, "p");
    xw->drawString(275, 75, "p");
    xw->drawString(325, 75, "p");
    xw->drawString(375, 75, "p");

    for (int i = 100; i < 300; i += 50)
    {
      for (int j = 0; j <= 350; j += 50)
      {
        if ((i % 100 == 0) && (j % 100 == 0))
        {
          //prints white
          xw->fillRectangle(j, i, 50, 50, 8);
        }
        else if ((i % 100 == 0) && (j % 100 != 0))
        {
          // prints black
          xw->fillRectangle(j, i, 50, 50, 9);
        }
        else if ((i % 100 != 0) && (j % 100 == 0))
        {
          // prints black
          xw->fillRectangle(j, i, 50, 50, 9);
        }
        else
        {
          // prints white
          xw->fillRectangle(j, i, 50, 50, 8);
        }
      }
    }

    xw->drawString(25, 325, "P");
    xw->drawString(75, 325, "P");
    xw->drawString(125, 325, "P");
    xw->drawString(175, 325, "P");
    xw->drawString(225, 325, "P");
    xw->drawString(275, 325, "P");
    xw->drawString(325, 325, "P");
    xw->drawString(375, 325, "P");

    xw->drawString(25, 375, "R");
    xw->drawString(75, 375, "N");
    xw->drawString(125, 375, "B");
    xw->drawString(175, 375, "Q");
    xw->drawString(225, 375, "K");
    xw->drawString(275, 375, "B");
    xw->drawString(325, 375, "N");
    xw->drawString(375, 375, "R");
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
    xw->fillRectangle(from_x * 50, from_y * 50, 50, 50, 8);

  } else if ((from_x % 2 == 0) && (from_y % 2 != 0)){
  // if x % 2 == 0 and y % 2 != 0
    // prints black
    xw->fillRectangle(from_x * 50, from_y * 50, 50, 50, 9);

  } else if ((from_x % 2 != 0) && (from_y % 2 == 0)){
  // if x % 2 != 0 y % 2 == 0
    // prints black
    xw->fillRectangle(from_x * 50, from_y * 50, 50, 50, 9);

  } else {
  // else 
    // prints white
    xw->fillRectangle(from_x * 50, from_y * 50, 10, 10, 8);
  }
  
  // 3. get the piece (move.get_piece()) 

  // 4. add the piece to the "to" position
  std::string p;
  p += last_move.get_piece()->get_type();

  xw->fillRectangle(to.get_x() * 50, to.get_y() * 50, 50, 50, 0);
  xw->drawString(to.get_x() * 50 + 25, to.get_y() * 50 + 25, p);
  }
}
