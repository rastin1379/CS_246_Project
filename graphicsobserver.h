#ifndef _GRAPHICSOBSERVER_H_
#define _GRAPHICSOBSERVER_H_
#include <vector>
#include "observer.h"
#include <memory>
#include "window.h"
#include "board.h"

class GraphicsObserver : public Observer
{
  Board * board;
  //Xwindow *xw = nullptr;
  std::shared_ptr<Xwindow> xw = nullptr;
public:
  GraphicsObserver(Board * board);
  void notify(std::string result) override;
  ~GraphicsObserver();
};

#endif
