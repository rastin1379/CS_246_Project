#include <iostream>
#include "studio.h"
#include "observer.h"
#include "textobserver.h"

TextObserver::TextObserver(ChessView *board) : board{board}
{
  board->attach(this);
}

TextObserver::~TextObserver()
{
  board->detach(this);
}

void TextObserver::notify()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      std::cout << board->getChar(i, j);
    }
  }
}
