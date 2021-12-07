#include <iostream>
#include "studio.h"
#include "observer.h"
#include "textobserver.h"

TextObserver::TextObserver(shared_ptr<ChessView> board) : board{board}
{
  board->attach(this);
}

TextObserver::~TextObserver()
{
  board->detach(this);
}

void TextObserver::notify()
{
}
