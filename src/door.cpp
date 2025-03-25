#include "door.h"

namespace door {
    void open() {
        servo::mg996r::getInstance().rotateTo(OPEN_DEGREE);
    }

    void close() {
        servo::mg996r::getInstance().rotateTo(CLOSE_DEGREE);
    }
}