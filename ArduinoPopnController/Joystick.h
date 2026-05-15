#ifndef JOYSTICK_h
#define JOYSTICK_h

#include <stdint.h>

class Joystick_ {
private:
    // Joystick State
    uint8_t   report[4];
    bool      reportChanged;
public:
    Joystick_();
    void setButton(uint8_t button, uint8_t value);
    void sendState();
};

#endif // JOYSTICK_h
