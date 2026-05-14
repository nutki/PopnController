#include <Keyboard.h>
#include "Joystick.h"
#include <Keypad.h>

/* Keypad declarations */
const byte ROWS = 4;
const byte COLS = 3;
byte rowPins[ROWS] = {40, 42, 44, 46}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {48, 50, 52}; //connect to the column pinouts of the keypad
char numpad[ROWS][COLS] = {
  {'7', '8', '9'},
  {'4', '5', '6'},
  {'1', '2', '3'},
  {'0', ',', '\337'}
};
Keypad kpd = Keypad( makeKeymap(numpad), rowPins, colPins, ROWS, COLS );

Joystick_ Joystick;

void setup() {
  // Initialize Button Pins
  for(int i = 0; i < 9; i++) {
    pinMode(i+2, OUTPUT);
    digitalWrite(i, 0);
  }
  for(int i = 9; i < 18; i++) {
    pinMode(i+2, INPUT_PULLUP);
  }
//  Serial.begin(115200);
  Keyboard.begin();
}

// Last state of the button
int lastButtonState[9];

void loop() {
  // Read pin values
  bool changed = false;
  for (int index = 0; index < 9; index++)
  {
    int currentButtonState = !digitalRead(index + 11);
    if (currentButtonState != lastButtonState[index])
    {
      if (lastButtonState[index] != currentButtonState) {
//        digitalWrite(2+index, !currentButtonState);
        Joystick.setButton(index, currentButtonState);
        changed = true;
        lastButtonState[index] = currentButtonState;
      }
    }
  }
  if (changed) Joystick.sendState();
  if (kpd.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if (kpd.key[i].stateChanged)   // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
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
