#include <Arduino.h>
#include "ESP32TimerInterrupt.h"

#define BUTTON_PIN_A 26
#define BUTTON_PIN_B 23
#define DEBOUNCE_TIME 50   // Debounce time in milliseconds
#define INITIAL_DELAY 500  // Delay in milliseconds before starting to repeat
#define REPEAT_RATE 100    // Repeat rate in milliseconds after initial delay

bool buttonPressedA = false;
bool buttonPressedB = false;
unsigned long lastDebounceTimeA = 0;
unsigned long lastDebounceTimeB = 0;
unsigned long lastRepeatTimeA = 0;
unsigned long lastRepeatTimeB = 0;
bool initialPressA = true;
bool initialPressB = true;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN_A, INPUT_PULLUP); // Initialize Button A
  pinMode(BUTTON_PIN_B, INPUT_PULLUP); // Initialize Button B
}

void loop() {
  int buttonStateA = digitalRead(BUTTON_PIN_A); // Read the state of Button A
  int buttonStateB = digitalRead(BUTTON_PIN_B); // Read the state of Button B

  // Debounce logic for Button A
  if (millis() - lastDebounceTimeA > DEBOUNCE_TIME) {
    if (buttonStateA == LOW) { // Check if Button A is pressed
      if (!buttonPressedA) {
        // First press of Button A
        buttonPressedA = true;
        initialPressA = true;
        lastRepeatTimeA = millis();
        Serial.print("A");  // Print 'A' for the first press
      } else {
        // Handle continuous press for Button A
        if (initialPressA && (millis() - lastRepeatTimeA > INITIAL_DELAY)) {
          // Initial delay before repeating has passed
          initialPressA = false;
          lastRepeatTimeA = millis();
        } else if (!initialPressA && (millis() - lastRepeatTimeA > REPEAT_RATE)) {
          // Repeat rate logic
          lastRepeatTimeA = millis();
          Serial.print("A");  // Print 'A' repeatedly
        }
      }
    } else {
      buttonPressedA = false;  // Button A is released
    }
    lastDebounceTimeA = millis();
  }

  // Debounce logic for Button B
  if (millis() - lastDebounceTimeB > DEBOUNCE_TIME) {
    if (buttonStateB == LOW) { // Check if Button B is pressed
      if (!buttonPressedB) {
        // First press of Button B
        buttonPressedB = true;
        initialPressB = true;
        lastRepeatTimeB = millis();
        Serial.print("B");  // Print 'B' for the first press
      } else {
        // Handle continuous press for Button B
        if (initialPressB && (millis() - lastRepeatTimeB > INITIAL_DELAY)) {
          // Initial delay before repeating has passed
          initialPressB = false;
          lastRepeatTimeB = millis();
        } else if (!initialPressB && (millis() - lastRepeatTimeB > REPEAT_RATE)) {
          // Repeat rate logic
          lastRepeatTimeB = millis();
          Serial.print("B");  // Print 'B' repeatedly
        }
      }
    } else {
      buttonPressedB = false;  // Button B is released
    }
    lastDebounceTimeB = millis();
  }
}
