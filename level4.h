#ifndef LEVEL4_H
#define LEVEL4_H

#include "computerplayer.h"

class Level4 : public ComputerPlayer {
        public:
        std::vector<Position> play(Board * board_obj);
};

#endif
