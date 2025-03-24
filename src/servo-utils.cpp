#include "servo-utils.h"
#include <cmath>

// Constructor implementation
servo::mg996r::mg996r(int pin, int degree) : SERVO_PIN(pin), curDegree(degree) {
    // Setup LEDC
    ledcSetup(MG996R_CHANNEL, MG996R_FREQ, MG996R_RESOLUTION);
    ledcAttachPin(SERVO_PIN, MG996R_CHANNEL);
    // Reset to current degree
    rotateTo(degree);
}

// Calculate duty ratio of the target degree
int servo::mg996r::calculatePWM(int degree) {
    float min_width = 0.6 / 20 * pow(2, MG996R_RESOLUTION);
    float max_width = 2.5 / 20 * pow(2, MG996R_RESOLUTION);
    if (degree < 0)
        degree = 0;
    if (degree > 180)
        degree = 180;
    return (int)(((max_width - min_width) / 180) * degree + min_width);
}

void servo::mg996r::rotateTo(int degree) {
    ledcWrite(MG996R_CHANNEL, calculatePWM(degree));
    curDegree = degree;
}

int servo::mg996r::getCurrentDegree() {
    return curDegree;
}