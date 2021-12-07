#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include <vector>
#include <iostream>
#include "observer.h"
#include "board.h"

class TextObserver : public Observer
{
	std::shared_ptr<Board> board;

	public:
  	TextObserver(std::shared_ptr<Board> board);
  	void notify() override;
  	~TextObserver();
};

#endif
