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
            // Make the construction func private to avoid being instanced externally
            mg996r(int pin, int degree);
            
            int SERVO_PIN;
            int curDegree;
            
            static mg996r* instance;
            
        public:
            mg996r(const mg996r&) = delete;
            mg996r& operator=(const mg996r&) = delete;
            
            static mg996r& getInstance(int pin = -1, int degree = 0);
            
            static int calculatePWM(int degree);
            void rotateTo(int degree);
            int getCurrentDegree();
    };
}
#endif // SERVO_H