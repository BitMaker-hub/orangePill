#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "leds.h"

#include "hidkeyboard.h"
HIDkeyboard Keyboard;

const int buttonPin = 45;          // input pin for pushbutton
int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize control over the keyboard:
  Serial.begin(115200);
  Keyboard.begin();
  LedSetup();
  //USB.begin();
}

void loop() {
  Ledloop();
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == LOW)) {
    // increment the button counter
    Serial.print("pressed - ");
    counter++;
    // type out a message
    String text = "You pressed the button " + String(counter) + "times.\n";
    Serial.println(Keyboard.sendString(text)?"OK":"FAIL");
    /*Keyboard.sendString("You pressed the button ");
    Keyboard.sendString(counter);
    Keyboard.sendString(" times.\n");*/
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}