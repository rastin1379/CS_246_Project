#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <vector>
#include <iostream>
#include "observer.h"
#include "subject.h"

class TextObserver : public Observer
{
  shared_ptr<ChessView> board;

public:
  TextObserver(shared_ptr<ChessView> board);
  void notify() override;
  ~TextObserver();
};

#endif
