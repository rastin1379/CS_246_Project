#ifndef _GRAPHICSOBSERVER_H_
#define _GRAPHICSOBSERVER_H_
#include <vector>
#include "observer.h"
#include "window.h"
#include "board.h"

class GraphicsObserver : public Observer
{
  std::shared_ptr<Board> board;
  Xwindow *xw = nullptr;

public:
  GraphicsObserver(std::shared_ptr<Board> board);
  void notify(std::string result) override;
  ~GraphicsObserver();
};

#endif
