#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <vector>
#include <iostream>
#include "observer.h"
#include "subject.h"

class TextObserver : public Observer
{
  ChessView *board = nullptr;
  const int top = 0;
  const int bottom = 0;
  const int left = 0;
  const int right = 0;

public:
  TextObserver(ChessView *board);
  void notify() override;
  ~TextObserver();
};

#endif
