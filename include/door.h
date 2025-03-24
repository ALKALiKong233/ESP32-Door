#ifndef DOOR_H
#define DOOR_H

#include "servo-utils.h"

#define OPEN_DEGREE 180
#define CLOSE_DEGREE 90

namespace door {
    void open() {
        servo::mg996r::getInstance().rotateTo(OPEN_DEGREE);
    }

    void close() {
        servo::mg996r::getInstance().rotateTo(CLOSE_DEGREE);
    }
}
#endif
