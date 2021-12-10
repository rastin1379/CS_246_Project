#ifndef LEVEL1_H
#define LEVEL1_H

#include "computerplayer.h"

class Level1 : public ComputerPlayer {
	public:
	std::vector<Position> play(Board * board_obj) override;
};

#endif
