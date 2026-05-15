#include <Keyboard.h>
#include "Joystick.h"
#include <Keypad.h>

/* Keypad declarations */
byte rowPins[] = {40, 42, 44, 46};
byte colPins[] = {48, 50, 52};
char numpad[] = {
  '7', '8', '9',
  '4', '5', '6',
  '1', '2', '3',
  '0', '.', KEY_KP_PLUS,
};
Keypad kpd = Keypad(numpad, rowPins, colPins, 4, 3);

Joystick_ Joystick;

void startupLightshow() {
  for(int x = -200; x < 1200; x++) {
    for(int i = 0; i < 9; i++) {
      int xd = x - i * 100 + 100;
      if (xd < 0) xd = -xd;
      if (xd > 255) xd = 255;
      analogWrite(i+2, 255 - xd);
    }
    delay(1);
  }
}

void setup() {
  for(int i = 0; i < 9; i++) {
    pinMode(i+11, INPUT_PULLUP);
    pinMode(i+2, OUTPUT);
    digitalWrite(i+2, 0);
  }
  Keyboard.begin();
  startupLightshow();
}

void loop() {
  for (int index = 0; index < 9; index++) {
    int currentButtonState = !digitalRead(index + 11);
//  digitalWrite(2+index, !currentButtonState);
    Joystick.setButton(index, currentButtonState);
  }
  Joystick.sendState();
  if (kpd.getKeys()) {
    for (int i = 0; i < kpd.numKeys(); i++) {
      if (kpd.key[i].stateChanged) {
        switch (kpd.key[i].kstate) {
          case PRESSED:
            Keyboard.press(kpd.key[i].kchar);
            break;
          case RELEASED:
            Keyboard.release(kpd.key[i].kchar);
            break;
        }
      }
    }
  }
  delay(10);
}
