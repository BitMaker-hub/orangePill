#include "gpio.h"
#include "btc.h"
#include "workflow.h"
#include "GlobalVARS.h"

sPILL myPill;

void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);            // Init pushbutton pin
  Serial.begin(SERIAL_BAUD);                    // Init Serial port
  EEPROMsetup();                                // Init EEPROMdata
  LedSetup();                                   // Init neopixels leds
  AccSetup();                                   // Init Accelerometer
  initUSBKeyboard();                            // Init USB Keyboard emulation
  initWallet();                                 // Init wallet data
}


void loop() {
  showInitEffect();

  while(true){
    int buttonState = checkButton();

    switch(myPill.State){
      case STATE_VIRGIN:   doVirginState(buttonState); break;
      case STATE_SEEDING:  doSeedingState(buttonState); break;
      case STATE_LOCKED:   doLockedState(buttonState); break;
      case STATE_OPENPILL: doOpenPill(buttonState); break;
      case STATE_UNLOCKED: doUnlockedState(buttonState); break;
    }
    delay(10);
  }
}
