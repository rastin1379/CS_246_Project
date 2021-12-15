#include <iostream>
#include "observer.h"
#include <string>
#include "window.h"
#include "graphicsobserver.h"

using namespace std;

GraphicsObserver::GraphicsObserver(Board * board) : board{board}, 
 // xw{new Xwindow(480, 480)}
  xw{make_shared<Xwindow>(480, 480)}
{
  board->attach(this);
}

GraphicsObserver::~GraphicsObserver()
{
  board->detach(this);
}

void GraphicsObserver::notify(string result)
{
  std::vector<std::vector<std::shared_ptr<Piece>>> board_array = board->get_board();

  if(board->get_game_mode() == "setup" || board->get_move_size() == 0){
	  for (int i = 0; i < 8; ++i) {
		  for (int j = 0; j < 8; ++j) {
			  if (board_array[i][j] == nullptr){
				  if ((j + i) % 2 == 1) { xw->fillRectangle(j * 50, i * 50, 50, 50, 9);}
				  else { xw->fillRectangle(j * 50, i * 50, 50, 50, 8); }
			  }
			  else {
          std::string p;
          p += board_array[i][j]->get_type();
          xw->fillRectangle(j * 50, i * 50, 50, 50, 0);
          xw->drawString(j * 50 + 25, i * 50 + 25, p);
			  }
      }
    }
    
  } else {
    // the x position starts from 0, from left
    // the y position starts from 0, from top
    Move last_move = board->get_last_move();
    Position from = last_move.get_from();
    Position to = last_move.get_to();
    
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
      xw->fillRectangle(from_x * 50, from_y * 50, 50, 50, 8);
    }
    
    // 3. add the piece to the "to" position
    std::string p;
    p += last_move.get_piece()->get_type();
    xw->fillRectangle(to.get_x() * 50, to.get_y() * 50, 50, 50, 0);
    xw->drawString(to.get_x() * 50 + 25, to.get_y() * 50 + 25, p);

    if(last_move.is_en_passant()){
      int step = (last_move.get_piece()->get_color() == 'w') ? -1 : 1;
      int passant_x = last_move.get_to().get_x();
      int passant_y = last_move.get_to().get_y() - step;
      if ((passant_x + passant_y) % 2 == 1) { xw->fillRectangle(passant_x * 50, passant_y * 50, 50, 50, 9);}
			else { xw->fillRectangle(passant_x * 50, passant_y * 50, 50, 50, 8); }
    }

    if (last_move.is_castle()){
      
      if (last_move.get_to().get_x() == 6 && last_move.get_to().get_y() == 7){
        //move the rook
        xw->fillRectangle(5 * 50, 7 * 50, 50, 50, 0);
        xw->drawString(5 * 50 + 25, 7 * 50 + 25, "R");

        //delete old rook
        xw->fillRectangle(7 * 50, 7 * 50, 50, 50, 8);
      }

      if (last_move.get_to().get_x() == 2 && last_move.get_to().get_y() == 7){
        //move the rook
        xw->fillRectangle(3 * 50, 7 * 50, 50, 50, 0);
        xw->drawString(3 * 50 + 25, 7 * 50 + 25, "R");

        //delete old rook
        xw->fillRectangle(0 * 50, 7 * 50, 50, 50, 9);
      }

      if (last_move.get_to().get_x() == 6 && last_move.get_to().get_y() == 0){
        //move the rook
        xw->fillRectangle(5 * 50, 0 * 50, 50, 50, 0);
        xw->drawString(5 * 50 + 25, 0 * 50 + 25, "r");

        //delete old rook
        xw->fillRectangle(7 * 50, 0 * 50, 50, 50, 9);
      }

      if (last_move.get_to().get_x() == 2 && last_move.get_to().get_y() == 0){
        //move the rook
        xw->fillRectangle(3 * 50, 0 * 50, 50, 50, 0);
        xw->drawString(3 * 50 + 25, 0 * 50 + 25, "r");

        //delete old rook
        xw->fillRectangle(0 * 50, 0 * 50, 50, 50, 8);
      }
    }

    //promotion
    if ((board_array[last_move.get_to().get_y()][last_move.get_to().get_x()]->get_color() == 'w' && last_move.get_to().get_y() == 0) || 
        (board_array[last_move.get_to().get_y()][last_move.get_to().get_x()]->get_color() == 'b' && last_move.get_to().get_y() == 7)){
          if (board_array[last_move.get_to().get_y()][last_move.get_to().get_x()]->get_color() == 'w'){
            xw->fillRectangle(last_move.get_to().get_x() * 50, last_move.get_to().get_y() * 50, 50, 50, 0);
            xw->drawString(last_move.get_to().get_x() * 50 + 25, last_move.get_to().get_y() * 50 + 25, "Q");
          } else {
            xw->fillRectangle(last_move.get_to().get_x() * 50, last_move.get_to().get_y() * 50, 50, 50, 0);
            xw->drawString(last_move.get_to().get_x() * 50 + 25, last_move.get_to().get_y() * 50 + 25, "q");
          }
      }
  }
}