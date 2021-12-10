#ifndef LEVEL2_H
#define LEVEL2_H

#include "computerplayer.h"

class Level2 : public ComputerPlayer {
        public:
        std::vector<Position> play(Board * board_obj) override;
};

#endif
