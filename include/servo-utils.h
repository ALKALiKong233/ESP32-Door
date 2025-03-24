#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif // ARDUINO_H

#ifndef SERVO_H
#define SERVO_H
#define MG996R_FREQ 50
#define MG996R_CHANNEL 0
#define MG996R_RESOLUTION 8
namespace servo {
    class mg996r {
        private:
            int SERVO_PIN;
            int curDegree;
        public:
            mg996r( int pin, int degree );
            static int calculatePWM( int degree );
            void rotateTo( int degree );
            int getCurrentDegree();
    };
}
#endif // SERVO_H