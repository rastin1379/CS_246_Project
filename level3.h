#ifndef LEVEL3_H
#define LEVEL3_H

#include "computerplayer.h"

class Level3 : public ComputerPlayer {
        public:
        std::vector<Position> play(Board * board_obj) override;
};

#endif
